#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 35;
int k,b,c[N][N];
void init(){
	for (int i = 0;i < N;i++){
		c[i][0] = 1;
		c[i][i] = 1;
	}
	for (int i = 2;i < N - 1;i++)
		for (int j = 1;j < i;j++)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
}
int solve(int x){
	int len = 0,num[N] = {0};
	while (x){
		num[++len] = x % b;
		x /= b;
	}

	int cnt = 0;
	ll ans = 0;
	for (int i = len;i > 0;i--){
		if (num[i] == 1){
			if (i > k - cnt)	ans += c[i - 1][k - cnt];
			cnt++;
			if (cnt > k)	break;
		}else if (num[i] > 1){
			ans += c[i][k - cnt];
			break;
		}

		if (i == 1 && cnt == k)	ans++;
	}
	return ans;
}
int main(int argc, char **argv){
	int A,B;
	cin >> A >> B;
	cin >> k >> b;
	init();
	cout << solve(B) - solve(A - 1);
	return 0;
}