#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n,q,a[N],b[N],c[N];
ll sum;
int main(int argc, char **argv){
	cin >> n >> q;
	for (int i = 1;i <= n;i++)	cin >> a[i];
	for (int i = 1;i <= n;i++)	cin >> b[i],c[i] = min(a[i],b[i]),sum += c[i];
	while (q--){
		char op;
		int x,v;
		cin >> op >> x >> v;
		if (op == 'A'){
			a[x] = v;
			sum += min(a[x],b[x]) - c[x];
			c[x] = min(a[x],b[x]);
		}else{
			b[x] = v;
			sum += min(a[x],b[x]) - c[x];
			c[x] = min(a[x],b[x]);
		}
		cout << sum << '\n';
	}
	return 0;
}