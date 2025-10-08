#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
ll a[N],b[N],c[N];
int n,q;
inline ll lowbit(ll x){
	return x & -x;
}
void addb(int i,ll x){
	for (;i <= n;i += lowbit(i)){
		b[i] += x;
	}
}
void addc(int i,ll x){
	for (;i <= n;i += lowbit(i)){
		c[i] += x;
	}
}
ll queryb(int x){
	ll res = 0;
	for (;x;x -= lowbit(x)){
		res += b[x];
	}
	return res;
}
ll queryc(int x){
	ll res = 0;
	for (;x;x -= lowbit(x)){
		res += c[x];
	}
	return res;
}
inline ll queryb(int l,int r){
	return queryb(r) - queryb(l - 1);
}
inline ll queryc(int l,int r){
	return queryc(r) - queryc(l - 1);
}
int main(int argc, char **argv){
#ifdef LOCAL
	// freopen("A3.in","r",stdin);
	// freopen("A.ans","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin >> n >> q;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		addb(i,a[i]);
		addc(i,a[i] * i); 
	}
	while (q--){
		string s;
		int i;
		cin >> s >> i;
		if (s == "Query"){
			cout << (i + 1) * queryb(i) - queryc(i) << '\n';
		}else{
			int x;
			cin >> x;
			addb(i,x - a[i]);
			addc(i,ll(x - a[i]) * i);
			a[i] = x; 
		}
	}
	return 0;
}