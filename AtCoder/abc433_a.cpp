#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int a,b,c;
	cin >> a >> b >> c;
	if (a >= b * c && 1.0 * (a - b * c) / (c - 1) == (a - b * c) / (c - 1))	cout << "Yes";
	else	cout << "No";
	return 0;
}