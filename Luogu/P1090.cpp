#include <bits/stdc++.h>
using namespace std;
template<typename tp>
class Heap{
	private:
		vector<tp> hp = {0};
		bool (*cmp)(tp,tp);
		void down(int p){
			int n = size();
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
		Heap(){
			cmp = [](tp a,tp b){return a > b;};
		}
		Heap(bool (*f)(tp,tp)){
			cmp = f;
		}
		int size(){
			return hp.size() - 1;
		}
		void ins(tp x){
			hp.emplace_back(x);
			up(size());
		}
		void rm(int p){
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
		tp operator[](int p){
			return get(p);
		}
};

bool cmp(int a,int b){return a < b;}
Heap<int> hp(cmp);
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		int x;
		cin >> x;
		hp.ins(x);
	}
	int sum = 0;
	while (hp.size() > 1){
		int a = hp.top();
		hp.pop();
		int b = hp.top();
		hp.pop();
		sum += a + b;
		hp.ins(a + b);
	}
	cout << sum;
	return 0;
}