#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int a,b;
	cin >> a >> b;
	double ab = 1.0 * a / b;
	cout << (ab - floor(ab) < ceil(ab) - ab?floor(ab):ceil(ab));
	return 0;
}