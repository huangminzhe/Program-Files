#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 25,M = 1 << 20;
int d[N][N],dp[M][N];
int lowbit(int x){
	return x & -x;
}
int lowwei(int x){
	return __builtin_ffs(x);
}
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			cin >> d[i][j];
		}
	}
	memset(dp,0x3f,sizeof dp);
	dp[1][1] = 0;
	for (int k = 1;k < 1 << n;k++){	// 枚状态
		if (!(k & 1))	continue;
		for (int i = k,si = lowwei(k);i;i -= lowbit(i),si = lowwei(i)){	// 枚当前点
			for (int sj = 1;sj <= n;sj++){	// 枚下一个点
				int j = 1 << sj - 1;
				if ((k | j) == k)	continue;
				dp[k | j][sj] = min(dp[k | j][sj],dp[k][si] + d[si][sj]);
			}
		}
	}
	int mn = dp[(1 << n) - 1][1] + d[1][1];
	for (int i = 2;i <= n;i++){
		mn = min(mn,dp[(1 << n) - 1][i] + d[i][1]);
	}
	cout << mn;
	return 0;
}