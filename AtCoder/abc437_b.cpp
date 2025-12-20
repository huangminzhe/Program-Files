#include <bits/stdc++.h>
using namespace std;
const int N = 95;
int n,m,q,a[N][N];
set<int> b;
int main(int argc, char **argv){
	cin >> n >> m >> q;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= m;j++){
			cin >> a[i][j];
		}
	}
	for (int i = 1;i <= q;i++){
		int x;
		cin >> x;
		b.insert(x);
	}
	int ans = 0;
	for (int i = 1;i <= n;i++){
		int cnt = 0;
		for (int j = 1;j <= m;j++){
			if (b.find(a[i][j]) != b.end())	cnt++;
		}
		ans = max(cnt,ans);
	}
	cout << ans;
	return 0;
}