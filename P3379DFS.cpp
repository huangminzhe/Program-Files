#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5,LOG2N = 20;
class LCA{
	private:
		vector<int> a[N];	// 图
		int dep[N],fa[N];	// 层数；父节点
		int d[N],dfn[N],t;	// DFS序；时间戳；时间总和
		int Log2[N],st[N][LOG2N];	// 2的幂次；区间深度最小的结点的ST表
		inline int get(int u,int v){return dep[u] < dep[v]?u:v;}
		void dfs(int u){
			dfn[u] = ++t,d[t] = u,st[t][0] = fa[u];
			for (int v : a[u]){
				if (v != fa[u]){
					dep[v] = dep[u] + 1;
					fa[v] = u;
					dfs(v);
				}
			}
		}
	public:
		LCA(){
			t = 0;
		}
		void init(int n,int s){
			dep[s] = 1;
			dfs(s);

			for (int i = 2;i <= n;i++)
				Log2[i] = Log2[i >> 1] + 1;
			for (int j = 1;j <= Log2[n];j++)
				for (int i = 1;i <= n - (1 << j) + 1;i++)
					st[i][j] = get(st[i][j - 1],st[i + (1 << (j - 1))][j - 1]);
		}
		void push(int u,int v){
			a[u].push_back(v);
			a[v].push_back(u);
		}
		int lca(int u,int v){
			if (dfn[u] > dfn[v])	swap(u,v);

			if (u == v)	return u;
			int k = Log2[dfn[v] - dfn[u]];	// u+1~v
			return get(st[dfn[u] + 1][k],st[dfn[v] - (1 << k) + 1][k]);
		}
};
int n,m,s;
LCA a;
int main(int argc, char **argv){
	cin >> n >> m >> s;
	int u,v;
	for (int i = 1;i < n;i++){
		scanf("%d %d",&u,&v);
		a.push(u,v);
	}
	a.init(n,s);
	while (m--){
		scanf("%d %d",&u,&v);
		printf("%d\n",a.lca(u,v));
	}
	return 0;
}