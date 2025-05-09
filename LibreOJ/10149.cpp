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
	if (b > 10)
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
const int N = 55;
int a[N];
lll dp[N][N];
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	for (int k = 2;k < n;k++){
		for (int i = 1;i <= n - k;i++){
			int j = i + k;
			dp[i][j] = dp[i][i + 1] + dp[i + 1][j] + a[i] * a[i + 1] * a[j];
			for (int h = i + 2;h < j;h++)
				dp[i][j] = min(dp[i][j],dp[i][h] + dp[h][j] + a[i] * a[h] * a[j]);
		}
	}
	cout << dp[1][n];
	return 0;
}