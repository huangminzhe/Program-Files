#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int a[N];
long long cnt;
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	for (int i = 1;a[i] * 2 <= a[n];i++){
		int it = lower_bound(a + i,a + n + 1,a[i] * 2) - a;
		cnt += n - it + 1;
	}
	cout << cnt;
	return 0;
}