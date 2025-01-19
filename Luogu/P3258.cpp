#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5,LOG2N = 20;
int p[N];	// 指定路径
vector<int> a[N];
int fa[N],st[N][LOG2N],dfn[N],t,d[N],dep[N];
void dfs(int u){
	dfn[u] = ++t,d[t] = u,st[t][0] = fa[u];
	for (int v : a[u]){
		if (v != fa[u]){
			dep[v] = dep[u] + 1;
			fa[v] = u;
			dfs(v);
		}
	}
}
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		scanf("%d",p + i);
	}
	for (int i = 1;i < n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		a[u].emplace_back(v);
		a[v].emplace_back(u);
	}
	dfs(1);
	return 0;
}