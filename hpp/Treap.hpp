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
		int root,tot;
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
	public:
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
		void ins(int x){
			ins(root,x);
		}
		void rm(int x){
			rm(root,x);
		}
		int pre(int x){
			int p = root;
			int res = 0;
			while (p){
				if (nodes[p].x < x)	res = nodes[p].x,p = nodes[p].r;
				else	p = nodes[p].l;
			}
			return res;
		}
		int nxt(int x){
			int p = root;
			int res = 0;
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

#endif