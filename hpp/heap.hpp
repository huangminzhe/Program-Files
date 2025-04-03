#ifndef HEAP_HPP
#define HEAP_HPP

#include <bits/stdc++.h>
using namespace std;
template<typename tp>
class Heap{
	private:
		vector<tp> hp = {0};
		bool (*cmp)(tp,tp);
		void down(size_t p){
			size_t n = size();
			while (p << 1 <= n){
				size_t t = p << 1;
				if (t < n && (*cmp)(hp[t + 1],hp[t])) t++;
				if ((*cmp)(hp[t],hp[p])){
					swap(hp[t],hp[p]);
					p = t;
				}else	break;
			}
		}
		void up(size_t p){
			while (p > 1 && (*cmp)(hp[p],hp[p >> 1])){
				swap(hp[p],hp[p >> 1]);
				p >>= 1;
			}
		}
		tp get(size_t p){
			return hp[p];
		}
	public:
		Heap(){
			cmp = [](tp a,tp b){return a > b;};
		}
		Heap(bool (*f)(tp,tp)){
			cmp = f;
		}
		size_t size(){
			return hp.size() - 1;
		}
		void ins(tp x){
			hp.emplace_back(x);
			up(size());
		}
		void rm(size_t p){
			swap(hp[p],hp[size()]);
			hp.pop_back();
			down(p);
		}
		void pop(){
			rm(1);
		}
		tp top(){
			return get(1);
		}
		tp operator[](size_t p){
			return get(p);
		}
};

#endif