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
		void check_sz(){
			while (sz <= n) sz <<= 1;
			hp.resize(sz);
		}
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
			check_sz();
			hp[++n] = x;
			int p = n;
			up(p);
		}
		void pop(){
			hp[1] = hp[n--];
			int p = 1;
			down(p);
		}
		void rm(int p){
			hp[p] = hp[n--];
			down(p);
		}
		tp top(){
			return get(1);
		}
		size_t size(){
			return n;
		}
};

#endif