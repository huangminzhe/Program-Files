#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int a[N * 2],dp[N * 2][N * 2],mx;
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		a[n + i] = a[i];
	}
	a[2 * n + 1] = a[1];
	for (int i = 1;i <= 2 * n - 1;i++){
		// dp[i][i + 1] = a[i] * a[i + 1] * a[i + 2];
	}
	for (int k = 2;k <= n;k++){
		for (int i = 1;i <= n * 2 - k;i++){
			int j = i + k;
			for (int h = i + 1;h < j;h++){
				// dp[i][j] = max(dp[i][j],dp[i][h] + dp[h + 1][j] + a[i] * a[h + 1] * a[j + 1]);
				dp[i][j] = max(dp[i][j],dp[i][h] + dp[h][j] + a[i] * a[h] * a[j]);
			}
			mx = max(mx,dp[i][j]);
			// printf("%d %d %d\n",i,j,dp[i][j]);
		}
	}
	cout << mx;
	return 0;
}
/*
dp[i][i]=0;
dp[i][i+1]=max(dp[i][i+1],
			   a[i]*a[i+1]*a[i+2]);
dp[i][i+2]=max(dp[i][i+2],
			   dp[i][i+1]+dp[i+2][i+2]+a[i]*a[i+2]*a[i+3]);
dp[i][i+3]=max(dp[i][i+3],
			   dp[i][i+1]+dp[i+2][i+3]+a[i]*a[i+2]*a[i+4],
			   dp[i][i+2]+dp[i+3][i+3]+a[i]*a[i+3]*a[i+4]);
*/