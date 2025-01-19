#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5,LOG2N = 20;
/**
 * @brief Lowest Common Ancestor
 */
class LCA{
	private:
		vector<int> a[N];	// 图
		int dep[N],fa[N];	// 层数；父节点
		int d[N],dfn[N],t;	// DFS序；时间戳；时间总和
		int Log2[N],st[N][LOG2N];	// 2的幂次；区间深度最小的结点的ST表
		/**
		 * @brief Get the deeper node.
		 * @param u the first node
		 * @param v the second node
		 */
		inline int get(int u,int v){return dep[u] < dep[v]?u:v;}
		/**
		 * @brief Record the depth of nodes by DFS.
		 * @param u current node
		 */
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
		/**
		 * @brief Initialize the depth and ST table.
		 * @param n number of nodes
		 * @param s tree root
		 */
		void init(int n,int s){
			dep[s] = 1;
			dfs(s);

			for (int i = 2;i <= n;i++)
				Log2[i] = Log2[i >> 1] + 1;
			for (int j = 1;j <= Log2[n];j++)
				for (int i = 1;i <= n - (1 << j) + 1;i++)
					st[i][j] = get(st[i][j - 1],st[i + (1 << (j - 1))][j - 1]);
		}
		/**
		 * @brief Add an edge between u and v.
		 * @param u the first node
		 * @param v the second node
		 */
		void push(int u,int v){
			a[u].push_back(v);
			a[v].push_back(u);
		}
		/**
		 * @brief Find the LCA of u and v.
		 * @param u the first node
		 * @param v the second node
		 */
		int lca(int u,int v){
			if (dfn[u] > dfn[v])	swap(u,v);

			if (u == v)	return u;
			int k = Log2[dfn[v] - dfn[u]];	// u+1~v
			return get(st[dfn[u] + 1][k],st[dfn[v] - (1 << k) + 1][k]);
		}
		inline int get_dep(int x){return dep[x];}
};
LCA a;
int main(int argc, char **argv){
	int n,m;
	cin >> n;
	for (int i = 1;i < n;i++){
		int u,v;
		cin >> u >> v;
		a.push(u,v);		
	}
	a.init(n,1);
	cin >> m;
	while (m--){
		int u,v;
		cin >> u >> v;
		int lca = a.lca(u,v);
		u = a.get_dep(u),v = a.get_dep(v),lca = a.get_dep(lca);
		printf("%d\n",u + v - 2 * lca);
	}
	return 0;
}