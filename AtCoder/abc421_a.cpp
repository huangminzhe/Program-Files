#include <bits/stdc++.h>
using namespace std;
string a[105];
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	int x;string s;
	cin >> x >> s;
	if (a[x] == s)	cout << "Yes";
	else	cout << "No";
	return 0;
}