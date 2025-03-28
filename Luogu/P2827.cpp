#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,q,u,v,t;
int tim;
struct ew{
	ll len;
	int sub;
	// 当前长度=len+(tim-sub)*q
};
bool operator<(const ew &a,const ew &b){
	return ((a.len + (tim - a.sub) * q) < (b.len + (tim - b.sub) * q)?1:0);
}
priority_queue<ew> hp;
int main(int argc, char **argv){
	cin >> n >> m >> q >> u >> v >> t;
	for (int i = 1;i <= n;i++){
		int x;
		scanf("%d",&x);
		hp.push({x,0});
	}
	for (tim = 0;tim < m;tim++){
		ew x = hp.top();
		hp.pop();
		ll len = x.len + (tim - x.sub) * q;
		printf("%lld %d\n",len,x.sub);
		hp.push({len * u / v,x.sub + 1});
		hp.push({len - len * u / v,x.sub + 1});
	}
	cout << '\n';
	return 0;
}