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
SYSTEMTIME systime;
DWORD err;

SYSTEMTIME getTime(){
	SYSTEMTIME time;
	GetLocalTime(&time);
	return time;
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
    while (is_connected) {
        int bytes = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes > 0) {
            if (strncmp(buffer, "[PONG]", 6) == 0) {
                last_pong = time(nullptr);
                continue;
            }
            cout << "\n接收: " << string(buffer, bytes) << endl;
        }
        else {
            is_connected = false;
            break;
        }
    }
}

void ping_thread(SOCKET sock) {
    while (is_connected) {
        if (send(sock, "[PING]", 6, 0) <= 0) {
            is_connected = false;
            break;
        }
        this_thread::sleep_for(chrono::seconds(5));

        if (time(nullptr) - last_pong > 10) {
            cerr << "\n服务器无响应，连接已断开！\n";
            is_connected = false;
            closesocket(sock);
            break;
        }
    }
}

void send_file(SOCKET sock, const string& path) {
    ifstream file(path, ios::binary);
    if (!file) {
        cerr << "文件打开失败\n";
        return;
    }

    // 发送文件头
    string header = "[FILE]" + path.substr(path.find_last_of("\\") + 1);
    send(sock, header.c_str(), header.size(), 0);

    // 发送文件内容
    char buffer[BUFFER_SIZE];
    while (!file.eof()) {
        file.read(buffer, BUFFER_SIZE);
        send(sock, buffer, file.gcount(), 0);
    }
    cout << "文件已发送\n";
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

		if (!connect(sock, (sockaddr*)&addr, sizeof(addr))){
			cout << "已连接至 " << ip << '\n';
            is_connected = true;
            last_pong = time(nullptr);

			thread(receive_handler, sock).detach();
			thread(ping_thread, sock).detach();

			// 输入循环
            string input;
            while (is_connected) {
                cout << "> ";
                getline(cin, input);

                if (input == "/exit") break;
                if (input.substr(0, 9) == "/sendfile") {
                    send_file(sock, input.substr(10));
                } else {
                    send(sock, input.c_str(), input.size(), 0);
                }
            }

			is_connected = false;
            closesocket(sock);
            if (input == "/exit") break;
		}else{
			cerr << "连接失败！\n";
		}
	}

	WSACleanup();
	return 0;
}