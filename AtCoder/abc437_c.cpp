#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5;
struct deer{
	int w,p;
}a[N];
int n;
bool cmp(deer b,deer c){
	return b.w + b.p < c.w + c.p;
}
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		ll sumwp = 0,sump = 0;
		int cnt = 0;

		cin >> n;
		for (int i = 1;i <= n;i++){
			cin >> a[i].w >> a[i].p;
			sump += a[i].p;
		}
		sort(a + 1,a + n + 1,cmp);
		for (int i = 1;sump >= sumwp && i <= n;i++,cnt++){
			sumwp += a[i].w + a[i].p;
		}
		cout << cnt - 1 << '\n';
	}
	return 0;
}