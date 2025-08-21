#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll sum;
int main(int argc, char **argv){
// 	freopen("trol.in","r",stdin);
// #ifndef LOCAL
// 	freopen("trol.out","w",stdout);
// #endif
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		sum = 0;
		ll l,r;
		cin >> l >> r;
		sum += (r - l + 1) / 9 * 45;
		for (ll i = l + (r - l + 1) / 9 * 9;i <= r;i++){
			sum += (i - 1) % 9 + 1;
		}
		cout << sum << '\n';
	}
	return 0;
}

