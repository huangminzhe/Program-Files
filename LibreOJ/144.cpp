#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n,m,s;
vector<int> a[N];
int d[N],c[N];
int main(int argc, char **argv){
	cin >> n >> m >> s;
	for (int i = 1;i <= n;i++){
		cin >> v;
	}
	for (int i = 1;i < n;i++){
		int u,v;
		cin >> u >> v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	return 0;
}