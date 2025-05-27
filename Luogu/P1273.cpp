#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e3 + 5;
int n,m,a[N],dfsx[N],sz[N],tot,dp[N][N];
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
			int v,w;
			cin >> v >> a[i];
			g[i].push_back(v);
		}
	}
	for (int i = n - m + 1;i <= n;i++){
		cin >> a[i];
	}
	init(1);
	for (int i = n;i >= 1;i--){
		for (int j = 1;j <= m;j++){
			if (i >= n - m + 1){
				dp[i][j] = max(dp[i + sz[dfsx[i]]][j],dp[i + 1][j - 1] + a[dfsx[i]]);
			}else{
				dp[i][j] = max(dp[i + sz[dfsx[i]]][j],dp[i + 1][j - 1] - a[dfsx[i]]);
			}
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