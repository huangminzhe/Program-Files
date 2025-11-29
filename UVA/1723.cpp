#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N = 5e4 + 5;
int n,mx;
vector<pii> a[N];
int dis[N];
bool f[N];
void spfa(){
	memset(dis,0xc0,sizeof dis);
	memset(f,0,sizeof f);
	dis[0] = 0;
	queue<int> q;
	q.push(0);
	while (!q.empty()){
		int u = q.front();
		q.pop();
		f[u] = 0;
		for (auto [v,w] : a[u]){
			if (dis[u] + w > dis[v]){
				dis[v] = dis[u] + w;
				if (!f[v]){
					q.push(v);
					f[v] = 1;
				}
			}
		}
	}
}
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		mx = 0;

		cin >> n;
		for (int i = 0;i <= n;i++)	a[i].clear();
		for (int i = 1;i <= n;i++){
			int u,v,w;
			cin >> u >> v >> w;
			u++,v++;
			a[u - 1].push_back({v,w});
			mx = max(mx,v);
		}
		for (int i = 1;i <= mx;i++){
			a[i - 1].push_back({i,0});
			a[i].push_back({i - 1,-1});
		}
		spfa();
		cout << dis[mx] << '\n';
	}
	return 0;
}