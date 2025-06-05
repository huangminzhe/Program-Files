#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 15;
ll dp[N][N];
void init(){
	for (int i = 0;i <= 9;i++)	dp[1][i] = 1;
	for (int i = 2;i < N;i++)	// 位数
		for (int j = 0;j <= 9;j++)	// 当前位数字
			for (int k = 0;k <= 9;k++)	// 上一位数字
				if (abs(j - k) >= 2)	dp[i][j] += dp[i - 1][k];
}
ll solve(int x){
	int len = 0,num[N] = {0};
	while (x){
		num[++len] = x % 10;
		x /= 10;
	}

	ll ans = 0;
	// 做法类似 P2602 数字计数
	for (int i = 1;i < num[len];i++)
		ans += dp[len][i];
	for (int i = 1;i < len;i++)
		for (int j = 1;j <= 9;j++)	// 最高位不能为 0
			ans += dp[i][j];
	for (int i = len - 1;i > 0;i--){
		for (int j = 0;j < num[i];j++){	// 枚举当前数字
			if (abs(j - num[i + 1]) >= 2)	ans += dp[i][j];
		}
		if (abs(num[i + 1] - num[i]) < 2)	break;
		if (i == 1)	ans++;
	}
	return ans;
}
int main(int argc, char **argv){
	int A,B;
	cin >> A >> B;
	init();
	cout << solve(B) - solve(A - 1);
	return 0;
}
// hack ink