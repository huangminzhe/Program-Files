#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e3 + 5,M = 1e4 + 5;
int n,m,dfn[N],low[N],tot,cnt,f[N],sum;
vector<int> g[N],g2[N];
stack<int> s;
void tarjan(int u,int fa){
	dfn[u] = ++tot,low[u] = tot;
	s.push(u);
	bool flag = 0;
	for (int v : g[u]){
		if (!dfn[v])	tarjan(v,u),low[u] = min(low[u],low[v]);
		else if (v != fa || flag)	low[u] = min(low[u],dfn[v]);
		else	flag = 1;
	}
	if (dfn[u] == low[u]){
		cnt++;
		f[u] = cnt;
		while (s.top() != u){
			f[s.top()] = cnt;
			s.pop();
		}
		s.pop();
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 1;i <= n;i++){
		if (!dfn[i])	tarjan(i,0);
	}
	for (int i = 1;i <= n;i++){
		for (int v : g[i]){
			if (f[i] != f[v])	g2[f[i]].push_back(f[v]);
		}
	}
	for (int i = 1;i <= cnt;i++)
		if (g2[i].size() == 1)	sum++;
	cout << (sum + 1) / 2;
	return 0;
}