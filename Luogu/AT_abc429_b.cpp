#include <bits/stdc++.h>
using namespace std;
int n,m,sum;
bool t[105];
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		int x;
		cin >> x;
		t[x] = 1;
		sum += x;
	}
	for (int i = 0;i <= 100;i++){
		if (t[i] && sum - i == m){
			cout << "Yes";
			return 0;
		}
	}
	cout << "No";
	return 0;
}