#include <bits/stdc++.h>
using namespace std;
int sum;
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		int x;
		cin >> x;
		sum += x;
	}
	if (sum > m)	cout << "No";
	else	cout << "Yes";
	return 0;
}