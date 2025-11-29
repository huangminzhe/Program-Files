#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= (n - 1) / 2;i++)	cout << '-';
	if (n & 1)	cout << '=';
	else	cout << "==";
	for (int i = 1;i <= (n - 1) / 2;i++)	cout << '-';
	return 0;
}