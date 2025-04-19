#include <bits/stdc++.h>
using namespace std;
long long l,r,lr,sum;
int main(int argc, char **argv){
	int n,t;
	cin >> n >> t;
	cin >> l >> lr;
	for (int i = 1;i < n;i++){
		cin >> l >> r;
		if (l - lr > t)	sum += l - lr - t;
		lr = r;
	}
	cout << sum;
	return 0;
}