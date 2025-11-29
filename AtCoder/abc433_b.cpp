#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int a[N];
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		for (int j = i - 1;j > 0;j--){
			if (a[j] > a[i]){
				cout << j << '\n';
				goto out;
			}
		}
		cout << "-1\n";
		out:
	}
	return 0;
}