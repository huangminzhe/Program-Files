#include <bits/stdc++.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define TCP_PORT 8888
#define UDP_PORT 8889
#define BUFFER_SIZE 4096

using namespace std;

vector<SOCKET> clients;
mutex mtx;
atomic<bool> server_running{1};

SYSTEMTIME getTime(){
	SYSTEMTIME time;
	GetLocalTime(&time);
	return time;
}

void handle_client(SOCKET client_sock) {
    char buffer[BUFFER_SIZE];
    time_t last_active = time(nullptr);

    while (server_running) {
        // 设置接收超时
        struct timeval tv{1, 0}; // 1秒，0微秒
        setsockopt(client_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));

        int bytes_received = recv(client_sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received > 0) {
            last_active = time(nullptr);

            // 处理心跳包
            if (strncmp(buffer, "[PING]", 6) == 0) {
                send(client_sock, "[PONG]", 6, 0);
                continue;
            }

            // 广播消息
            lock_guard<mutex> lock(mtx);
            for (SOCKET sock : clients) {
                if (sock != client_sock) {
                    send(sock, buffer, bytes_received, 0);
                }
            }
        }
        else {
            // 检测超时（30秒）
            if (time(nullptr) - last_active > 10) {
                cout << "客户端超时断开\n";
                break;
            }
        }
    }

    // 清理客户端
    lock_guard<mutex> lock(mtx);
    auto it = find(clients.begin(), clients.end(), client_sock);
    if (it != clients.end()) clients.erase(it);
    closesocket(client_sock);
}

void udp_broadcast() {
    SOCKET udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    int broadcast = 1;
    setsockopt(udp_sock, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast));

    sockaddr_in broadcast_addr{};
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    broadcast_addr.sin_port = htons(UDP_PORT);

    const char* discovery_msg = "CHAT_SERVER_V1.4";

    while (server_running) {
        sendto(udp_sock, discovery_msg, strlen(discovery_msg), 0,
               (sockaddr*)&broadcast_addr, sizeof(broadcast_addr));
        this_thread::sleep_for(chrono::seconds(3));
    }
    closesocket(udp_sock);
}

int main(int argc, char **argv){
	SYSTEMTIME time;
	DWORD err;
	WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa)){
		time = getTime();
		err = GetLastError();
		printf("[%02d:%02d:%02d] 初始化套接字失败。代码：%lu\n",time.wHour,time.wMinute,time.wSecond,err);
		WSACleanup();
		return err;
	}

	// 启动TCP服务器
    SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in tcp_addr{};
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_addr.s_addr = INADDR_ANY;
    tcp_addr.sin_port = htons(TCP_PORT);
    if (bind(tcp_sock, (sockaddr*)&tcp_addr, sizeof(tcp_addr))){
		time = getTime();
		err = GetLastError();
		printf("[%02d:%02d:%02d] 绑定套接字失败。代码：%lu\n",time.wHour,time.wMinute,time.wSecond,err);
		WSACleanup();
		return err;
	}
    listen(tcp_sock, 5);

	// 启动UDP广播线程
    thread(udp_broadcast).detach();

	time = getTime();
	printf("[%02d:%02d:%02d] 服务器已启动。\n",time.wHour,time.wMinute,time.wSecond);

	while (server_running) {
        SOCKET client_sock = accept(tcp_sock, nullptr, nullptr);
        if (client_sock != INVALID_SOCKET) {
            lock_guard<mutex> lock(mtx);
            clients.push_back(client_sock);
            thread(handle_client, client_sock).detach();
			time = getTime();
			printf("[%02d:%02d:%02d] 新客户端连接，当前在线：%d\n",time.wHour,time.wMinute,time.wSecond,clients.size());
        }
    }

	// 清理
    closesocket(tcp_sock);
    WSACleanup();
	return 0;
}