#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 15;
ll b[N],p[N] = {1},a[N] = {0};
/*
b[i]：0 ~ 10^(i+1)-1 间每个数码出现次数（包括前导零）
p[i]：10^i
*/
void init(){
	for (int i = 1;i < N;i++){
		p[i] = p[i - 1] * 10;
		b[i] = b[i - 1] * 10 + p[i - 1];
		// b[i] = i * p[i - 1];
	}
}
void solve(ll x){
	ll t[N];
	copy(begin(a),end(a),begin(t));
	memset(a,0,sizeof a);

	int len = 0,num[N] = {0};
	while (x){
		num[++len] = x % 10;
		x /= 10;
	}

	// 设 x=2617
	for (int i = len;i > 0;i--){	// 以 i=n 为例
		for (int j = 0;j <= 9;j++){
			// j 小于 2 的都有 10^3（10^(i-1)）次
			if (j < num[i])	a[j] += p[i - 1];
			// 无论 j 是什么，它在第 3（i-1）位一定是满的
			a[j] += num[i] * b[i - 1];
		}
		// 2（num[i]）的出现次数是 618（记得算 2000）次
		ll num_10 = 0;
		for (int j = i - 1;j > 0;j--){
			num_10 *= 10;
			num_10 += num[j];
		}
		a[num[i]] += num_10 + 1;
		// 减去 10^3（10^(i-1)）个 0（0000~0999）
		a[0] -= p[i - 1];
	}

	for (int i = 0;i <= 9;i++){
		a[i] -= t[i];
	}
}
int main(int argc, char **argv){
	init();
	ll A,B;
	cin >> A >> B;
	solve(A - 1);
	solve(B);
	for (int i = 0;i <= 9;i++){
		cout << a[i] << ' ';
	}
	return 0;
}