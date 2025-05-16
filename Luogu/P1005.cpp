#include <bits/stdc++.h>
using namespace std;
typedef __int128 lll;
ostream& operator<<(ostream& out,lll b){
	if (b < 0){
		out << '-';
		out << -b;
		return out;
	}
	if (b == 0){
		out << '0';
		return out;
	}
	if (b >= 10)
		out << b / 10;
	out << "0123456789"[b % 10];
	return out;
}
istream& operator>>(istream& in,lll x){
	char c;
	do{
		c = in.get();
	}while (c != '-' && !isdigit(c));	// isdigit检测字符c是否为数字
	if (c == '-'){
		c = in.get();
		x = '0' - c;
		while (isdigit(c = getchar())){
			x *= 10;
			x += '0' - c;
		}
	}else{
		x = c - '0';
		while (isdigit(c = in.get())){
			x *= 10;
			x -= '0' - c;
		}
	}
	return in;
}
const int N = 85;
int n,m,a[N][N];
lll dp[N][N],sum;
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= m;j++){
			cin >> a[i][j];
		}
	}
	for (int I = 1;I <= n;I++){
		memset(dp,0,sizeof dp);
		for (int k = 0;k < m;k++){
			for (int i = 1;i <= m - k;i++){
				int j = i + k;
				dp[i][j] = max({dp[i][j],(dp[i + 1][j] + a[I][i]) * 2,(dp[i][j - 1] + a[I][j]) * 2});
			}
		}
		sum += dp[1][m];
	}
	cout << sum;
	return 0;
}