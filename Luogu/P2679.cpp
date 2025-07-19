#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e3 + 5,M = 205,MOD = 1e9 + 7;
int n,m,k;
ll dp[2][M][M][2];
// 	  ^ 行太大了，滚它
bool zt;
// zt 表示当前行，!zt 表示上一行
string a,b;
int main(int argc, char **argv){
	cin >> n >> m >> k >> a >> b;
	for (int i = 1;i <= n;i++){
		dp[zt][0][0][0] = 1;
		zt = !zt;
		for (int j = 1;j <= m;j++){
			for (int h = 1;h <= k;h++){
				int si = i - 1,sj = j - 1;
				if (a[si] == b[sj])
					dp[zt][j][h][1] = (dp[!zt][j - 1][h - 1][0] + dp[!zt][j - 1][h - 1][1] + dp[!zt][j - 1][h][1]) % MOD;
				else
					dp[zt][j][h][1] = 0;
				dp[zt][j][h][0] = (dp[!zt][j][h][0] + dp[!zt][j][h][1]) % MOD;
			}
		}
	}
	cout << (dp[zt][m][k][0] + dp[zt][m][k][1]) % MOD;
	return 0;
}