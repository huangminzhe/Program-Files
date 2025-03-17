#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n,m;
int b[N],w[N];
ll pb[N],pw[N],mx,mxpw;
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++)	cin >> b[i];
	for (int i = 1;i <= m;i++)	cin >> w[i];

	sort(b + 1,b + n + 1);
	sort(w + 1,w + m + 1);
	reverse(b + 1,b + n + 1);
	reverse(w + 1,w + m + 1);

	for (int i = 1;i <= n;i++)	pb[i] = pb[i - 1] + b[i];
	for (int i = 1;i <= m;i++)	pw[i] = pw[i - 1] + w[i];

	for (int i = 0;i <= n;i++){
		int j = min(i,m);
		mxpw = max(mxpw,pw[j]);
		mx = max(mx,pb[i] + mxpw);
	}
	cout << mx;
	return 0;
}