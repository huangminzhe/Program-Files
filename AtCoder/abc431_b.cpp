#include <bits/stdc++.h>
using namespace std;
const int N = 105;
bool t[N];
int a[N];
int main(int argc, char **argv){
	int w,n;
	cin >> w >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	int q;
	cin >> q;
	while (q--){
		int x;
		cin >> x;
		t[x] = !t[x];
		if (t[x])	w += a[x];
		else	w -= a[x];
		cout << w << '\n';
	}
	return 0;
}