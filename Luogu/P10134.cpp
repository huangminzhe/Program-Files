#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
struct point{
	int u,v;
};
int n,q,c,kw[N],to[N],pre[N],a[N],fr[N];
vector<point> g;
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		g = vector<point>(1,{0,0});
		cin >> n >> q >> c;
		for (int i = 1;i <= n;i++){
			cin >> a[i];
			kw[i] = a[i]?kw[i - 1]:i;
		}
		for (int i = 1;i <= q;i++){
			int u,v;
			cin >> u >> v;
			g.push_back({u,v - 1});
		}

		for (int i = 1;i <= n;i++)	to[i] = i + 1;
		for (int i = 1;i <= q;i++){
			to[g[i].u] = g[i].v + 1;
			fr[g[i].v + 1] = 1;
		}

		pre[0] = 1;
		for (int i = 1;i <= n;i = to[i]){
			pre[i] = pre[i - 1] + fr[i];
			for (int j = i;j < to[i];j++){
				pre[i] = max(pre[i],a[j]);
			}
			for (int j = i;j < to[i];j++){
				pre[j] = pre[i];
			}
		}

		bool f = 0;
		for (int i = 1;i <= n;i++){
			if (!a[i]){
				a[i] = pre[i - 1] == pre[i]?1:pre[i];
			}else if (pre[i - 1] != pre[i] && pre[i] > a[i]){
				if (kw[i])	a[kw[i]] = pre[i];
			}
			if (a[i] > c)	f = 1;
			pre[i] = max({pre[i],pre[i - 1],a[i]});
			fr[i] = 0;
		}

		for (int i = 1;i <= n;i++){
			pre[i] = max(pre[i - 1],a[i]);
		}
		for (int i = 1;i <= q;i++){
			if (pre[g[i].u] < pre[g[i].v] || pre[g[i].u] == pre[g[i].v + 1])	f = 1;
		}

		if (f)	cout << "-1\n";
		else{
			for (int i = 1;i <= n;i++){
				cout << a[i] << ' ';
			}
			cout << '\n';
		}
	}
	return 0;
}