#include <bits/stdc++.h>
using namespace std;
map<string,int> t;
int mx;
int main(int argc, char **argv){
	int n,k;string s;
	cin >> n >> k >> s;
	for (int i = 1;i <= n - k + 1;i++){
		int si = i - 1;string st = "";
		for (int j = 0;j < k;j++){
			st += s[si + j];
		}
		t[st]++;
		mx = max(mx,t[st]);
	}
	cout << mx << '\n';
	for (auto [i,x] : t){
		// printf("%d %s\n",i.size(),i.c_str());
		if (x == mx)	cout << i << ' ';
	}
	return 0;
}