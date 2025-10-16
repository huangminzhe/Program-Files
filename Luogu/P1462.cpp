#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e4 + 5;
const ll INF = 0x7fffffffffffffff;
struct point{
	int v;
	ll w;
};
bool operator< (point b,point c){
	return b.w > c.w;
}
vector<point> g[N];
int n,m,b,a[N],mx;
ll d[N];
bool f[N];
bool check(int x){
	fill(d + 1,d + n + 1,INF);
	fill(f + 1,f + n + 1,0);
	if (a[1] > x)	return 0;
	priority_queue<point> q;
	d[1] = 0;
	q.push({1,0});
	while (!q.empty()){
		int u = q.top().v;
		q.pop();
		if (f[u])	continue;
		f[u] = 1;
		for (auto [v,w] : g[u]){
		// for (auto i : g[u]){
		// 	int v = i.v,w = i.w;
			if (a[v] > x)	continue;
			if (d[u] + w < d[v]){
				d[v] = d[u] + w;
				q.push({v,d[v]});
			}
		}
	}
	return d[n] <= b;
}
int main(int argc, char **argv){
	cin >> n >> m >> b;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		mx = max(mx,a[i]);
	}
	for (int i = 1;i <= m;i++){
		int u,v,w;
		cin >> u >> v >> w;
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	int l = 0,r = mx;
	while (l < r){
		int mid = l + r >> 1;
		if (check(mid))	r = mid;
		else	l = mid + 1;
	}
	if (!check(mx)){
		cout << "AFK";
		return 0;
	}
	cout << l;
	return 0;
}