#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e4 + 5,M = 5e4 + 5;
int n,m,tot,dfn[N],low[N],cnt,a[N],f[N];
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
int main(int argc, char **argv){
	cin >> n >> m;
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
			if (f[i] != f[v])	g2[f[i]].push_back(f[v]),f2[f[i]] = 1;
		}
	}
	int ans = 0;
	for (int i = 1;i <= cnt;i++){
		if (!f2[i] && ans){
			cout << 0;
			return 0;
		}else if (!f2[i])	ans = a[i];
	}
	cout << ans;
	return 0;
}
