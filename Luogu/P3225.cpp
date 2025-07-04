#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 505;
int n,dfn[N],low[N],tot,cnt;
vector<int> g[N];
void tarjan(int u,int fa){
	dfn[u] = ++tot,low[u] = tot;
	bool flag = 0;
	for (int v : g[u]){
		if (!dfn[v]){
			tarjan(v,u),low[u] = min(low[u],low[v]);
			if (low[v] >= dfn[u]){
				cnt++;
			}
		}else if (v != fa || flag)	low[u] = min(low[u],dfn[v]);
		else	flag = 1;
	}
}
int main(int argc, char **argv){
	cin >> n;
	while (n){
		;

		for (int i = 1;i <= n;i++){
			int u,v;
			cin >> u >> v;
			if (u == v)	continue;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		for (int i = 1;i <= n;i++){
			if (!dfn[i])	tarjan(i,0);
		}
		cin >> n;
	}
	return 0;
}