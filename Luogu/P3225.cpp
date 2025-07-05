#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 505;
int n,dfn[N],low[N],tot,cnt,a[N],ans,sum[N],ans2;
bool f[N];
vector<int> g[N];
stack<int> s;
void tarjan(int u,int fa){
	dfn[u] = ++tot,low[u] = tot;
	if (!fa && !g[u].size())	cnt++,sum[cnt] = 1;
	s.push(u);
	bool flag = 0;
	int son = 0,o;
	for (int v : g[u]){
		if (!dfn[v]){
			son++;
			tarjan(v,u),low[u] = min(low[u],low[v]);
			if (low[v] >= dfn[u]){
				o = cnt++;
				if (fa && son || !fa && son > 1)	f[u] = 1;
				if (f[u])	a[o]++;
				sum[cnt] = 1;
				while (s.top() != u){
					sum[cnt]++;
					s.pop();
				}
			}
		}else if (v != fa || flag)	low[u] = min(low[u],dfn[v]);
		else	flag = 1;
	}
	if (f[u])	a[cnt]++;
}
int main(int argc, char **argv){
	int CASE = 0;
	cin >> n;
	while (n){
		for (int i = 1;i <= n;i++)	g[i].clear();
		memset(f,0,sizeof f);
		memset(dfn,0,sizeof dfn);
		tot = 0,cnt = 0;
		memset(a,0,sizeof a);

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
		ans = 0,ans2 = 1;
		for (int i = 1;i <= cnt;i++){
			if (a[i] == 1)	ans++,ans2 *= sum[i];
		}
		if (ans < 2)	ans = 2,ans2 = n * (n - 1) / 2;
		cout << "Case " << ++CASE << ": " << ans << ' ' << ans2 / 2 << '\n';
		cin >> n;
	}
	return 0;
}