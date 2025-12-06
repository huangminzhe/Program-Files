#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5;
int n,m;
vector<int> a[N];
bool f[N];
void dfs(int x){
	if (f[x])	return ;
	f[x] = 1;
	for (int v : a[x]){
		dfs(v);
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		int u,v;
		cin >> u >> v;
		a[v].push_back(u);
	}
	int t;
	cin >> t;
	while (t--){
		int op,x;
		cin >> op >> x;
		if (op == 1){
			dfs(x);
		}else{
			cout << (f[x]?"Yes\n":"No\n");
		}
	}
	return 0;
}