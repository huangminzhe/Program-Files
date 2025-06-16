#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
struct edge{
	int u,v;
	int nxt;
}edges[N];
int tot,head[N];
void add(int u,int v){
	edges[++tot] = {u,v,head[u]};
	head[u] = tot;
}

int n,a[N],fa[N];
ll dp[N][2],ans;
bool f[N];
void dfs(int u,int root){
	f[u] = 1;
	dp[u][0] = 0,dp[u][1] = a[u];	// 记得初始化 dp[u][0]
	for (int i = head[u];i;i = edges[i].nxt){	// 枚举讨厌自己的人
		int v = edges[i].v;
		if (v == root)	continue;	// 不经过断边
		dfs(v,root);
		dp[u][0] += max(dp[v][0],dp[v][1]);	// 自己不选时，讨厌自己的人可以选或不选
		dp[u][1] += dp[v][0];	// 自己选时，讨厌自己的人一定不会选
	}
}
void solve(int x){
	int root = x;
	while (!f[fa[root]]){	// 找环上的点
		root = fa[root];
		f[root] = 1;
	}
	dfs(root,root);
	ll t = dp[root][0];	// 防止 root 讨厌的那个人被选上
	root = fa[root];
	dfs(root,root);
	ans += max(t,dp[root][0]);	// 同上
}
int main(int argc, char **argv){
	ios::sync_with_stdio(0),cin.tie(0);	// 开 O2 或加这一句都行
	cin >> n;
	for (int i = 1;i <= n;i++){
		int v;
		cin >> a[i] >> v;
		add(v,i);
		fa[i] = v;	// 自己讨厌的人是父亲，这样每个点只有一个父亲
	}
	for (int i = 1;i <= n;i++){
		if (!f[i])	solve(i);	// 有可能是森林
	}
	cout << ans;
	return 0;
}