#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5,M = 5e5 + 5;
int n,m,dfn[N],low[N],tot,f[N],sz[N];
ll ans[N];
vector<int> g[N];
stack<int> s;
void tarjan(int u,int fa){
	sz[u] = 1;
	dfn[u] = ++tot,low[u] = tot;
	s.push(u);
	int cnt = 0,sum = 0;
	for (int v : g[u]){
		if (!dfn[v]){
			tarjan(v,u),low[u] = min(low[u],low[v]);
			if (low[v] >= dfn[u]){
				cnt++;
				ans[u] += (ll)sz[v] * (n - sz[v]);	// 被分离的子树与其他块都不连通
				sum += sz[v];
			}
			sz[u] += sz[v];
		}else if (v != fa)	low[u] = min(low[u],dfn[v]);
	}
	if (cnt && fa || cnt > 1 && !fa){	// 是割点，加上自己和父节点的块
		ans[u] += n - 1 + ll(n - sum - 1) * (sum + 1);
	}else	ans[u] = 2 * (n - 1);	// 不是割点，直接重置
}
int main(int argc, char **argv){
	ios::sync_with_stdio(0),cin.tie(0);
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	tarjan(1,0);
	for (int i = 1;i <= n;i++){
		cout << ans[i] << '\n';
	}
	return 0;
}