#include <bits/stdc++.h>
using namespace std;
const int N = 20,INF = 0x7fffffff;
int w[N],n,m,ans = INF,a[N];
void dfs(int x,int cnt){
	if (cnt >= ans)	return ;
	if (x > n){
		ans = cnt;
		// ans = min(ans,cnt);
		return ;
	}
	for (int i = 1;i <= cnt;i++){
		if (a[i] + w[x] <= m){
			a[i] += w[x];
			dfs(x + 1,cnt);
			a[i] -= w[x];
		}
	}
	a[++cnt] = w[x];
	dfs(x + 1,cnt);
	a[cnt] = 0;
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		cin >> w[i];
	}
	sort(w + 1,w + n + 1);
	reverse(w + 1,w + n + 1);
	dfs(1,0);
	cout << ans;
	return 0;
}