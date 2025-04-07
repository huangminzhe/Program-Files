#ifndef TREAP_HPP
#define TREAP_HPP

#include <bits/stdc++.h>
using namespace std;
class BST{
	protected:
		struct node{
			size_t l,r;
			int x;
		};
		vector<node> nodes = {{0,0,0}};
		size_t root;
		const int INF = 0x7fffffff;
		size_t push(int x){
			nodes.push_back({0,0,x});
			return nodes.size() - 1;
		}
		size_t get(size_t p,int x){
			if (!p)	return 0;
			if (x == nodes[p].x)	return p;
			return (x < nodes[p].x?get(nodes[p].l,x):get(nodes[p].r,x));
		}
		void ins(size_t &p,int x){
			if (!p){
				p = push(x);	// nodes[fa].l（或r）= p
				return ;
			}
			if (x < nodes[p].x)	ins(nodes[p].l,x);
			else	ins(nodes[p].r,x);
		}
		void rm(size_t &p,int x){
			if (!p)	return ;
			if (nodes[p].x == x){
				if (nodes[p].l && nodes[p].r){	// 有两个子树
					size_t scs = nodes[p].r;
					while (nodes[scs].l)	scs = nodes[scs].l;
					rm(nodes[p].r,nodes[scs].x);
					nodes[scs].l = nodes[p].l,nodes[scs].r = nodes[p].r;
					p = scs;
				}else{
					if (nodes[p].l){	// 只有左子树
						p = nodes[p].l;	// nodes[fa].l（或r）= nodes[p].l;
					}else{	// 只有右子树
						p = nodes[p].r;	// nodes[fa].l（或r）= nodes[p].l;
					}
				}
				return ;
			}
			if (x < nodes[p].x)	rm(nodes[p].l,x);
			else	rm(nodes[p].r,x);
		}
	public:
		BST(){
			build();
		}
		size_t size(){
			return nodes.size() - 3;
		}
		void build(){
			push(-INF),push(INF);
			root = 1,nodes[root].r = 2;
		}
		size_t find(int x){	// 返回值为x的编号
			return get(root,x);
		}
		void ins(int x){
			ins(root,x);
		}
		size_t nxt(int x){
			size_t mni = 2,p = root;	// nodes[2].x == INF;
			while (p){
				if (nodes[p].x == x){
					if (nodes[p].r){
						p = nodes[p].r;
						while (nodes[p].l)	p = nodes[p].l;
						mni = p;
					}
					break;
				}
				if (nodes[p].x > x && nodes[p].x < nodes[mni].x)	mni = p;
				p = x < nodes[p].x?nodes[p].l:nodes[p].r;
			}
			return mni;
		}
		size_t pre(int x){
			size_t mxi = 1,p = root;	// nodes[1].x == -INF
			while (p){
				if (nodes[p].x == x){
					if (nodes[p].l){
						p = nodes[p].l;
						while (nodes[p].r)	p = nodes[p].r;
						mxi = p;
					}
					break;
				}
				if (nodes[p].x < x && nodes[p].x > nodes[mxi].x)	mxi = p;
				p = x < nodes[p].x?nodes[p].l:nodes[p].r;
			}
			return mxi;
		}
		void rm(int x){
			rm(root,x);
		}
		int get(size_t p){	// 返回编号为p的值
			return nodes[p].x;
		}
};
class Treap:public BST{
	
};

#endif