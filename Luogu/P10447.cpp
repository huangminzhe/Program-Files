#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 25,M = 1 << 20;
int d[N][N],dp[M][N];
int lowbit(int x){
	return x & -x;
}
int lowwei(int x){
	return __builtin_ffs(x) - 1;
}
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			cin >> d[i][j];
		}
	}
	for (int k = 1;k < 1 << n;k++){	// 枚状态
		if (!(k & 1))	continue;
		for (int i = k,si = lowwei(k);i;i -= lowbit(i),si = lowwei(i)){	// 枚当前点
			for (int j = 1;j <= n;j <<= 1){	// 枚下一个点
				if ((k | j) == k)	continue;
				dp[k | j][lowwei(j)] = min(dp[k | j][lowwei(j)],dp[k][si] + d[si][lowwei(j)]);
			}
		}
	}
	cout << dp[(1 << n) - 1][n];
	return 0;
}