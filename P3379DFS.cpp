#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int n,m,s;
vector<int> a[N];
int dep[N],fa[N],d[N],dfn[N],t;	// 层数；父亲；DFS序；时间戳；时间总和
void dfs(int u){
	dfn[u] = ++t,d[t] = u;
	for (int v : a[u]){
		if (v != fa[u]){
			dep[v] = dep[u] + 1;
			fa[v] = u;
			dfs(v);
		}
	}
}
int lca(int u,int v){
	// 确保u在v左边（或上面）
	if (dfn[u] > dfn[v])	swap(u,v);

	int v_ = v;
	for (int i = dfn[u] + 1;i <= dfn[v];i++)
		if (dep[d[i]] < dep[v_])	v_ = d[i];
	return fa[v_];
}
int main(int argc, char **argv){
	cin >> n >> m >> s;
	int u,v;
	for (int i = 1;i < n;i++){
		scanf("%d %d",&u,&v);
		a[u].push_back(v);
		a[v].push_back(u);
	}
	dep[s] = 1;
	dfs(s);
	while (m--){
		scanf("%d %d",&u,&v);
		printf("%d\n",lca(u,v));
	}
	return 0;
}