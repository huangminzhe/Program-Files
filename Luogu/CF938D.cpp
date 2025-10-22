#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5,M = 2e5 + 5;
const ll INF = LLONG_MAX;
struct edge{
	int v;
	ll w;
	int nxt;
}edges[(M << 1) + N];
int tot,head[N];
void add(int u,int v,ll w){
	edges[++tot] = {v,w,head[u]};
	head[u] = tot;
}

struct point{
	int v;
	ll w;
};
bool operator< (point b,point c){
	return b.w > c.w;
}
int n,m;
ll d[N];
bool f[N];
void djkstr(int s){
	fill(d + 1,d + n + 1,INF);
	priority_queue<point> q;
	d[s] = 0;
	q.push({s,0});
	while (!q.empty()){
		int u = q.top().v;
		q.pop();
		if (f[u])	continue;
		f[u] = 1;
		for (int i = head[u];i;i = edges[i].nxt){
			int v = edges[i].v;ll w = edges[i].w;
			if (d[u] + w < d[v]){
				d[v] = d[u] + w;
				q.push({v,d[v]});
			}
		}
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		int u,v;ll w;
		cin >> u >> v >> w;
		add(u,v,w * 2);
		add(v,u,w * 2);
	}
	for (int i = 1;i <= n;i++){
		ll x;
		cin >> x;
		add(0,i,x);
	}
	djkstr(0);
	for (int i = 1;i <= n;i++){
		cout << d[i] << ' ';
	}
	return 0;
}