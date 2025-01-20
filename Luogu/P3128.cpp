#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5,LOG2N = 20;
int n,m;
vector<int> a[N];
int fa[N],st[N][LOG2N],Log2[N],dfn[N],t,d[N],dep[N];
int b[N],sz[N],mx;
inline int get(int x,int y){return dep[x] < dep[y]?x:y;}
void dfs(int u){
	dfn[u] = ++t,d[t] = u,st[t][0] = fa[u],sz[u] = 1;
	for (int v : a[u]){
		if (v != fa[u]){
			dep[v] = dep[u] + 1;
			fa[v] = u;
			dfs(v);
			sz[u] += sz[v];
		}
	}
}
void init(int s){
	dep[s] = 1;
	dfs(s);
	
	for (int i = 2;i <= n;i++)
		Log2[i] = Log2[i >> 1] + 1;
	for (int j = 1;j <= Log2[n];j++)
		for (int i = 1;i <= n - (1 << j) + 1;i++)
			st[i][j] = get(st[i][j - 1],st[i + (1 << (j - 1))][j - 1]);
}
int lca(int u,int v){
	if (dfn[u] > dfn[v])	swap(u,v);

	if (u == v)	return u;
	int k = Log2[dfn[v] - dfn[u]];
	return get(st[dfn[u] + 1][k],st[dfn[v] - (1 << k) + 1][k]);
}
void diff(int u){
	for (int v : a[u]){
		if (v != fa[u]){
			diff(v);
			b[u] += b[v];
		}
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i < n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		a[u].push_back(v);
		a[v].push_back(u);
	}
	init(1);
	for (int i = 1;i <= m;i++){
		int s,t;
		cin >> s >> t;
		int l = lca(s,t);
		b[s]++;
		b[t]++;
		b[l]--;
		b[fa[l]]--;
	}
	diff(1);
	for (int i = 1;i <= n;i++){
		mx = max(mx,b[i]);
	}
	cout << mx;
	return 0;
}