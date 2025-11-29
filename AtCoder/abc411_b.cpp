#include <bits/stdc++.h>
using namespace std;
int a[55],d[55][55];
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i < n;i++){
		cin >> a[i];
	}
	for (int i = 1;i <= n;i++){
		for (int j = i + 1;j <= n;j++){
			d[i][j] = d[i][j - 1] + a[j - 1];
			cout << d[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}