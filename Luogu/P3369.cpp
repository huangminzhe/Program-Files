#include <bits/stdc++.h>
using namespace std;
class BST{
	protected:
		struct node{
			size_t l,r,k;	// k：关键码
			int x;
			int cnt,size;	// cnt：个数；size：子树大小
		};
		vector<node> nodes = {{0,0,0,0,0,0}};
		size_t root;
		const int INF = 0x7fffffff;
		size_t randk(){
			srand(time(0) * size());
			return rand();
		}
		size_t push(int x){
			nodes.push_back({0,0,randk(),x,1,1});
			return nodes.size() - 1;
		}
		void upd(size_t p){
			nodes[p].size = nodes[nodes[p].l].size + nodes[nodes[p].r].size + nodes[p].cnt;
		}
		void build(){
			push(-INF),push(INF);
			root = 1,nodes[root].r = 2;
			upd(root);
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
			return max(0ULL,nodes.size() - 3);
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
	private:
		size_t v2r(size_t p,int x){
			if (!p)	return 0;
			if (x == nodes[p].x)	return nodes[nodes[p].l].size + 1;
			if (x < nodes[p].x)	return v2r(nodes[p].l,x);
			return v2r(nodes[p].r,x) + nodes[nodes[p].l].size + nodes[p].cnt;
		}
		int r2v(size_t p,size_t r){
			if (!p)	return INF;
			if (nodes[p].size >= r)	return nodes[p].x;
			if (nodes[nodes[p].l].size + nodes[p].x >= r)	return nodes[p].x;
			return r2v(nodes[p].r,r - nodes[nodes[p].l].size - nodes[p].cnt);
		}
		void ins(size_t &p,int x){
			if (!p){
				p = push(x);	// nodes[fa].l（或r）= p
				return ;
			}
			if (x == nodes[p].x){
				nodes[p].cnt++,
				upd(p);
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
	public:
		size_t find(int x){	// 返回值为x的排名
			return v2r(root,x);
		}
		int get(size_t r){	// 返回排名为p的值
			return r2v(root,r);
		}
		void zag(size_t &x){	// 左旋
			size_t y = nodes[x].r;
			nodes[x].r = nodes[y].l,
			nodes[y].l = x,
			x = y;
			upd(nodes[x].l),upd(y);
		}
		void zig(size_t &y){	// 右旋
			size_t x = nodes[x].l;
			nodes[y].l = nodes[x].r,
			nodes[x].r = x,
			y = x;
			upd(y),upd(nodes[x].r);
		}
		void ins(int x){
			ins(root,x);
		}
		int operator[](const size_t &p){
			return nodes[p].x;
		}
};
Treap a;
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		int op,x;
		cin >> op >> x;
		if (op == 1)	a.ins(x);
		else if (op == 2)	a.rm(x);
		else if (op == 3)	cout << a.find(x) << '\n';
		else if (op == 4)	cout << a.get(x) << '\n';
		else if (op == 5)	cout << a[a.pre(x)] << '\n';
		else	cout << a[a.nxt(x)] << '\n';
	}
	return 0;
}