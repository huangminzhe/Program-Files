#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5;
int n,m,a[N];
ll k,b[N];
int main(int argc, char **argv){
	cin >> n >> m >> k;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	sort(a + 1,a + n + 1);
	reverse(a + 1,a + n + 1);
	for (int i = 1;i <= n;i++){
		b[i] = b[i - 1] + a[i];
	}
	int s = n - m + 1;
	int m = lower_bound(b + s,b + n + 1,k + b[s - 1]) - b;
	cout << (m == n + 1?-1:m);
	return 0;
}