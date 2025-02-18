#include <bits/stdc++.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define TCP_PORT 8888
#define UDP_PORT 8889
#define BUFFER_SIZE 4096

using namespace std;

atomic<bool> is_running{1};
atomic<bool> is_connected{0};
atomic<time_t> last_pong{0};
string username;
SYSTEMTIME systime;
DWORD err;

SYSTEMTIME getTime(){
	SYSTEMTIME time;
	GetLocalTime(&time);
	return time;
}

// 进度显示函数
void show_progress(size_t current, size_t total) {
    float progress = (float)current / total * 100;
    cout << "\r[";
    int pos = progress / 2;
    for (int i = 0; i < 50; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(progress) << "% (" 
         << current/1024 << "KB/" << total/1024 << "KB)" << flush;
}

vector<string> discover_servers(int timeout = 3) {
    unordered_set<string> servers;
    SOCKET udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    // 非阻塞模式
    unsigned long mode = 1;
    ioctlsocket(udp_sock, FIONBIO, &mode);
    
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(UDP_PORT);
    bind(udp_sock, (sockaddr*)&addr, sizeof(addr));

    time_t start = time(nullptr);
    char buffer[256];
    cout << "正在扫描服务器...";

    while (time(nullptr) - start < timeout) {
        sockaddr_in from{};
        int from_len = sizeof(from);
        int len = recvfrom(udp_sock, buffer, sizeof(buffer), 0,
                          (sockaddr*)&from, &from_len);
        
        if (len > 0 && strncmp(buffer, "CHAT_SERVER_", 12) == 0) {
            servers.insert(inet_ntoa(from.sin_addr));
        }
        cout << "." << flush;
        Sleep(300);
    }
    closesocket(udp_sock);
    return {servers.begin(), servers.end()};
}

string select_server(const vector<string>& servers) {
    cout << "\n发现 " << servers.size() << " 个服务器:\n";
    for (size_t i = 0; i < servers.size(); ++i) {
        cout << " [" << i+1 << "] " << servers[i] << "\n";
    }

    while (true) {
        cout << "请选择 (1-" << servers.size() << ") 或 0 重新扫描: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) return "";
        if (choice > 0 && choice <= (int)servers.size()) {
            return servers[choice-1];
        }
    }
}

void receive_handler(SOCKET sock) {
    char buffer[BUFFER_SIZE];
    size_t file_size = 0, received = 0;
    ofstream out_file;
    string current_file;

    while (is_connected) {
        int bytes = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes > 0) {
            if (strncmp(buffer, "[PONG]", 6) == 0) {
                last_pong = time(nullptr);
                continue;
            }

            if (strncmp(buffer, "[FILE]", 6) == 0) {
                string header(buffer, bytes);
                size_t pos1 = header.find('|', 6);
                size_t pos2 = header.find('|', pos1+1);
                
                string sender = header.substr(6, pos1-6);
                current_file = header.substr(pos1+1, pos2-pos1-1);
                file_size = stoull(header.substr(pos2+1));
                
                received = 0;
                out_file.open(current_file, ios::binary);
                cout << "\n接收文件: " << current_file 
                     << " (" << file_size/1024 << "KB) 来自 " << sender << endl;
                continue;
            }

            if (out_file.is_open()) {
                out_file.write(buffer, bytes);
                received += bytes;
                show_progress(received, file_size);
                
                if (received >= file_size) {
                    out_file.close();
                    cout << "\n文件保存完成: " << current_file << endl;
                }
            } else {
                cout << "\n" << string(buffer, bytes) << endl;
                cout << "> " << flush;
            }
        }
        else {
            is_connected = false;
        }
    }
}

void ping_thread(SOCKET sock) {
    while (is_connected) {
        if (send(sock, "[PING]", 6, 0) <= 0) {
            is_connected = false;
            break;
        }
        this_thread::sleep_for(5s);

        if (time(nullptr) - last_pong > 10) {
            cerr << "\n与服务器失去连接！\n";
            is_connected = false;
            closesocket(sock);
            break;
        }
    }
}

void send_file(SOCKET sock, const string& path) {
    ifstream file(path, ios::binary | ios::ate);
    if (!file) {
        cerr << "文件打开失败\n";
        return;
    }

    size_t file_size = file.tellg();
    file.seekg(0);

    string filename = path.substr(path.find_last_of("\\/") + 1);
    string header = "[FILE]" + username + "|" + filename + "|" + to_string(file_size);
    
    if (send(sock, header.c_str(), header.size(), 0) <= 0) {
        cerr << "文件头发送失败\n";
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t total_sent = 0;
    while (!file.eof()) {
        file.read(buffer, BUFFER_SIZE);
        int bytes = send(sock, buffer, file.gcount(), 0);
        if (bytes > 0) {
            total_sent += bytes;
            show_progress(total_sent, file_size);
        } else {
            cerr << "\n文件发送中断\n";
            break;
        }
    }
    file.close();
    cout << "\n文件发送完成\n> " << flush;
}

int main(int argc, char **argv){
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
	if (WSAStartup(MAKEWORD(2,2), &wsa)){
		err = GetLastError();
		printf("初始化套接字失败。代码：%lu\n",err);
		WSACleanup();
		return err;
	}

	while (is_running){
		auto servers = discover_servers();
		if (servers.empty()) {
            cout << "\n未找到服务器！\n1.重试\n2.退出\n请选择: ";
            int opt;
            cin >> opt;
            cin.ignore();
            if (opt != 1) break;
            continue;
        }

		string ip = select_server(servers);
        if (ip.empty()) continue;

		SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(TCP_PORT);
		
		if (connect(sock, (sockaddr*)&addr, sizeof(addr)) != 0) {
            cerr << "连接失败！\n";
            continue;
        }

		cout << "请输入用户名: ";
        getline(cin, username);
        if (send(sock, username.c_str(), username.size(), 0) <= 0) {
            cerr << "用户名发送失败\n";
            closesocket(sock);
            continue;
        }

		is_connected = true;
		last_pong = time(nullptr);

		thread(receive_handler, sock).detach();
		thread(ping_thread, sock).detach();

		// 输入循环
		string input;
		while (is_connected) {
			cout << "> ";
            getline(cin, input);

            if (input.empty()) continue;
            if (input == "/exit" || input == "quit") break;

            if (input.substr(0, 9) == "/sendfile") {
                string path = input.substr(10);
                path.erase(remove(path.begin(), path.end(), '\"'), path.end());
                send_file(sock, path);
            } else {
                if (send(sock, input.c_str(), input.size(), 0) <= 0) {
                    cerr << "消息发送失败\n";
                    break;
                }
            }
		}

		is_connected = false;
		closesocket(sock);
		if (input == "/exit" || input == "/quit") break;
	}

	WSACleanup();
	return 0;
}