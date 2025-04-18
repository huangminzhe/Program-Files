#ifndef TREAP_HPP
#define TREAP_HPP

#include <bits/stdc++.h>
using namespace std;
template<int SIZE = int(1e7) + 5>
class Treap{
	private:
		struct node{
			int l,r;
			int k,x;	// k：关键码
			int cnt,size;	// cnt：个数；size：子树大小
		}nodes[SIZE];
		int root,tot,INF = 0x7fffffff;
		int push(int x){
			nodes[++tot].k = rand();
			nodes[tot].x = x;
			nodes[tot].cnt = 1;
			nodes[tot].size = 1;
			return tot;
		}
		void upd(int p){
			nodes[p].size = nodes[nodes[p].l].size + nodes[nodes[p].r].size + nodes[p].cnt;
		}
		void ins(int &p,int x){
			if (!p){
				p = push(x);	// nodes[fa].l（或r）= p
				return ;
			}
			nodes[p].size++;
			if (x == nodes[p].x){
				nodes[p].cnt++;
				return ;
			}
			if (x < nodes[p].x){
				ins(nodes[p].l,x);
				if (nodes[p].k < nodes[nodes[p].l].k)	zig(p);
			}else{
				ins(nodes[p].r,x);
				if (nodes[p].k < nodes[nodes[p].r].k)	zag(p);
			}
		}
		void rm(int &p,int x){
			if (!p)	return ;
			nodes[p].size--;
			if (x == nodes[p].x){
				if (nodes[p].cnt > 1){
					nodes[p].cnt--;
					return ;
				}
				if (!(nodes[p].l && nodes[p].r))	p = nodes[p].l + nodes[p].r;
				else if (nodes[nodes[p].l].k > nodes[nodes[p].r].k){
					zig(p);
					rm(nodes[p].r,x);
				}else{
					zag(p);
					rm(nodes[p].l,x);
				}
				return ;
			}
			if (x < nodes[p].x)	rm(nodes[p].l,x);
			else	rm(nodes[p].r,x);
		}
		int v2r(int p,int x){
			if (!p)	return 1;	// 如果x不在合集，得多返回1（定义）
			if (x == nodes[p].x)	return nodes[nodes[p].l].size + 1;
			if (x < nodes[p].x)	return v2r(nodes[p].l,x);
			return v2r(nodes[p].r,x) + nodes[nodes[p].l].size + nodes[p].cnt;
		}
		int r2v(int p,int r){
			if (!p)	return 0;
			if (nodes[nodes[p].l].size >= r)	return r2v(nodes[p].l,r);
			if (nodes[nodes[p].l].size + nodes[p].cnt >= r)	return nodes[p].x;
			return r2v(nodes[p].r,r - nodes[nodes[p].l].size - nodes[p].cnt);
		}
		void zig(int &p){	// 右旋
			int q = nodes[p].l;
			nodes[p].l = nodes[q].r,
			nodes[q].r = p,
			nodes[q].size = nodes[p].size;
			upd(p);
			p = q;
		}
		void zag(int &p){	// 左旋
			int q = nodes[p].r;
			nodes[p].r = nodes[q].l,
			nodes[q].l = p,
			nodes[q].size = nodes[p].size;
			upd(p);
			p = q;
		}
	public:
		Treap(){
			srand(time(0));
		}
		void ins(int x){
			ins(root,x);
		}
		void rm(int x){
			rm(root,x);
		}
		int pre(int x){
			int p = root;
			int res = -INF;
			while (p){
				if (nodes[p].x < x)	res = nodes[p].x,p = nodes[p].r;
				else	p = nodes[p].l;
			}
			return res;
		}
		int nxt(int x){
			int p = root;
			int res = INF;
			while (p){
				if (nodes[p].x > x)	res = nodes[p].x,p = nodes[p].l;
				else	p = nodes[p].r;
			}
			return res;
		}
		int find(int x){	// 返回值x的排名（定义为比x小的数的个数+1）
			return v2r(root,x);
		}
		int get(int r){	// 返回排名r的值
			return r2v(root,r);
		}
};
template<int SIZE = int(1e7) + 5>
class fhq_Treap{
	private:
		struct node{
			int l,r;
			int k,x;
			int size;
		}nodes[SIZE];
		int root,tot,INF = 0x7fffffff;
		int push(int x){
			nodes[++tot] = {0,0,rand(),x,1};
			return tot;
		}
		void upd(int p){
			nodes[p].size = nodes[nodes[p].l].size + nodes[nodes[p].r].size + 1;
		}
		void split(int p,int x,int &l,int &r){
			if (!p)	l = r = 0;
			else if (nodes[p].x <= x){
				l = p;
				split(nodes[p].r,x,nodes[l].r,r);
			}else{
				r = p;
				split(nodes[p].l,x,l,nodes[r].l);
			}
			upd(p);
		}
		int merge(int l,int r){
			if (!l || !r)	return l + r;
			if (nodes[l].k < nodes[r].k){
				nodes[l].r = merge(nodes[l].r,r);
				upd(l);
				return l;
			}else{
				nodes[r].l = merge(l,nodes[r].l);
				upd(r);
				return r;
			}
		}
		int get(int p,int x){
			int lsz = nodes[nodes[p].l].size;
			if (x == lsz + 1)	return nodes[p].x;
			if (x <= lsz)	return get(nodes[p].l,x);
			return get(nodes[p].r,x - lsz - 1);
		}
	public:
		fhq_Treap(){
			srand(time(0));
		}
		int size(){
			return nodes[root].size;
		}
		void ins(int x){
			int l,r;
			split(root,x,l,r);
			root = merge(merge(l,push(x)),r);
		}
		void rm(int x){
			int l,r1,r2;
			split(root,x,l,r1);
			split(l,x - 1,l,r2);
			r2 = merge(nodes[r2].l,nodes[r2].r);
			root = merge(merge(l,r2),r1);
		}
		int find(int x){	// 返回值x的排名（定义为比x小的数的个数+1）
			int l,r;
			split(root,x - 1,l,r);
			int res = nodes[l].size + 1;
			root = merge(l,r);
			return res;
		}
		int get(int r){	// 返回排名r的值
			return get(root,r);
		}
		int pre(int x){
			int l,r;
			split(root,x - 1,l,r);
			int res = get(l,nodes[l].size);
			root = merge(l,r);
			return res;
		}
		int nxt(int x){
			int l,r;
			split(root,x,l,r);
			int res = get(r,1);
			root = merge(l,r);
			return res;
		}
};

#endif