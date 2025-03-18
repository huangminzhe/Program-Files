#include <bits/stdc++.h>
using namespace std;
const string TGT = "123804765";
map<string,bool> f;
int bfs(string st){
	queue<pair<string,int>> q;
	q.push({st,0});
	f[st] = 1;
	while (!q.empty()){
		string cur = q.front().first;
		int u = q.front().second;
		q.pop();
		if (cur == TGT)	return u;
		int i0 = cur.find('0');
		if (i0 % 3){	// 不在第一列
			swap(cur[i0],cur[i0 - 1]);
			if (!f[cur]){
				f[cur] = 1;
				q.push({cur,u + 1});
			}
			swap(cur[i0],cur[i0 - 1]);
		}
		if (i0 % 3 < 2){	// 不在第三列
			swap(cur[i0],cur[i0 + 1]);
			if (!f[cur]){
				f[cur] = 1;
				q.push({cur,u + 1});
			}
			swap(cur[i0],cur[i0 + 1]);
		}
		if (i0 / 3){	// 不在第一行
			swap(cur[i0],cur[i0 - 3]);
			if (!f[cur]){
				f[cur] = 1;
				q.push({cur,u + 1});
			}
			swap(cur[i0],cur[i0 - 3]);
		}
		if (i0 / 3 < 2){	// 不在第三行
			swap(cur[i0],cur[i0 + 3]);
			if (!f[cur]){
				f[cur] = 1;
				q.push({cur,u + 1});
			}
			swap(cur[i0],cur[i0 + 3]);
		}
	}
}
int main(int argc, char **argv){
	string s;
	cin >> s;
	cout << bfs(s);
	return 0;
}