#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N = 105;
int n,q,sum;
vector<pii> a[N];
int dp[N][N];
void dfs(int u,int fa){
	for (pii v : a[u]){
		if (v.first == fa)	continue;
	}
}
int main(int argc, char **argv){
	cin >> n >> q;
	for (int i = 1;i < n;i++){
		int u,v,w;
		cin >> u >> v >> w;
		a[u].push_back({v,w});
		a[v].push_back({u,w});
		sum += w;
	}
	if (n == q){
		cout << sum;
		return 0;
	}
	dp[1][n] = sum;
	dfs(1,0);
	return 0;
}