#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
int n,a[N],b[N];
int main(int argc, char **argv){
	ios::sync_with_stdio(0),cin.tie(0);
	int t;
	cin >> t;
	while (t--){
		cin >> n;
		for (int i = 1;i <= n;i++)	cin >> a[i];
		bool f = 0;
		for (int i = 1;i <= n;i++){
			cin >> b[i];
			if (!(abs(a[i] - b[i]) & 1))	f = 1;
		}
		if (f || n == 1)	cout << "Yes\n";
		else	cout << "No\n";
	}
	return 0;
}