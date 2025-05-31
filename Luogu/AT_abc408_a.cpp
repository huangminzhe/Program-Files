#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int n,s;
	cin >> n >> s;
	int o = 0;
	for (int i = 1;i <= n;i++){
		int x;
		cin >> x;
		if (x - o > s){
			cout << "No";
			return 0;
		}
		o = x;
	}
	cout << "Yes";
	return 0;
}