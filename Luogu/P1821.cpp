#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5,INF = 0x7fffffff;
struct point{
	int v,w;
};
bool operator< (point b,point c){
	return b.w > c.w;
}
vector<point> g[N];
int n,m,s,d[N],r[N];
bool f[N];
void djkstr(int s){
	fill(d + 1,d + n + 1,INF);
	fill(f + 1,f + n + 1,0);
	priority_queue<point> q;
	d[s] = 0;
	q.push({s,0});
	while (!q.empty()){
		int u = q.top().v;
		q.pop();
		if (f[u])	continue;
		f[u] = 1;
		for (auto [v,w] : g[u]){
		// for (auto i : g[u]){
		// 	int v = i.v,w = i.w;
			if (d[u] + w < d[v]){
				d[v] = d[u] + w;
				q.push({v,d[v]});
			}
		}
	}
}
int main(int argc, char **argv){
	cin >> n >> m >> s;
	for (int i = 1;i <= m;i++){
		int u,v,w;
		cin >> u >> v >> w;
		g[u].push_back({v,w});
	}
	djkstr(s);
	for (int i = 1;i <= n;i++)	r[i] = d[i];
	int mx = 0;
	for (int i = 1;i <= n;i++){
		djkstr(i);
		r[i] += d[s];
		mx = max(r[i],mx);
	}
	cout << mx;
	return 0;
}