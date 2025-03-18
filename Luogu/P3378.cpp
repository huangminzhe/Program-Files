#include <bits/stdc++.h>
using namespace std;
template<typename tp>
class Heap{
	private:
		vector<tp> hp;
		int n,sz;
		bool (*cmp)(tp,tp);
		void insert(tp x){
			hp[++n] = x;
			int p = n;
			while (p > 1 && (*cmp)(hp[p],hp[p >> 1])){
				swap(hp[p],hp[p >> 1]);
				p >>= 1;
			}
		}
		void pop_head(){
			hp[1] = hp[n--];
			int p = 1;
			while (p << 1 <= n){
				int t = p << 1;
				if (t < n && (*cmp)(hp[t + 1],hp[t])) t++;
				if ((*cmp)(hp[t],hp[p])){
					swap(hp[t],hp[p]);
					p = t;
				}else	break;
			}
		}
		void remove(int p){
			hp[p] = hp[n--];
			while (p << 1 <= n){
				int t = p << 1;
				if (t < n && (*cmp)(hp[t + 1],hp[t])) t++;
				if ((*cmp)(hp[t],hp[p])){
					swap(hp[t],hp[p]);
					p = t;
				}else	break;
			}
		}
		tp get(int p){
			return hp[p];
		}
	public:
		Heap(int len){
			n = 0;
			sz = 1;
			while (sz <= len) sz <<= 1;
			hp.resize(sz);
			(*cmp) = [](tp a,tp b){return a > b;};
		}
		Heap(int len,bool (*f)(tp,tp)){
			n = 0;
			sz = 1;
			while (sz <= len) sz <<= 1;
			hp.resize(sz);
			cmp = f;
		}
		void ins(tp x){
			insert(x);
		}
		void pop(){
			pop_head();
		}
		void rm(int p){
			remove(p);
		}
		tp top(){
			return get(1);
		}
};
bool cmp(int a,int b){
	return a < b;
}
Heap<int> h(1e6,cmp);
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		int op;
		cin >> op;
		if (op == 1){
			int x;
			cin >> x;
			h.ins(x);
		}else if (op == 2){
			printf("%d\n",h.top());
		}else{
			h.pop();
		}
	}
	return 0;
}