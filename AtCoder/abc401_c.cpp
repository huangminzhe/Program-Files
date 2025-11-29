#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
ll a[N],b[N];
ll query(int l,int r){
	return b[r] - b[l - 1] % int(1e9);
}
int main(int argc, char **argv){
	int n,k;
	cin >> n >> k;
	if (n < k){
		cout << 1;
		return 0;
	}
	a[0] = 1,b[0] = 1;
	for (int i = 1;i < k;i++){
		a[i] = 1,b[i] = b[i - 1] + 1;
	}
	for (int i = k;i <= n;i++){
		a[i] = query(i - k,i - 1),b[i] = (b[i - 1] + a[i]) % int(1e9);
	}
	cout << a[n] % int(1e9);
	return 0;
}