#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 15,M = 1 << 12;
int n,m;
ll dp[N][M];
bool check(int x){
	int cnt = 0;
	x |= 1 << m;
	while (x){
		if (x & 1){
			if (cnt & 1)	return 0;
			cnt = 0;
		}else	cnt++;
		x >>= 1;
	}
	return 1;
}
int main(int argc, char **argv){
	cin >> n >> m;
	while (n || m){
		if (n * m & 1){
			cout << "0\n";
			cin >> n >> m;
			continue;
		}
		memset(dp,0,sizeof dp);
		
		for (int i = 0;i < 1 << m;i++){
			if (check(i))	dp[1][i] = 1;
		}
		for (int i = 2;i <= n;i++){
			for (int j1 = 0;j1 < 1 << m;j1++){	// 当前行
				for (int j2 = 0;j2 < 1 << m;j2++){	// 上一行
					if (j1 & j2 || 
						!check(j1 | j2))	continue;
					dp[i][j1] += dp[i - 1][j2];
				}
			}
		}
		cout << dp[n][0] << '\n';
		cin >> n >> m;
	}
	return 0;
}