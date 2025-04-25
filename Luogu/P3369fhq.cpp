#include <bits/stdc++.h>
using namespace std;
template<int SIZE = int(1e7) + 5>
class fhq_Treap{
	private:
		struct node{
			int l,r;
			int k,x;
			int size;
		}nodes[SIZE];
		bool f[SIZE];	// 懒标记
		int b[SIZE];	// 懒标记值
		int root,tot,INF = 0x7fffffff;
		void pd(int p){
			if (!p || !f[p])	return ;
			nodes[p].x += b[p];
			f[nodes[p].l] = 1,b[nodes[p].l] += b[p];
			f[nodes[p].r] = 1,b[nodes[p].r] += b[p];
			f[p] = 0,b[p] = 0;
		}
		void upd(int p){
			nodes[p].size = nodes[nodes[p].l].size + nodes[nodes[p].r].size + 1;
		}
		int push(int x){
			nodes[++tot] = {0,0,rand(),x,1};
			return tot;
		}
		void split(int p,int x,int &l,int &r){
			if (!p){
				l = r = 0;
				return ;
			}
			pd(p);
			if (nodes[p].x <= x){
				l = p;
				split(nodes[p].r,x,nodes[p].r,r);
			}else{
				r = p;
				split(nodes[p].l,x,l,nodes[r].l);
			}
			upd(p);
		}
		int merge(int l,int r){
			if (!l || !r)	return l + r;
			if (nodes[l].k < nodes[r].k){
				pd(l);
				nodes[l].r = merge(nodes[l].r,r);
				upd(l);
				return l;
			}else{
				pd(r);
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
fhq_Treap<int(1e5) + 5> a;
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
		else if (op == 5)	cout << a.pre(x) << '\n';
		else	cout << a.nxt(x) << '\n';
	}
	return 0;
}