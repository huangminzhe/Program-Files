#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		int n,cnt = 0;
		cin >> n;
		int n3 = n / 3;
		cnt += n3 * 2;
		if (n % 3 == 2)	cnt++;
		cout << cnt << '\n';
	}
	return 0;
}