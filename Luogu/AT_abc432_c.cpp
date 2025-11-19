#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n,s,b,a[N];
ll x[N],cnt;
int main(int argc, char **argv){
	cin >> n >> s >> b;
	for(int i = 1;i <= n;i++){
		cin >> a[i];
	}

	int b_s = b - s,yu = ll(a[1]) * s % b_s;
	for (int i = 2;i <= n;i++){
		if (ll(a[i]) * s % b_s != yu){
			cout << -1;
			return 0;
		}
	}

	for (int i = 1;i <= n;i++){
		x[i] = (ll(a[i]) * s - yu) / b_s;
	}

	ll l = x[1],r = x[1] + a[1];
	for (int i = 2;i <= n;i++){
		l = max(l,x[i]);
		r = min(r,x[i] + a[i]);
	}
	if (l > r){
		cout << -1;
		return 0;
	}

	for (int i = 1;i <= n;i++){
		cnt += r - x[i];
	}
	cout << cnt;
	return 0;
}