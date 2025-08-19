#ifndef DSU_HPP
#define DSU_HPP

#include <bits/stdc++.h>
using namespace std;
template<typename tp>
class DSU{
	private:
		unordered_map<tp,tp> fa;
	public:
		void init(tp x){
			fa[x] = x;
		}
		tp find(tp x){
			if (fa[x] == x)	return x;
			return fa[x] = find(fa[x]);
		}
		void merge(tp x,tp y){
			fa[find(y)] = find(x);
		}
};

#endif