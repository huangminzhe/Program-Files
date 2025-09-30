#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int o[] = {0,1,1,0};
ull qpow(int x,int y){
	if (!y)	return 1;
	ull a = qpow(x,y / 2);
	return a * a * (y & 1?x:1);
}
int main(int argc, char **argv){
	int n;ull k;
	cin >> n >> k;
	while (n--){
		cout << o[k / qpow(2,n) % 4];
	}
	return 0;
}