#include <bits/stdc++.h>
using namespace std;
int a[105],cnt;
int main(int argc, char **argv){
	int n,k;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	cin >> k;
	for (int i = 1;i <= n;i++){
		if (k <= a[i])	cnt++;
	}
	cout << cnt;
	return 0;
}