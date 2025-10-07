#include <bits/stdc++.h>
using namespace std;
const int N = 225;
struct point{
	int v,w;
}; 
bool operator< (point b,point c){
	return b.w < c.w;
}
vector<point> g[N];
int mony[N];
int n,m1,d,m2,s;
bool f[N],p[N][N];
bool check_path(int u,int v){
	for (int i = 1;i <= n;i++){
		if (p[u][i] != p[v][i])	return 0;
	}
	return 1;
}
bool bfs(int s){
	priority_queue<point> q;
	mony[s] = d;
	q.push({s,0});
	while (!q.empty()){
		int u = q.top().v,uw = q.top().w;
		q.pop();
		if (f[u])	continue;
		f[u] = 1;
		p[u][u] = 1;
		for (auto i : g[u]){
			int v = i.v,w = i.w;
			if (mony[u] + w >= mony[v]){
//				printf("%d %d %d+%d=%d %d\n",u,v,mony[u],w,mony[u] + w,mony[v]);
				if (!check_path(u,v)){
					f[v] = 0;
					for (int i = 1;i <= n;i++){
						p[v][i] = p[u][i];
					}
					p[v][u] = 1;
					mony[v] = mony[u] + w;
					q.push({v,mony[u] + w});
				}else{
					return 1;
				}
			}
		}
	}
	return 0;
}
int main(int argc, char **argv){
#ifdef LOCAL
	freopen("A.in","r",stdin);
#endif 
	cin >> d >> m1 >> n >> m2 >> s;
	for (int i = 1;i <= m1;i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back({v,d});
	} 
	for (int i = 1;i <= m2;i++){
		int u,v,w;
		cin >> u >> v >> w;
		g[u].push_back({v,d - w});
	}
	if (bfs(s)){
		cout << -1;
		return 0;
	}
	int mx = 0;
	for (int i = 1;i <= n;i++){
		mx = max(mx,mony[i]);
	}
	cout << mx;
	return 0;
}