#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
const ll INF = 0x7fffffffffffffff;
struct edge{
	int v,w;
	int nxt;
}edges[N * 2];
int tot,head[N];
void add(int u,int v,int w){
	edges[++tot] = {v,w,head[u]};
	head[u] = tot;
}

ll dp[N],ans;
ll init(int u,int fa){
	for (int i = head[u];i;i = edges[i].nxt){
		int v = edges[i].v,w = edges[i].w;
		if (v == fa)	continue;
		dp[u] += min(ll(w),init(v,u));
	}
	if (!dp[u])	return INF;
	return dp[u];
}
void dfs(int u,int fa){
	for (int i = head[u];i;i = edges[i].nxt){
		int v = edges[i].v,w = edges[i].w;
		if (v == fa)	continue;
		if (i == head[u] && edges[i].nxt == 0)	dp[v] += w;	// 根节点只有一个儿子时
		else	dp[v] = dp[v] + min(ll(w),dp[u] - min(ll(w),dp[v]));
		dfs(v,u);
	}
}
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		memset(edges,0,sizeof edges);
		memset(head,0,sizeof head);
		tot = 0;
		memset(dp,0,sizeof dp);

		int n;
		cin >> n;
		for (int i = 1;i < n;i++){
			int u,v,w;
			cin >> u >> v >> w;
			add(u,v,w);
			add(v,u,w);
		}
		init(1,0);
		dfs(1,0);
		cout << *max_element(dp + 1,dp + n + 1) << '\n';
	}
	return 0;
}