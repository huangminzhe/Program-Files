#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1.6e4 + 5,INF = 0x7fffffff;
int n,dp[N],a[N],mx = -INF;
vector<int> g[N];
void dfs(int u,int fa){
	dp[u] = a[u];
	for (int v : g[u]){
		if (v == fa)	continue;
		dfs(v,u);
		dp[u] += max(dp[v],0);
	}
}
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	for (int i = 1;i < n;i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	for (int i = 1;i <= n;i++){
		mx = max(mx,dp[i]);
	}
	cout << mx;
	return 0;
}