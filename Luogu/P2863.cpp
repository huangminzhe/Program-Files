#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e4 + 5,M = 5e4 + 5;
int n,m,tot,dfn[N],low[N],cnt;
bool f[N],is[N];
// f[i] 表示 i 走过没有；is[i] 表示 i 是否在栈内
vector<int> a[N],root;
void dfs(int u){
	dfn[u] = ++tot,low[u] = dfn[u];
	for (int v : a[u]){
		if (!dfn[v])	dfs(v);
	}
}
stack<int> s;
void tarjan(int u){
	s.push(u);
	f[u] = 1;
	is[u] = 1;
	for (int v : a[u]){
		if (!f[v])	tarjan(v);
		if (is[v])	low[u] = min(low[u],low[v]);
	}
	if (dfn[u] == low[u]){
		int sz = 1;
		while (s.top() != u){
			sz++;
			is[s.top()] = 0;
			s.pop();
		}
		s.pop();
		is[u] = 0;
		if (sz > 1)	cnt++;
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		int u,v;
		cin >> u >> v;
		a[u].push_back(v);
	}
	for (int i = 1;i <= n;i++){
		if (!dfn[i])	dfs(i),root.push_back(i);
	}
	// for (int i = 1;i <= n;i++)	printf("%d:%d ",i,dfn[i]);
	for (int i : root)	tarjan(i);
	// cout << '\n';
	// for (int i = 1;i <= n;i++)	printf("%d:%d ",i,low[i]);
	cout << cnt;
	return 0;
}
