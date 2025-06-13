#include <bits/stdc++.h>
using namespace std;
const int N = 15,M = 105;
int b[N][N][M];	// i位数，j开头，%mod=k
int md(int x,int y){
	return (x % y < 0?x % y + y:x % y);
}
void init(int mod){
	memset(b,0,sizeof b);

	for (int i = 0;i <= 9;i++)
		b[1][i][i % mod] = 1;
	for (int i = 2;i <= 10;i++)	// 位数
		for (int j = 0;j <= 9;j++)	// 当前位数字
			for (int k = 0;k < mod;k++)	// %mod=
				for (int h = 0;h <= 9;h++)	// 上一位数字
					b[i][j][k] += b[i - 1][h][md(k - j,mod)];
}
int solve(int x,int mod){
	int len = 0,num[N] = {0};
	while (x){
		num[++len] = x % 10;
		x /= 10;
	}

	int ans = 0,o = 0;
	for (int i = len + 1;i > 0;i--){
		for (int j = 0;j < num[i];j++){
			ans += b[i][j][md(-o,mod)];
		}
		o = (o + num[i]) % mod;
		if (i == 1 && o % mod == 0)	ans++;
	}
	return ans;
}
int main(int argc, char **argv){
	// freopen("d:\\Users\\Administrator\\Downloads\\test1.ans","w",stdout);
	int A,B,mod;
	while (cin >> A >> B >> mod){
		init(mod);
		cout << solve(B,mod) - solve(A - 1,mod) << '\n';
	}
	return 0;
}