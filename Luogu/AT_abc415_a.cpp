#include <bits/stdc++.h>
using namespace std;
bool f[105];
int main(int argc, char **argv){
	int n,x;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> x;
		f[x] = 1;
	}
	cin >> x;
	cout << (f[x]?"Yes":"No");
	return 0;
}