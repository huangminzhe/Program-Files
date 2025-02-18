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
map<SOCKET, string> client_users;
SYSTEMTIME systime;
DWORD err;

SYSTEMTIME getTime(){
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	return systime;
}

void broadcast_message(const string& message) {
    lock_guard<mutex> lock(mtx);
    
    auto it = clients.begin();
    while (it != clients.end()) {
        SOCKET sock = *it;
        int result = send(sock, message.c_str(), message.size(), 0);
        
        if (result == SOCKET_ERROR) {
			systime = getTime();
            cerr << '[' << systime.wHour << ':' << systime.wMinute << ':' << systime.wSecond << 
					"] 清理失效连接: " << client_users[sock] << endl;
            closesocket(sock);
            it = clients.erase(it);
            client_users.erase(sock);
        } else {
            ++it;
        }
    }
}

void handle_client(SOCKET client_sock) {
    char username_buf[256];
    int name_len = recv(client_sock, username_buf, 255, 0);
    if (name_len <= 0) {
        closesocket(client_sock);
        return;
    }
    
    string username(username_buf, name_len);
    {
        lock_guard<mutex> lock(mtx);
        client_users[client_sock] = username;
        clients.push_back(client_sock);
    }

    broadcast_message("[系统] 用户 " + username + " 加入了聊天室");

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
            string full_msg = "[" + username + "] " + 
                                  string(buffer, bytes_received);
            broadcast_message(full_msg);
        }
        else {
            // 检测超时（10秒）
            if (time(nullptr) - last_active > 10) {
				systime = getTime();
                printf("[%02d:%02d:%02d] 客户端超时断开\n",systime.wHour,systime.wMinute,systime.wSecond);
                break;
            }
        }
    }

	{
        lock_guard<mutex> lock(mtx);
        auto it = find(clients.begin(), clients.end(), client_sock);
        if (it != clients.end()) clients.erase(it);
        client_users.erase(client_sock);
    }
	// 广播用户离开
    string leave_msg = "[系统] 用户 " + username + " 离开聊天室";
    broadcast_message(leave_msg);
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

    const char* discovery_msg = "CHAT_SERVER_V2.0";

    while (server_running) {
        sendto(udp_sock, discovery_msg, strlen(discovery_msg), 0,
               (sockaddr*)&broadcast_addr, sizeof(broadcast_addr));
        this_thread::sleep_for(chrono::seconds(3));
    }
    closesocket(udp_sock);
}

int main(int argc, char **argv){
	WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa)){
		systime = getTime();
		err = GetLastError();
		printf("[%02d:%02d:%02d] 初始化套接字失败。代码：%lu\n",systime.wHour,systime.wMinute,systime.wSecond,err);
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
		systime = getTime();
		err = GetLastError();
		printf("[%02d:%02d:%02d] 绑定套接字失败。代码：%lu\n",systime.wHour,systime.wMinute,systime.wSecond,err);
		WSACleanup();
		return err;
	}
    listen(tcp_sock, 5);

	// 启动UDP广播线程
    thread(udp_broadcast).detach();

	systime = getTime();
	printf("[%02d:%02d:%02d] 服务器已启动于 %d 端口。将广播服务器地址于 %d 端口。\n",systime.wHour,systime.wMinute,systime.wSecond,TCP_PORT,UDP_PORT);

	while (server_running) {
        SOCKET client = accept(tcp_sock, nullptr, nullptr);
        if (client != INVALID_SOCKET) {
            thread(handle_client, client).detach();
        }
    }

	// 清理
    closesocket(tcp_sock);
    WSACleanup();
	return 0;
}