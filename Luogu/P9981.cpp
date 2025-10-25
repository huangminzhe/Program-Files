#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
struct point{
	int v,w;
};
int n,m,in[N],d[N],ord[N];
vector<point> g[N];
vector<vector<ll>> ans[N];
ll sum[N];
void bfs(){
	queue<int> q;
	for (int i = 1;i <= n;i++){
		if (!in[i])	q.push(i);
	}
	while (!q.empty()){
		int len = q.size();
		while (len--){
			int u = q.front();
			q.pop();
			for (auto [v,w] : g[u]){
			// for (auto i : g[u]){
			// 	int v = i.v,w = i.w;
				ans[v].push_back({-d[u],w,ord[u],sum[u] + w});
				in[v]--;
				if (!in[v]){
					d[v] = d[u] + 1;
					q.push(v);
				}
			}
		}
		vector<vector<ll>> t;
		len = q.size();
		while (len--){
			int x = q.front();
			q.pop();
			sort(ans[x].begin(),ans[x].end());
			sum[x] = ans[x][0][3];
			t.push_back({ans[x][0][1],ans[x][0][2],x});
			q.push(x);
		}
		sort(t.begin(),t.end());
		for (int i = 0;i < t.size();i++)	ord[t[i][2]] = i;
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		int u,v,w;
		cin >> u >> v >> w;
		g[v].push_back({u,w});
		in[u]++;
	}
	bfs();
	for (int i = 1;i <= n;i++){
		cout << d[i] << ' ' << sum[i] << '\n';
	}
	return 0;
}