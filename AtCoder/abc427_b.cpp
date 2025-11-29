#include <bits/stdc++.h>
using namespace std;
int a[105] = {1};
int f(int x){
	int res = 0;
	while (x){
		res += x % 10;
		x /= 10;
	}
	return res;
}
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		for (int j = 0;j < i;j++){
			a[i] += f(a[j]);
		}
	}
	cout << a[n];
	return 0;
}