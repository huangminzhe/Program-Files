#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5,MOD = 19650827;
int a[N],dp[N][N][2];
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		dp[i][i][0] = 1;
	}
	for (int k = 1;k < n;k++){
		for (int i = 1;i <= n - k;i++){
			int j = i + k;
			(dp[i][j][0] += (a[i] < a[i + 1]?dp[i + 1][j][0]:0) + (a[i] < a[j]?dp[i + 1][j][1]:0)) %= MOD;
			(dp[i][j][1] += (a[j] > a[i]?dp[i][j - 1][0]:0) + (a[j] > a[j - 1]?dp[i][j - 1][1]:0)) %= MOD;
		}
	}
	cout << (dp[1][n][0] + dp[1][n][1]) % MOD;
	return 0;
}