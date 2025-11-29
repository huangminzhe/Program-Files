#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll cnt;
map<ll,bool> f;
int main(int argc, char **argv){
	ll n;
	cin >> n;
	for (ll i = 1;i <= 60;i++){
		ll a = 1LL << i;
		if (a > n)	break;
		for (ll j = 1;a * j * j <= n;j++){
			ll b = j * j;
			if (a * b <= n && !f[a * b])	cnt++,f[a * b] = 1;
		}
	}
	cout << cnt;
	return 0;
}