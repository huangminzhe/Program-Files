#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
template<typename tp>
class Heap{
	private:
		tp _;
		vector<tp> hp = {_};
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

bool cmp(pll a,pll b){
	if (a.first == b.first) return a.second < b.second;
	return a.first < b.first;
}
Heap<pll> hp(cmp);
ll ans;
int main(int argc, char **argv){
	// freopen("d:\\Users\\Administrator\\Downloads\\P2168_4.in","r",stdin);
	int n,k;
	cin >> n >> k;
	for (int i = 1;i <= n;i++){
		ll x;
		cin >> x;
		hp.ins({x,0});
	}
	while ((hp.size() - 1) % (k - 1)) hp.ins({0,0});
	while (hp.size() >= k){
		ll sum = 0,l = hp.top().second;
		for (int i = 1;i <= k;i++){
			sum += hp.top().first;
			l = max(l,hp.top().second);
			hp.pop();
		}
		ans += sum;
		hp.ins({sum,l + 1});
	}
	cout << ans << '\n' << hp.top().second;
	return 0;
}