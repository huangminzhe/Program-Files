#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5;
int a[N];
ll sum,b[N];
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		b[i] = b[i - 1] + a[i];
	}
	for (int i = 1;i < n;i++){
		sum += (ll)a[i] * (b[n] - b[i]);
	}
	cout << sum;
	return 0;
}