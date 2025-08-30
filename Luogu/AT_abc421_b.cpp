#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[105];
int main(int argc, char **argv){
	cin >> a[1] >> a[2];
	for (int i = 3;i <= 10;i++){
		ll t = a[i - 1] + a[i - 2];
		// printf("%lld ",t);
		while (t){
			a[i] *= 10;
			a[i] += t % 10;
			t /= 10;
		}
		// printf("%lld\n",a[i]);
	}
	cout << a[10];
	return 0;
}