#include <bits/stdc++.h>
using namespace std;
set<string> s;
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	string a,b;
	cin >> a >> b;
	for (int i = 0;i <= n - m;i++){
		string t = "";
		for (int j = i;j < i + m;j++){
			t += a[j];
		}
		s.insert(t);
	}
	int ans = 0x7fffffff;
	for (auto i : s){
		int cnt = 0;
		for (int j = 0;j < m;j++){
			cnt += (i[j] - b[j] + 10) % 10;
		}
		ans = min(ans,cnt);
	}
	cout << ans;
	return 0;
}