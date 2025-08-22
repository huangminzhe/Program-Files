#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		int n,cnt = 0;
		cin >> n;
		for (int i = 1;i <= n;i++){
			int x;
			cin >> x;
			for (int j = 1;j <= x;j++){
				if (i == 1 || j == 1 || j == x || i * j % 10 == 6)	cnt++;
			}
		}
		cout << cnt << '\n';
	}
	return 0;
}