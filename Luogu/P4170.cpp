#include <bits/stdc++.h>
using namespace std;
const int N = 55;
string s;
int n,dp[N][N];
int main(int argc, char **argv){
	cin >> s;
	n = s.size();
	for (int k = 0;k < n;k++){
		for (int i = 1;i <= n - k;i++){
			int j = i + k;
			int si = i - 1,sj = j - 1;
			if (i == j)	dp[i][j] = 1;
			else if (s[si] == s[sj])
				dp[i][j] = dp[i][j - 1];
			else{
				dp[i][j] = n;
				for (int h = i;h < j;h++){
					dp[i][j] = min(dp[i][j],dp[i][h] + dp[h + 1][j]);
				}
			}
		}
	}
	cout << dp[1][n];
	return 0;
}