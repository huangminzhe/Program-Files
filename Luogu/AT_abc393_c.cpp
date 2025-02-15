#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int cnt;
set<int> a[N];
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		int u,v;
		cin >> u >> v;
		if (u > v)	swap(u,v);
		if (u == v){
			cnt++;
			continue;
		}else{
			if (a[u].count(v))	cnt++;
			else	a[u].insert(v);
		}
	}
	cout << cnt;
	return 0;
}