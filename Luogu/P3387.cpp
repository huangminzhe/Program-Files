#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e4 + 5,M = 1e5 + 5;
int n,m,tot,dfn[N],low[N],cnt,f[N],a[N],a2[N],dp[N],mx;
bool is[N],f2[N];
vector<int> g[N],root,g2[N];
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
		int sum = a[u];
		f[u] = cnt;
		while (s.top() != u){
			sum += a[s.top()];
			f[s.top()] = cnt;
			is[s.top()] = 0;
			s.pop();
		}
		a2[cnt] = sum;
		s.pop();
		is[u] = 0;
	}
}
int dps(int u){
	f2[u] = 1;
	dp[u] = a2[u];
	for (int v : g2[u]){
		if (!f2[u])	dps(v);
		dp[u] = max(dp[u],dp[v] + a2[u]);
	}
	return dp[u];
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++)	cin >> a[i];
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
			if (f[i] != f[v])	g2[f[i]].push_back(f[v]);
		}
	}
	for (int i = 1;i <= cnt;i++){
		if (!f2[i])	mx = max(mx,dps(i));
	}
	cout << mx;
	return 0;
}