#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 15;
int b[N][N];	// b[][]：j开头i位数的不降数个数
void init(){
	for (int i = 0;i <= 9;i++)
		b[1][i] = 1;
	for (int i = 2;i <= 10;i++){
		for (int j = 0;j <= 9;j++){
			for (int k = j;k <= 9;k++){
				b[i][j] += b[i - 1][k];
			}
		}
	}
}
ll solve(int x){
	if (!x)	return 1;

	int len = 0,s[N] = {0};
	while (x){
		s[++len] = x % 10;
		x /= 10;
	}

	int o = 0;	// 上一位
	ll ans = 0;
	for (int i = len;i > 0;i--){
		int n = s[i];
		for (int j = o;j < n;j++)
			ans += b[i][j];
		if (o > n)	break;
		o = n;
		if (i == 1)	ans++;	// 算上边界
	}
	return ans;
}
int main(int argc, char **argv){
	ios::sync_with_stdio(0);
	cin.tie(0);
	init();
	int l,r;
	while (cin >> l >> r){
		cout << solve(r) - solve(l - 1) << '\n';
	}
	return 0;
}