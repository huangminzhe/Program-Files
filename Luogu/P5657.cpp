#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull qpow(int x,int y){
	if (!y)	return 1;
	ull a = qpow(x,y / 2);
	return a * a * (y & 1?x:1);
}
int main(int argc, char **argv){
	int n;ull k;
	cin >> n >> k;
	n--;
	bool flag = k < qpow(2,n);
	while (n){
		n--;
		if (flag){
			cout << 0;
			flag = k < qpow(2,n);
		}else{
			cout << 1;
			flag = k > qpow(2,n);
		}
	}
	cout << !flag;
	return 0;
}