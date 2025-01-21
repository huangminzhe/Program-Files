#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5,INF = 0x7fffffff;
int mod;
template<typename tp>
class SGT{
	private:
		vector<tp> a,d,b;
		int n;
		inline void up(int p){d[p] = (d[p * 2] + d[p * 2 + 1]) % mod;}
		void pd(int l,int r,int p){
			size_t mid = l + (r - l >> 1);
			(d[p * 2] += b[p] * (mid - l + 1)) %= mod,(d[p * 2 + 1] += b[p] * (r - mid)) %= mod;
			(b[p * 2] += b[p]) %= mod,(b[p * 2 + 1] += b[p]) %= mod;
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
			if (tr > mid)	(res += query(tl,tr,mid + 1,r,p * 2 + 1)) %= mod;
			return res;
		}
		void add(size_t tl,size_t tr,tp x,size_t l,size_t r,size_t p){
			if (tl <= l && r <= tr){
				(d[p] += (r - l + 1) * x) %= mod,(b[p] += x) %= mod;
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

int n,m,s;
vector<ll> aa(N);
vector<int> a(N),g[N];
SGT<ll> d(N);
int fa[N],dep[N],hs[N],top[N],dfn[N],t;	// hs：重儿子
ll sz[N];
void dfs(int u){
	ll mx = -INF;
	sz[u] = 1;
	for (int v : g[u]){
		if (v != fa[u]){
			dep[v] = dep[u] + 1;
			fa[v] = u;
			dfs(v);
			sz[u] += sz[v];
			if (sz[v] > mx){
				hs[u] = v,mx = sz[v];
			}
		}
	}
}
void chn(int u,int tp){
	dfn[u] = ++t,top[u] = tp,aa[t] = a[u];
	if (!hs[u])	return ;
	chn(hs[u],tp);
	for (int v : g[u])
		if (v != fa[u] && v != hs[u])
			chn(v,v);
}
void init(int s){
	dep[s] = 1;
	dfs(s);
	chn(s,s);
	d.build(aa);
}
void add(int u,int v,int x){
	while (top[u] != top[v]){
		if (dep[top[u]] < dep[top[v]])	swap(u,v);
		d.add(dfn[top[u]],dfn[u],x);
		u = fa[top[u]];
	}
	if (dep[u] > dep[v])	swap(u,v);
	d.add(dfn[u],dfn[v],x);
}
int query(int u,int v){
	ll res = 0;
	while (top[u] != top[v]){
		if (dep[top[u]] < dep[top[v]])	swap(u,v);
		(res += d.query(dfn[top[u]],dfn[u])) %= mod;
		u = fa[top[u]];
	}
	if (dep[u] > dep[v])	swap(u,v);
	res += d.query(dfn[u],dfn[v]);
	return res;
}
int main(int argc, char **argv){
	cin >> n >> m >> s >> mod;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	for (int i = 1;i < n;i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	init(s);
	while (m--){
		int op,x,y,z;
		cin >> op >> x;
		if (op == 1){
			cin >> y >> z;
			add(x,y,z);
		}else if (op == 2){
			cin >> y;
			printf("%d\n",query(x,y) % mod);
		}else if (op == 3){
			cin >> z;
			d.add(dfn[x],dfn[x] + sz[x] - 1,z);
		}else{
			printf("%d\n",d.query(dfn[x],dfn[x] + sz[x] - 1) % mod);
		}
	}
	return 0;
}