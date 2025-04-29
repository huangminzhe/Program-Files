#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int a[N],win[] = {1,2,0},mx,dp[N][25][3];
int main(int argc, char **argv){
	int n,k;
	cin >> n >> k;
	for (int i = 1;i <= n;i++){
		char c;
		cin >> c;
		if (c == 'S')	a[i] = 2;
		else if (c == 'P')	a[i] = 1;
	}
	memset(dp,-1,sizeof(dp));
	for (int i = 0;i < 3;i++)
		dp[0][k][i] = 0;
	for (int i = 1;i <= n;i++){	// 第几轮
		for (int j = k;j >= 0;j--){	// 还剩几次换的机会
			for (int h = 0;h < 3;h++){	// 上次手势
				if (dp[i - 1][j][h] == -1)	continue;
				bool add = h == win[a[i]];
				dp[i][j][h] = max(dp[i][j][h],dp[i - 1][j][h] + add);
				if (j > 0)	dp[i][j - 1][win[a[i]]] = max(dp[i][j - 1][win[a[i]]],dp[i - 1][j][h] + 1);
			}
		}
	}
	for (int i = 0;i <= k;i++)
		for (int j = 0;j < 3;j++)
			mx = max(mx,dp[n][i][j]);
	// for (int i = 1;i <= n;i++){
	// 	for (int j = 0;j <= k;j++){
	// 		printf("%d ",dp[i][j]);
	// 	}
	// 	cout << '\n';
	// }
	cout << mx;
	return 0;
}