#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int x,a,b,c;
	cin >> x >> a >> b >> c;
	x /= 60;
	if (x < 1)	cout << 0;
	else if (x < 2)	cout << a;
	else if (x < 4)	cout << b;
	else	cout << c;
	return 0;
}