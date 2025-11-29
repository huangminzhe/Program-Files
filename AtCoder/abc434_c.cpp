#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
struct scs{
	int t,l,u;
}a[N];
int n,h;
bool cmp(scs b,scs c){
	return b.t < c.t;
}
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		cin >> n >> h;
		a[0] = {0,h,h};
		for (int i = 1;i <= n;i++){
			cin >> a[i].t >> a[i].l >> a[i].u;
		}
		sort(a + 1,a + n + 1,cmp);
		vector<int> mx(n + 1),mn(n + 1);
		mx[0] = mn[0] = h;
		for (int i = 1;i <= n;i++){
			if (mx[i - 1] + a[i].t - a[i - 1].t < a[i].l || 
				mn[i - 1] - a[i].t + a[i - 1].t > a[i].u)	goto no;
			mx[i] = min(mx[i - 1] + a[i].t - a[i - 1].t,a[i].u);
			mn[i] = max(mn[i - 1] - a[i].t + a[i - 1].t,a[i].l);
		}
		cout << "Yes\n";
		goto end;
		no:
		cout << "No\n";
		end:
	}
	return 0;
}