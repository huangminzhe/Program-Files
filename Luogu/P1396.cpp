#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5,INF = 0x3fffffff;
struct point{
	int v,w;
};
bool operator< (point b,point c){
	return b.w > c.w;
}
int n,m,s,e,r,d[N];
vector<point> a[N];
bool f[N];
int main(int argc, char **argv){
    cin >> n >> m >> s >> e;
    for (int i = 1;i <= m;i++){
        int u,v,w;
        cin >> u >> v >> w;
		r = max(r,w);
        a[u].push_back({v,w});
		a[v].push_back({u,w});
    }

	fill(d + 1,d + n + 1,INF);
	priority_queue<point> q;
	q.push({s,0});
	d[s] = 0;
	while (!q.empty()){
		int u = q.top().v;
		q.pop();
		if (f[u])	continue;
		f[u] = 1;
		for (auto i : a[u]){
			int v = i.v,w = i.w;
			if (max(d[u],w) < d[v]){
				d[v] = max(d[u],w);
				q.push({v,max(d[u],w)});
			}
		}
	}
	cout << d[e];
}