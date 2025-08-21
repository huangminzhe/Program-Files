#include <bits/stdc++.h>
using namespace std;
unordered_map<string,int> servers;
bool check(string ip){
	ip = " " + ip;
	int n = ip.size(),num = 0,i = 1,o = 0;
	for (int I = 1;I <= 3;I++){
		for (;ip[i] != '.';i++){
			if (i >= n)	return 1;
			if (num > 255)	return 1;
			if ((i == 1 || ip[i - 1] == '.') && ip[i] == '0' && ip[i + 1] != '.')	return 1;
			if (ip[i] < '0' || ip[i] > '9')	return 1;
			num *= 10;
			num += ip[i] - '0';
		}
		if (i - o == 1)	return 1;
		if (num > 255)	return 1;
		o = i++;
		num = 0;
	}
	
	for (;ip[i] != ':';i++){
		if (i >= n)	return 1;
		if (num > 255)	return 1;
		if (ip[i - 1] == '.' && ip[i] == '0' && ip[i + 1] != ':')	return 1;
		if (ip[i] < '0' || ip[i] > '9')	return 1;
		num *= 10;
		num += ip[i] - '0';
	}
	if (i - o == 1)	return 1;
	if (num > 255)	return 1;
	num = 0;
	o = i++;
	
	for (;i < n;i++){
		if (num > 65535)	return 1;
		if (ip[i - 1] == ':' && ip[i] == '0' && i + 1 != n)	return 1;
		if (ip[i] < '0' || ip[i] > '9')	return 1;
		num *= 10;
		num += ip[i] - '0';
	}
	if (i - o <= 1)	return 1;
	if (num > 65535)	return 1;
	return 0;
}
inline bool find(string ip){
	return servers.find(ip) != servers.end();
}
int main(int argc, char **argv){
// 	freopen("network.in","r",stdin);
// #ifndef LOCAL
// 	freopen("network.out","w",stdout);
// #endif
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		string op,ip;
		cin >> op >> ip;
		if (!strcmp(op.c_str(),"Server")){
			if (check(ip)){
				cout << "ERR\n";
				continue;
			}
			if (find(ip)){
				cout << "FAIL\n";
				continue;
			}
			servers[ip] = i;
			cout << "OK\n";
		}else{
			if (check(ip)){
				cout << "ERR\n";
				continue;
			}
			if (!find(ip)){
				cout << "FAIL\n";
				continue;
			}
			cout << servers[ip] << '\n';
		}
	}
	return 0;
}
