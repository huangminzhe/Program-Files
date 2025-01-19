#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
const ll INF = 0x7fffffff;
int a[N];
ll d[N * 4],b[N * 4],c[N * 4];
bool v[N * 4];
inline void up(int p){d[p] = max(d[p * 2],d[p * 2 + 1]);}
void pd(int l,int r,int p){
    int mid = l + (r - l >> 1);
    if (v[p]){
		d[p * 2] = b[p] + c[p],d[p * 2 + 1] = b[p] + c[p];
        b[p * 2] = b[p],b[p * 2 + 1] = b[p];
		c[p * 2] = c[p],c[p * 2 + 1] = c[p];
		v[p * 2] = 1,v[p * 2 + 1] = 1;
        c[p] = 0,v[p] = 0;
	}else{
        d[p * 2] += b[p],d[p * 2 + 1] += b[p];
	    b[p * 2] += b[p],b[p * 2 + 1] += b[p];
    }
	b[p] = 0;
}
void build(int l,int r,int p){
	if (l == r){
		d[p] = a[l];
		return ;
	}
	int mid = l + (r - l >> 1);
	build(l,mid,p * 2);
	build(mid + 1,r,p * 2 + 1);
	up(p);
}
void add(int tl,int tr,int l,int r,int p,int x){
	if (tl <= l && r <= tr){
		d[p] += x;
		b[p] += x;
		return ;
	}
	pd(l,r,p);
	int mid = l + (r - l >> 1);
	if (tl <= mid)	add(tl,tr,l,mid,p * 2,x);
	if (mid < tr)	add(tl,tr,mid + 1,r,p * 2 + 1,x);
	up(p);
}
void mod(int tl,int tr,int l,int r,int p,int x){
	if (tl <= l && r <= tr){
		d[p] = x;
		c[p] = x;
		v[p] = 1;
        b[p] = 0;
		return ;
	}
	pd(l,r,p);
	int mid = l + (r - l >> 1);
	if (tl <= mid)	mod(tl,tr,l,mid,p * 2,x);
	if (mid < tr)	mod(tl,tr,mid + 1,r,p * 2 + 1,x);
	up(p);
}
ll query(int tl,int tr,int l,int r,int p){
	if (l == r)	return d[p];
	pd(l,r,p);
	int mid = l + (r - l >> 1);
	ll mx = -INF;
	if (tl <= mid)	mx = max(mx,query(tl,tr,l,mid,p * 2));
	if (mid < tl)	mx = max(mx,query(tl,tr,mid + 1,r,p * 2 + 1));
	return mx;
}
int main(int argc, char **argv){
	int n,q;
	cin >> n >> q;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	build(1,n,1);
	while (q--){
		int op,l,r;
		cin >> op >> l >> r;
		if (op == 1){
			int x;
			cin >> x;
			mod(l,r,1,n,1,x);
		}else if (op == 2){
			int x;
			cin >> x;
			add(l,r,1,n,1,x);
		}else{
			printf("%lld\n",query(l,r,1,n,1));
		}
	}
	return 0;
}