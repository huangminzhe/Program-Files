#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N = 2e4 + 5,M = 1e5 + 5;
int n,m,c[N],edges[M];
vector<pii> g[N];
bool dfs(int u,int x){
	// cout << u << ' ' << x << '\n';
	for (auto [v,w] : g[u]){
		if (w < x)	continue;
		if (c[v] == c[u])	return 1;
		if (c[v])	continue;
		c[v] = (c[u] & 1) + 1;
		if (dfs(v,x))	return 1;
	}
	return 0;
}
bool check(int x){
	memset(c,0,sizeof c);
	for (int i = 1;i <= n;i++){
		if (!c[i]){
			c[i] = 1;
			if (dfs(i,x))	return 1;
		}
	}
	return 0;
}
int main(int argc, char **argv){
	// freopen("C:\\Users\\Administrator\\Desktop\\P1525_2.in","r",stdin);
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		int u,v,w;
		cin >> u >> v >> w;
		g[u].push_back({v,w});
		g[v].push_back({u,w});
		edges[i] = w;
	}
	sort(edges,edges + m + 1);
	int l = 1,r = m,ans = 0;
	int mid = l + r >> 1;
	while (l <= r){
		mid = l + r >> 1;
		// printf("%d %d\n",l,r);
		if (check(edges[mid]))	l = mid + 1;
		else	r = mid - 1,ans = edges[mid - 1];
	}
	cout << ans;
	return 0;
}