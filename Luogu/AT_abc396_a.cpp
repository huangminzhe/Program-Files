#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n,a[N];
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		if (i > 2 && a[i] == a[i - 1] && a[i - 1] == a[i - 2]){
			cout << "Yes" << endl;
			return 0;
		}
	}
	cout << "No" << endl;
	return 0;
}