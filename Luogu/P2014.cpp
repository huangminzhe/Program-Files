#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 305;
int n,m,tot;
int pre[N],a[N],dp[N][N],sz[N],dfsx[N];
vector<int> g[N];
void init(int u){
	sz[u] = 1,dfsx[tot++] = u;
	for (int v : g[u]){
		init(v);
		sz[u] += sz[v];
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		cin >> pre[i] >> a[i];
		g[pre[i]].push_back(i);
	}
	init(0);
	for (int i = n;i >= 0;i--){
		for (int j = 1;j <= m;j++){
			dp[i][j] = max(dp[i + sz[dfsx[n]]][j],dp[i + 1][j - 1] + a[dfsx[i]]);
		}
	}
	cout << dp[0][m] - 1;	// 虚点（0）不算
	return 0;
}