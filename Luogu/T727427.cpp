#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
ll r[N],c[N],s[N];
int main(int argc, char **argv){
	ll n,m;
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		cin >> r[i] >> c[i];
		s[i] = r[i] * c[i];
	}
	ll sum = 0;
	for (int i = 1;i <= n;i++){
		sum += s[i];
		if (sum >= m){
			cout << i * 2;
			return 0;
		}
	}
	return 0;
}