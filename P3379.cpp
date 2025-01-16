#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5,LOG2N = 20;
int n,m,s;
vector<int> a[N];
int dep[N],fa[N][LOG2N];	// 层数；祖先ST表
void dfs(int u){
	for (int v : a[u]){
		if (v != fa[u][0]){
			dep[v] = dep[u] + 1;
			fa[v][0] = u;
			dfs(v);
		}
	}
}
void init(){
	for (int j = 1;j <= 18;j++)
		for (int i = 1;i <= n;i++)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
	// fa[i][j - 1]是距离i 2^(j-1)的祖先，fa[fa[i][j - 1]][j - 1]就是距离i 2^j（2^(j-1)+2^(j-1)）的祖先
}
int lca(int u,int v){
	// 确保u更深
	if (dep[u] < dep[v])	swap(u,v);
	for (int i = 18;i >= 0;i--)
		if (dep[fa[u][i]] >= dep[v])
			u = fa[u][i];
	// 二进制升高u，一定能升到和v一样的高度
	if (u == v)	return u;
	for (int i = 18;i >= 0;i--)
		if (fa[u][i] != fa[v][i])
			u = fa[u][i],v = fa[v][i];
	// 现在u和v的父亲是一样的了，返回父亲
	return fa[u][0];
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
	init();
	while (m--){
		scanf("%d %d",&u,&v);
		printf("%d\n",lca(u,v));
	}
	return 0;
}