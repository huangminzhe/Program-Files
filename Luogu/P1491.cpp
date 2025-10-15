#include <bits/stdc++.h>
using namespace std;
const int N = 205,INF = 0x7fffffff;
struct point{
	int v;
	double w;
}a[N];
bool operator< (point b,point c){
	return b.w > c.w;
}
int n,m,fa[N];
double d[N];
vector<point> g[N];
inline double calc(int u,int v){
	return sqrt((a[v].w - a[u].w) * (a[v].w - a[u].w) + (a[v].v - a[u].v) * (a[v].v - a[u].v));
}
void djkstr(int x,int y){
	fill(d + 1,d + n + 1,1.0 * INF);
	priority_queue<point> q;
	d[1] = 0;
	q.push({1,0});
	while (!q.empty()){
		int u = q.top().v;
		double uw = q.top().w;
		q.pop();
		if (uw > d[u])	continue;
		for (auto [v,w] : g[u]){
		// for (auto i : g[u]){
		// 	int v = i.v;double w = i.w;
			if (u == x && v == y || u == y && v == x)	continue;
			if (d[u] + w < d[v]){
				if (!x && !y)	fa[v] = u;
				d[v] = d[u] + w;
				q.push({v,d[v]});
			}
		}
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		cin >> a[i].v >> a[i].w;
	}
	for (int i = 1;i <= m;i++){
		int u,v;
		cin >> u >> v;
		double w = calc(u,v);
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	djkstr(0,0);
	// for (int i = 1;i <= n;i++)	printf("%.2f ",d[i]);
	double ans = INF;
	for (int i = n;i != 1;i = fa[i]){
		// cout << i << '\n';
		djkstr(i,fa[i]);
		ans = min(ans,d[n]);
	}
	if (ans == INF)	cout << -1;
	else	printf("%.2f",ans);
	return 0;
}