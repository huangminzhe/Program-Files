#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
struct tp{
	ll t;
	int x,y;
	bool operator< (const tp a) const{
		return t > a.t;
	}
};
ll p[N],ans[N];
int s[N],n,pre[N],nxt[N];
inline ll calc(int x,int y){
	return ceil(1.0 * (p[y] - p[x]) / (s[x] + s[y])) * 2 - (x & 1);
}
void init(){
	memset(ans,0,sizeof ans);
	for (int i = 1;i <= n;i++)	pre[i] = i - 1,nxt[i] = i + 1;
}
void solve(){
	priority_queue<tp> q;
	for (int i = 1;i < n;i++)	q.push({calc(i,i + 1),i,i + 1});
	while (!q.empty()){
		int x = q.top().x,y = q.top().y;ll t = q.top().t;
		q.pop();
		if (ans[x] || ans[y])	continue;
		ans[x] = t,ans[y] = t;
		if (pre[x] > 0 && nxt[y] <= n)	q.push({calc(pre[x],nxt[y]),pre[x],nxt[y]});
		nxt[pre[x]] = nxt[x],pre[nxt[x]] = pre[x];
		nxt[pre[y]] = nxt[y],pre[nxt[y]] = pre[y];
	}
	for (int i = 1;i <= n;i++){
		cout << ans[i] << ' ';
	}
	cout << '\n';
}
int main(int argc, char **argv){
// 	freopen("quantum.in","r",stdin);
// #ifndef LOCAL
// 	freopen("quantum.ans","w",stdout);
// #endif
	ios::sync_with_stdio(0),cin.tie(0);
	int t;
	cin >> t;
	while (t--){
		init();
		cin >> n;
		for (int i = 1;i <= n;i++)	cin >> p[i];
		for (int i = 1;i <= n;i++)	cin >> s[i];
		solve();
	}
	return 0;
}