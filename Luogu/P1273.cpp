#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N = 3e3 + 5,INF = 0x3fffffff;
int n,m,a[N] = {0},dfsx[N],sz[N],tot,dp[N][N],fa[N];
vector<int> g[N];
void init(int u){
	sz[u] = 1,dfsx[u] = ++tot;
	for (int v : g[u]){
		init(v);
		sz[u] += sz[v];
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n - m;i++){
		int k;
		cin >> k;
		for (int j = 1;j <= k;j++){
			int v;
			cin >> v >> fa[v];
			g[i].push_back(v);
		}
	}
	for (int i = n - m + 1;i <= n;i++){
		int x;
		cin >> x;
		a[i] = x;
	}
	init(1);
	for (int i = 1;i <= n + 1;i++)	// n+1是边界
		for (int j = 1;j <= m;j++)
			dp[i][j] = -INF;
	for (int i = n;i > 0;i--){
		for (int j = 1;j <= m;j++){
			// dp[i][j] = max(dp[i + sz[dfsx[i]]][j],dp[i + 1][j - (dfsx[i] >= n - m + 1?1:0)] + a[dfsx[i]] - fa[dfsx[i]]);
			if (dfsx[i] >= n - m + 1)	dp[i][j] = max(dp[i + 1][j],dp[i + 1][j - 1] + a[dfsx[i]] - fa[dfsx[i]]);
			else	dp[i][j] = max(dp[i + sz[dfsx[i]]][j],dp[i + 1][j] - fa[dfsx[i]]);
			// printf("%d %d %d %d %d\n",i,j,dp[i][j],dp[i + sz[dfsx[i]]][j],dp[i + 1][j - (dfsx[i] >= n - m + 1?1:0)] + a[dfsx[i]] - fa[dfsx[i]]);
		}
	}
	for (int i = m;i >= 0;i--){
		if (dp[1][i] >= 0){
			cout << i;
			return 0;
		}
	}
	return 0;
}