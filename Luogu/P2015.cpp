#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N = 105;
int n,q;
vector<pii> a[N];
int ls[N],rs[N],lse[N],rse[N];
int dp[N][N];
void build(int u,int f){
	for (pii v : a[u]){
		int vf = v.first,vs = v.second;
		if (vf == f)	continue;
		else if (ls[u])	rs[u] = vf,rse[u] = vs,build(vf,u);
		else	ls[u] = vf,lse[u] = vs,build(vf,u);
	}
}
int dfs(int u,int edges){
	if (!edges || !ls[u] && !rs[u])	return 0;
	if (dp[u][edges])	return dp[u][edges];
	dp[u][edges] = max(dfs(ls[u],edges - 1) + lse[u],dfs(rs[u],edges - 1) + rse[u]);
	for (int i = 0;i <= edges - 2;i++){
		dp[u][edges] = max(dp[u][edges],dfs(ls[u],i) + dfs(rs[u],edges - i - 2) + lse[u] + rse[u]);
	}
	return dp[u][edges];
}
int main(int argc, char **argv){
	cin >> n >> q;
	for (int i = 1;i < n;i++){
		int u,v,w;
		cin >> u >> v >> w;
		a[u].push_back({v,w});
		a[v].push_back({u,w});
	}
	build(1,0);
	cout << dfs(1,q);
	return 0;
}