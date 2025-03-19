#ifndef HEAP_H
#define HEAP_H

#include <bits/stdc++.h>
using namespace std;
template<typename tp>
class Heap{
	private:
		vector<tp> hp;
		int n,sz;
		bool (*cmp)(tp,tp);
		void down(int p){
			while (p << 1 <= n){
				int t = p << 1;
				if (t < n && (*cmp)(hp[t + 1],hp[t])) t++;
				if ((*cmp)(hp[t],hp[p])){
					swap(hp[t],hp[p]);
					p = t;
				}else	break;
			}
		}
		void up(int p){
			while (p > 1 && (*cmp)(hp[p],hp[p >> 1])){
				swap(hp[p],hp[p >> 1]);
				p >>= 1;
			}
		}
		void insert(tp x){
			hp[++n] = x;
			int p = n;
			up(p);
		}
		void pop_head(){
			hp[1] = hp[n--];
			int p = 1;
			down(p);
		}
		void remove(int p){
			hp[p] = hp[n--];
			down(p);
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

#endif