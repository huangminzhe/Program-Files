#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n,m,fa[N],sz[N];
bool op[N];
ll cnt,ans[N];
vector<int> g[N];
int find(int x){
	if (x == fa[x])	return x;
	return fa[x] = find(fa[x]);
}
void merge(int x,int y){
	if (find(x) != find(y)){
		x = fa[x],y = fa[y];
		fa[x] = y;
		cnt += 1LL * sz[x] * sz[y];
		sz[y] += sz[x];
	}
}
void add(int x){
	x = find(x);
	cnt += sz[x];
	sz[x]++;
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++)	fa[i] = i;
	for (int i = 1;i <= n;i++){
		char c;
		cin >> c;
		op[i] = c - '0';
	}
	for (int i = 1;i <= m;i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
		if (op[u] && op[v])	merge(u,v);
	}
	for (int i = n;i > 0;i--){
		for (int j : g[i]){
			if (j > i || op[j])	merge(i,j);
		}
		add(i);
		ans[i] = cnt;
	}
	for (int i = 1;i <= n;i++){
		cout << ans[i] << '\n';
	}
	return 0;
}