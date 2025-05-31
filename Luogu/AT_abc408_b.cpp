#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int a[N];
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	sort(a + 1,a + n + 1);
	int r = unique(a + 1,a + n + 1) - a - 1;
	cout << r << '\n';
	for (int i = 1;i <= r;i++){
		cout << a[i] << ' ';
	}
	return 0;
}