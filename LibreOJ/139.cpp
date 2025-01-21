#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
template<typename tp>
class SGT{
	private:
		vector<tp> a,d,b;
		int n;
		inline void up(int p){d[p] = d[p * 2] + d[p * 2 + 1];}
		void pd(int l,int r,int p){
			size_t mid = l + (r - l >> 1);
			d[p * 2] += b[p] * (mid - l + 1),d[p * 2 + 1] += b[p] * (r - mid);
			b[p * 2] += b[p],b[p * 2 + 1] += b[p];
			b[p] = 0;
		}
		void build(size_t l,size_t r,size_t p){
			if (l == r){
				d[p] = a[l];
				return ;
			}
			size_t mid = l + (r - l >> 1);
			build(l,mid,p * 2);
			build(mid + 1,r,p * 2 + 1);
			up(p);
		}
		tp query(size_t tl,size_t tr,size_t l,size_t r,size_t p){
			if (tl <= l && r <= tr)	return d[p];
			size_t mid = l + (r - l >> 1);
			pd(l,r,p);
			tp res = 0;
			if (tl <= mid)	res += query(tl,tr,l,mid,p * 2);
			if (tr > mid)	res += query(tl,tr,mid + 1,r,p * 2 + 1);
			return res;
		}
		void add(size_t tl,size_t tr,tp x,size_t l,size_t r,size_t p){
			if (tl <= l && r <= tr){
				d[p] += (r - l + 1) * x,b[p] += x;
				return ;
			}
			size_t mid = l + (r - l >> 1);
			pd(l,r,p);
			if (tl <= mid)	add(tl,tr,x,l,mid,p * 2);
			if (tr > mid)	add(tl,tr,x,mid + 1,r,p * 2 + 1);
			up(p);
		}
	public:
		SGT(size_t size){
			n = size;
			a = vector<tp>(n);
			d = vector<tp>(4 * n);
			b = vector<tp>(4 * n);
		}
		void build(vector<tp> arr){
			a = arr;
			build(1,n,1);
		}
		tp query(size_t r){
			return query(1,r,1,n,1);
		}
		tp query(size_t l,size_t r){
			return query(l,r,1,n,1);
		}
		void add(size_t i,tp x){
			add(i,i,x,1,n,1);
		}
		void add(size_t l,size_t r,tp x){
			add(l,r,x,1,n,1);
		}
};

int n,m;
vector<int> a(N),g[N];
vector<ll> aa(N);
SGT<ll> d(N);
int fa[N],dep[N],dfn[N],t,sz[N],top[N],hs[N],rt;
void dfs(int u){
	sz[u] = 1;
	for (int v : g[u]){
		if (v == fa[u])	continue;
		dep[v] = dep[u] + 1;
		dfs(v);
		sz[u] += sz[v];
		if (sz[hs[u]] < sz[v])	hs[u] = v;
	}
}
void chn(int u,int tp){
	dfn[u] = ++t,top[u] = tp,aa[t] = a[u];
	if (!hs[u])	return ;
	chn(hs[u],tp);
	for (int v : g[u]){
		if (v == fa[u] || v == hs[u])	continue;
		chn(v,v);
	}
}
void init(int s){
	dep[s] = 1;
	dfs(s);
	chn(s,s);
	d.build(aa);
}
int fs(int rt,int x){
	while (top[rt] != top[x]){
		if (fa[top[rt]] == x)	return top[rt];
		rt = fa[top[rt]];
	}
	return hs[x];
}
void padd(int u,int v,int x){	// 路径加
	while (top[u] != top[v]){
		if (dep[top[u]] < dep[top[v]])	swap(u,v);
		d.add(dfn[top[u]],dfn[u],x);
		u = fa[top[u]];
	}
	if (dep[u] > dep[v])	swap(u,v);
	d.add(dfn[u],dfn[v],x);
}
void tadd(int u,int x){	// 树加
	d.add(dfn[u],dfn[u] + sz[u] - 1,x);
}
ll pquery(int u,int v){	// 路径查询
	ll res = 0;
	while (top[u] != top[v]){
		if (dep[top[u]] < dep[top[v]])	swap(u,v);
		res += d.query(dfn[top[u]],dfn[u]);
		u = fa[top[u]];
	}
	if (dep[u] > dep[v])	swap(u,v);
	res += d.query(dfn[u],dfn[v]);
	return res;
}
ll tquery(int u){	// 树查询
	return d.query(dfn[u],dfn[u] + sz[u] - 1);
}
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++)
		scanf("%d",&a[i]);
	for (int i = 2;i <= n;i++){
		scanf("%d",fa + i);
		g[fa[i]].push_back(i);
		g[i].push_back(fa[i]);
	}
	rt = 1;
	init(rt);
	cin >> m;
	while (m--){
		int op,u,v,k;
		scanf("%d %d",&op,&u);
		if (op == 1){
			rt = u;
		}else if (op == 2){
			scanf("%d %d",&v,&k);
			padd(u,v,k);
		}else if (op == 3){
			scanf("%d",&k);
			if (dfn[u] > dfn[rt])	tadd(u,k);
			else if (rt == u)	tadd(1,k);
			else{
				int s = fs(rt,u);
				tadd(1,k);
				tadd(s,-k);
			}
		}else if (op == 4){
			scanf("%d",&v);
			printf("%lld\n",pquery(u,v));
		}else{
			if (dfn[u] > dfn[rt])	printf("%lld\n",tquery(u));
			else if (rt == u)	printf("%lld\n",tquery(1));
			else{
				int s = fs(rt,u);
				printf("%lld\n",tquery(1) - tquery(s));
			}
		}
	}
	return 0;
}