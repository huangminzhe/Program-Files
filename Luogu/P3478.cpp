#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
int n,sz[N];
ll dp[N];
vector<int> g[N];
void init(int u,int fa){
	sz[u] = 1;
	for (int v : g[u]){
		if (v == fa)	continue;
		init(v,u);
		sz[u] += sz[v];
		dp[u] += dp[v];
	}
	dp[u] += sz[u] - 1;
}
void dfs(int u,int fa){
	dp[u] = dp[fa] + n - 2 * sz[u];
	// dp[u] + (dp[fa] - dp[u] - sz[u]) + (n - sz[u])
	for (int v : g[u]){
		if (v == fa)	continue;
		dfs(v,u);
	}
}
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i < n;i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	init(1,0);
	dfs(1,0);
	cout << max_element(dp + 1,dp + n + 1) - dp;
	return 0;
}