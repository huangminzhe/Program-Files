#include <bits/stdc++.h>
using namespace std;
const int N = 6e3 + 5;
int a[N],fa[N],dp[N][2],root;
vector<int> g[N];
void dfs(int u){
	dp[u][1] = a[u];
	for (int v : g[u]){
		dfs(v);
		dp[u][0] += max(dp[v][0],dp[v][1]);
		dp[u][1] += dp[v][0];
	}
}
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	for (int i = 1;i < n;i++){
		int e,f;
		cin >> e >> f;
		fa[e] = f;
		g[f].push_back(e);
	}
	for (int i = 1;i <= n;i++){
		if (!fa[i]){
			root = i;
			break;
		}
	}
	dfs(root);
	cout << max(dp[root][0],dp[root][1]);
	return 0;
}