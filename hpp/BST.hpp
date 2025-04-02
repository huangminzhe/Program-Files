#ifndef BST_HPP
#define BST_HPP

#include <bits/stdc++.h>
using namespace std;
class BST{
	private:
		struct node{
			size_t l,r;
			int x;
		};
		vector<node> nodes = {{0,0,0}};
		size_t root;
		int INF = 0x7fffffff;
		size_t push(int x){
			nodes.push_back({0,0,x});
			return nodes.size();
		}
		size_t get(size_t p,int x){
			if (!p)	return 0;
			if (x == nodes[p].x)	return p;
			return (x < nodes[p].x?get(nodes[p].l,x):get(nodes[p].r,x));
		}
		void ins(size_t &p,int x){
			if (!p){
				p = push(x);
				return ;
			}
			if (x < nodes[p].x)	ins(nodes[p].l,x);
			else	ins(nodes[p].r,x);
		}
	public:
		BST(){
			build();
		}
		void build(){
			push(-INF),push(INF);
			root = 1,nodes[root].r = 2;
		}
		size_t find(int x){
			return get(root,x);
		}
		void ins(int x){
			ins(root,x);
		}
};

#endif