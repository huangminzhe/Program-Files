#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull qpow(int x,int y){
	if (!y)	return 1;
	ull a = qpow(x,y / 2);
	return a * a * (y & 1?x:1);
}
int main(int argc, char **argv){
	int n;ull k,p;
	cin >> n >> k;
	n--;
	p = qpow(2,n);
	bool flag = k >= p;
	while (n){
		n--;
		cout << flag;
		printf(" %llu ",p);
		if (flag)	k -= p,k = p - k - 1;
		p = qpow(2,n);
		flag = flag?k >= p:k < p;
	}
	cout << flag;
	return 0;
}