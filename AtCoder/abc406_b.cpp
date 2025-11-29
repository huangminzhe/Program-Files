#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans = 1;
int main(int argc, char **argv){
	int n,k;
	cin >> n >> k;
	for (int i = 1;i <= n;i++){
		int x;
		cin >> x;
		ans *= x;
		if (ans < 0 || to_string(ans).size() > k)	ans = 1;
	}
	cout << ans;
	return 0;
}