#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 15,M = (1 << 12) + 5,MOD = 1e8;
int n,m,a[N];
bool f[M];
ll dp[N][M],ans;
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= m;j++){
			bool x;
			cin >> x;
			a[i] <<= 1;
			a[i] += x;
		}
	}
	for (int i = 0;i < 1 << m;i++){
		if (!(i & i >> 1) && !(i & i << 1))	f[i] = 1;
	}
	// 以下参考 P1896
	dp[0][0] = 1;
	for (int i = 1;i <= n;i++){
		for (int j1 = 0;j1 < 1 << m;j1++){
			if (!f[j1] || 
				(j1 | a[i]) != a[i])	continue;
			for (int j2 = 0;j2 < 1 << m;j2++){
				if (!f[j2] || 
					(j2 | a[i - 1]) != a[i - 1] || 
					j1 & j2)	continue;
				dp[i][j1] += dp[i - 1][j2];
			}
		}
	}
	for (int i = 0;i < 1 << m;i++)
		if (f[i])
			ans += dp[n][i];
	cout << ans % MOD;
	return 0;
}