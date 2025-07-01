#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N = 5e3 + 5;
int n,m;
vector<pii> a[N];
int dis[N],cnt[N];
bool f[N];
bool spfa(){
	memset(dis,0x3f,sizeof dis);
	dis[0] = 0;
	cnt[0] = 1;
	queue<int> q;
	q.push(0);
	while (!q.empty()){
		int u = q.front();
		q.pop();
		f[u] = 0;
		for (auto [v,w] : a[u]){
			if (dis[u] + w < dis[v]){
				dis[v] = dis[u] + w;
				if (!f[v]){
					q.push(v);
					f[v] = 1;
					cnt[v]++;
					if (cnt[v] > n)	return 1;
					// 	cnt[v] >= n + 1（加了超级源点）
				}
			}
		}
	}
	return 0;
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		int u,v,w;
		cin >> v >> u >> w;
		a[u].push_back({v,w});
	}
	for (int i = 1;i <= n;i++)	a[0].push_back({i,0});
	if (spfa()){
		cout << "NO";
		return 0;
	}
	for (int i = 1;i <= n;i++)	cout << dis[i] << ' ';
	return 0;
}
// x_v-x_u<=y
// x_u+y>=x_v
// f[u]+w>=f[v]