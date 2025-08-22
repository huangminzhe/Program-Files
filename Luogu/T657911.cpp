#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
const ll INF = 1e18;
ll n,q,d[N][N],a[N][N];
int main(int argc, char **argv){
	cin >> n >> q;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			cin >> d[i][j];
			if (d[i][j] == -1)	d[i][j] = INF;
		}
	}
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			cin >> a[i][j];
		}
	}
	for (int k = 1;k <= n;k++)
		for (int i = 1;i <= n;i++)
			for (int j = 1;j <= n;j++)
				if (i != k && j != k && a[i][k] != -1 && a[k][j] != -1)	d[i][j] = min(d[i][j],a[i][k] + a[k][j]);
	while (q--){
		int u,v;
		cin >> u >> v;
		if (d[u][v] == INF)	cout << "-1\n";
		else	cout << d[u][v] << '\n';
	}
	return 0;
}