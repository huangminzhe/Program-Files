#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N = 5e5 + 5,M = 2e6 + 5;
int n,m,dfn[N],tot,low[N],cnt;
vector<int> g[N],ans[N];
stack<int> s;
void tarjan(int u,int fa){
	dfn[u] = ++tot;low[u] = tot;
	s.push(u);
	bool flag = 0;
	for (int v : g[u]){
		if (!dfn[v])	tarjan(v,u),low[u] = min(low[u],low[v]);
		else if (v != fa || flag)	low[u] = min(low[u],dfn[v]);
		else	flag = 1;	// 判重边
	}
	if (low[u] == dfn[u]){
		cnt++;
		while (s.top() != u){
			ans[cnt].push_back(s.top());
			s.pop();
		}
		ans[cnt].push_back(u);
		s.pop();
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		int u,v;
		cin >> u >> v;
		int t = u;u = min(u,v),v = max(t,v);
		if (u != v)
			g[u].push_back(v),
			g[v].push_back(u);
	}
	for (int i = 1;i <= n;i++){
		if (!dfn[i])	tarjan(i,0);
	}
	cout << cnt << '\n';
	for (int i = 1;i <= cnt;i++){
		cout << ans[i].size() << ' ';
		for (int v : ans[i])
			cout << v << ' ';
		cout << '\n';
	}
	return 0;
}