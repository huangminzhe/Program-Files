#include <bits/stdc++.h>
using namespace std;
const int N = 1.5e3 + 5;
int n,dp[N][N],s;
vector<int> a[N];
bool fa[N];
void dfs(int u){
	dp[u][1] = 1;
	for (int v : a[u]){
		dfs(v);
		dp[u][0] += dp[v][1];
		dp[u][1] += min(dp[v][0],dp[v][1]);
	}
}
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		int id,k;
		cin >> id >> k;
		for (int j = 1;j <= k;j++){
			int x;
			cin >> x;
			a[id].push_back(x);
			fa[x] = 1;
		}
	}
	for (int i = 0;i < n;i++){
		if (!fa[i]){
			s = i;
			dfs(s);
			break;
		}
	}
	cout << min(dp[s][0],dp[s][1]);
	return 0;
}