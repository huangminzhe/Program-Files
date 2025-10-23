#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5,M = 5e5 + 5;
const ll INF = LLONG_MAX;
struct point{
	int v;ll w;
};
bool operator< (point b,point c){
	return b.w > c.w;
}
int n,m,k,p[N],fa1[N],fa2[N];
bool f[N];
ll d1[N],d2[N],mn;
vector<point> g[N],fg[N];
void djkstr(vector<point> *g,ll *d,int *fa){
	fill(d + 1,d + n + 1,INF / 2);
	fill(fa + 1,fa + n + 1,-1);
	fill(f + 1,f + n + 1,0);
	priority_queue<point> q;
	for (int i = 1;i <= k;i++)	d[p[i]] = 0,fa[p[i]] = p[i],q.push({p[i],0});
	while (!q.empty()){
		int u = q.top().v;
		q.pop();
		if (f[u])	continue;
		f[u] = 1;
		for (auto [v,w] : g[u]){
		// for (auto i : g[u]){
		// 	int v = i.v;ll w = i.w;
			if (d[u] + w < d[v]){
				d[v] = d[u] + w;
				fa[v] = fa[u];
				q.push({v,d[v]});
			}
		}
	}
}
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		cin >> n >> m >> k;
		for (int i = 1;i <= n;i++)	g[i].clear(),fg[i].clear();
		for (int i = 1;i <= m;i++){
			int u,v;ll w;
			cin >> u >> v >> w;
			g[u].push_back({v,w});
			fg[v].push_back({u,w});
		}
		for (int i = 1;i <= k;i++){
			cin >> p[i];
		}
		djkstr(g,d1,fa1);
		djkstr(fg,d2,fa2);
		mn = INF;
		for (int i = 1;i <= n;i++){
			if (fa1[i] != fa2[i])
				mn = min(mn,d1[i] + d2[i]);
		}
		for (int u = 1;u <= n;u++){
			for (auto [v,w] : g[u]){
				if (fa1[u] != fa2[v])
					mn = min(mn,d1[u] + d2[v] + w);
			}
		}
		cout << mn << '\n';
	}
	return 0;
}