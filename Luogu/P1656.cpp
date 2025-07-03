#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N = 155,M = 5e3 + 5;
int n,m,dfn[N],tot,low[N];
vector<int> g[N];
set<pii> ans;
void tarjan(int u,int fa){
	dfn[u] = ++tot;low[u] = tot;
	for (int v : g[u]){
		if (!dfn[v])	tarjan(v,u),low[u] = min(low[u],low[v]);	// 树边
		else if (v != fa)	low[u] = min(low[u],dfn[v]);	// 非树边
	}
	if (dfn[u] == low[u]){
		for (int v : g[u]){
			if (low[u] != low[v]){
				ans.insert({min(u,v),max(u,v)});
			}
		}
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
	for (pii i : ans){
		cout << i.first << ' ' << i.second << '\n';
	}
	return 0;
}