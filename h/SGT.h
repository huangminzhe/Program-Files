#include <bits/stdc++.h>
using namespace std;
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
			pd(l,r,p)
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