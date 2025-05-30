#include <bits/stdc++.h>
using namespace std;
const int N = 1.5e3 + 5,INF = 0x7fffffff;
int a[N],dp[N][3],root,fa[N];
/*
dp[i][0]：自己看自己
dp[i][1]：儿子看自己
dp[i][2]：爸爸看自己
*/
vector<int> g[N];
void dfs(int u){
	dp[u][0] = a[u];
	bool f = 1;
	int mn = INF;
	for (int v : g[u]){
		dfs(v);
		dp[u][0] += min({dp[v][0],dp[v][1],dp[v][2]});
		dp[u][1] += min(dp[v][0],dp[v][1]);
		if (dp[v][0] <= dp[v][1])	f = 0;
		else	mn = min(mn,dp[v][0] - dp[v][1]);
		dp[u][2] += min(dp[v][0],dp[v][1]);
	}
	if (f)	dp[u][1] += mn;
}
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int I = 1;I <= n;I++){
		int i;
		cin >> i;
		cin >> a[i];
		int k;
		cin >> k;
		for (int j = 1;j <= k;j++){
			int x;
			cin >> x;
			g[i].push_back(x);
			fa[x] = i;
		}
	}
	for (int i = 1;i <= n;i++){
		if (!fa[i])	root = i;
	}
	dfs(root);
	cout << min(dp[root][0],dp[root][1]);
	return 0;
}