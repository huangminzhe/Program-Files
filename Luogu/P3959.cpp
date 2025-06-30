#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 15,M = 1 << 12,INF = 0x3f3f3f3f;
int n,m,a[N][N];
ll d[M][M],dp[N][M],ans;
int lowbit(int x){
	return x & -x;
}
int lowwei(int x){
	return __builtin_ffs(x);
}
int main(int argc, char **argv){
	cin >> n >> m;
	memset(a,0x3f,sizeof a);
	for (int i = 1;i <= m;i++){
		int u,v,w;
		cin >> u >> v >> w;
		a[u][v] = min(a[u][v],w);
		// a[u][v] = min(!a[u][v]?w:a[u][v],w);
		a[v][u] = a[u][v];
	}
	for (int i = 1;i < 1 << n;i++){
		int i_ = (1 << n) - 1 ^ i;	// i_ 是 i 的补集
		vector<int> zj;
		for (int j = i_;j;j = j - 1 & i_)	zj.push_back(j);
		reverse(zj.begin(),zj.end());
		for (int j : zj){	// j 是 i_ 的子集
			int mn = INF;
			int v = lowwei(j);
			for (int k = i;k;k -= lowbit(k)){
				int u = lowwei(k);
				mn = min(mn,a[u][v]);
			}
			d[i][j] = d[i][j - lowbit(j)] + mn;
		}
	}
	memset(dp,0x3f,sizeof dp);
	for (int i = 0;i < n;i++)
		dp[0][1 << i] = 0;
	ans = dp[0][(1 << n) - 1];
	for (int i = 1;i <= n;i++){
		for (int j = 1;j < 1 << n;j++){
			// if (!(j & 1 << i - 1))	continue;
			for (int k = j;k;k = k - 1 & j){
				if (k == j)	continue;
				dp[i][j] = min(dp[i][j],dp[i - 1][j - k] + i * d[j - k][k]);
			}
		}
		ans = min(ans,dp[i][(1 << n) - 1]);
	}
	cout << ans;
	return 0;
}