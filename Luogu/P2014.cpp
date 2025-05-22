#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 305;
int n,m;
int pre[N],a[N],dp[N][N];
vector<int> g[N];
int dfs(int u,int lss){
	if (!lss || !g[u].size())	return 0;
	for (int v : g[u]){
	}
	return dp[u][lss];
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		cin >> pre[i] >> a[i];
		g[pre[i]].push_back(i);
	}
	cout << dfs(0,m);
	return 0;
}