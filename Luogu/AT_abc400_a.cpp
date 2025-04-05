#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int n;
	cin >> n;
	if (400 % n == 0)	cout << 400 / n;
	else cout << -1;
	return 0;
}