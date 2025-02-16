#include <bits/stdc++.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define TCP_PORT 8888
#define UDP_PORT 8889
#define BUFFER_SIZE 4096

using namespace std;

atomic<bool> is_running{1};

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

int main(int argc, char **argv){
	SYSTEMTIME time;
	DWORD err;
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
	}
	return 0;
}