#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 15,M = 2.5e3 + 5;
int n,k;
ll cnt[M];	// 第 i 种状态中有几个国王（1）
bool f[M];	// 第 i 种状态是否合法（本行内）
ll dp[N][M][N * N];	// 第 i 行用了 k 个国王状态为 j
ll ans;
int lowbit(int x){
	return x & -x;
}
int popcount(int x){
	int res = 0;
	for (;x;x = lowbit(x))
		res++;
	return res;
}
int main(int argc, char **argv){
	cin >> n >> k;
	for (int i = 0;i < 1 << n;i++){
		cnt[i] = __builtin_popcount(i);
		if (!((i >> 1 | i << 1) & i))	f[i] = 1;
	}
	dp[0][0][0] = 1;	// 空棋盘算 1 个方案
	for (int i = 1;i <= n;i++){	// 枚举行
		for (int j1 = 0;j1 < 1 << n;j1++){	// 枚举当前状态
			if (!f[j1])	continue;
			for (int j2 = 0;j2 < 1 << n;j2++){	// 枚举上一行状态
				if (!f[j2])	continue;
				if (!((j2 >> 1 | j2 | j2 << 1) & j1))
					for (int h = i;h >= cnt[i];h--)
						dp[i][j1][h] += dp[i - 1][j2][h - cnt[i]];
			}
		}
	}
	for (int i = 0;i < 1 << n;i++)
		if (f[i])
			ans += dp[n][i][k];
	cout << ans;
	return 0;
}