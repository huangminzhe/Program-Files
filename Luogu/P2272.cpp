#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5,M = 1e6 + 5;
int n,m,tot,dfn[N],low[N],cnt,f[N],a[N],mod,mx[N],mxn[N],ans,dp[N];
// mx[i] 是以 i 为起点的最长链的长度，dp[i] 则是个数
ll anst;
bool is[N],f2[N];
vector<int> g[N],root,g2[N];
set<ll> edges;
void dfs(int u){
	dfn[u] = ++tot,low[u] = dfn[u];
	for (int v : g[u]){
		if (!dfn[v])	dfs(v);
	}
}
stack<int> s;
void tarjan(int u){
	s.push(u);
	f[u] = 1;
	is[u] = 1;
	for (int v : g[u]){
		if (!f[v])	tarjan(v);
		if (is[v])	low[u] = min(low[u],low[v]);
	}
	if (dfn[u] == low[u]){
		cnt++;
		int sum = 1;
		f[u] = cnt;
		while (s.top() != u){
			sum++;
			f[s.top()] = cnt;
			is[s.top()] = 0;
			s.pop();
		}
		a[cnt] = sum;
		s.pop();
		is[u] = 0;
	}
}
int dps(int u){
	if (mx[u])	return mx[u];
	mx[u] = a[u];
	dp[u] = 1;
	for (int v : g2[u]){
		if (a[u] + dps(v) > mx[u]){
			mx[u] = a[u] + dps(v);
			dp[u] = dp[v];
		}else if (a[u] + dps(v) == mx[u]){
			dp[u] += dp[v];
		}
	}
	return mx[u];
}
int main(int argc, char **argv){
	cin >> n >> m >> mod;
	for (int i = 1;i <= m;i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
	}
	for (int i = 1;i <= n;i++){
		if (!dfn[i])	dfs(i),root.push_back(i);
	}
	for (int i : root)	tarjan(i);
	for (int i = 1;i <= n;i++){
		for (int v : g[i]){
			if (f[i] != f[v] && edges.find(f[i] * ll(1e5) + f[v]) == edges.end())	g2[f[i]].push_back(f[v]),f2[f[v]] = 1,edges.insert(f[i] * ll(1e5) + f[v]);
		}
	}
	for (int i = 1;i <= cnt;i++){
		if (!f2[i]){
			if (dps(i) > ans){
				ans = dps(i);
				anst = dp[i];
			}else if (dps(i) == ans)	anst += dp[i];
		}
	}
	cout << ans << '\n' << anst % mod;
	return 0;
}