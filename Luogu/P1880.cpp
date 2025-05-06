#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int a[N * 2],dp[N][N],b[N * 2];
int main(int argc, char **argv){
	memset(dp,0x3f,sizeof(dp));
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		a[i + n] = a[i];
	}
	for (int i = 1;i <= n * 2;i++){
		b[i] = b[i - 1] + a[i];
		dp[i][i] = 0;
	}
	for (int k = 1;k < n;k++){
		for (int i = 1;i <= n - k;i++){
			int j = i + k;
			for (int k = i;k < j;k++){
				dp[i][j] = min(dp[i][j],dp[i][k] + dp[k + 1][j] + b[j] - b[i - 1]);
			}
		}
	}
	cout << dp[1][n];
	return 0;
}