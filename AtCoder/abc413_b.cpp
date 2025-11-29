#include <bits/stdc++.h>
using namespace std;
string a[105];
set<string> s;
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			if (i == j)	continue;
			s.insert(a[i] + a[j]);
		}
	}
	cout << s.size();
	return 0;
}