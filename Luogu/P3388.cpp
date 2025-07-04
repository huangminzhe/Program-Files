#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e4 + 5,M = 1e5 + 5;
int n,m,dfn[N],low[N],tot,sum;
vector<int> g[N];
bool ans[N];
void tarjan(int u,int fa){
	dfn[u] = ++tot;low[u] = tot;
	bool flag = 0;
	int cnt = 0;
	for (int v : g[u]){
		if (!dfn[v]){
			tarjan(v,u),low[u] = min(low[u],low[v]);
			if (low[v] >= dfn[u])	cnt++;
		}
		else if (v != fa || flag)	low[u] = min(low[u],dfn[v]);
		else	flag = 1;
	}
	if (cnt && fa || cnt > 1 && !fa)	ans[u] = 1;
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		int u,v;
		cin >> u >> v;
		if (u == v)	continue;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 1;i <= n;i++){
		if (!dfn[i])	tarjan(i,0);
	}
	for (int i = 1;i <= n;i++){
		if (ans[i])	sum++;
	}
	cout << sum << '\n';
	for (int i = 1;i <= n;i++){
		if (ans[i])	cout << i << ' ';
	}
	return 0;
}