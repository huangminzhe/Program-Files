#include <bits/stdc++.h>
using namespace std;
bool a[105];
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		char c;
		cin >> c;
		if (c == 'o')	a[i] = 1;
	}
	for (int i = 1;i <= n;i++){
		char c;
		cin >> c;
		if (c == 'o' && a[i]){
			cout << "Yes";
			return 0;
		}
	}
	cout << "No";
	return 0;
}