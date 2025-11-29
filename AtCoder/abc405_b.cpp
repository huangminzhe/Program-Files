#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int t[N],a[N],cnt;
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		t[a[i]]++;
	}
	for (int i = 1;i <= m;i++){
		if (!t[i]){
			cout << 0;
			return 0;
		}
	}
	for (int i = n;i > 0;i--){
		t[a[i]]--;
		cnt++;
		if (a[i] <= m && !t[a[i]])
			break;
	}
	cout << cnt;
	return 0;
}