#include <bits/stdc++.h>
using namespace std;
const int N = 105,INF = 0x7fffffff;
int d[N][N],f[N][N];
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	for (int i = 1;i <= n;i++)	fill(f[i] + 1,f[i] + n + 1,INF / 2);
	for (int i = 1;i <= m;i++){
		int u,v,w;
		cin >> u >> v >> w;
		f[u][v] = min(f[u][v],w);
		f[v][u] = min(f[v][u],w);
	}

	for (int k = 1;k <= n;k++){
		for (int i = 1;i <= n;i++){
			for (int j = 1;j <= n;j++){
				f[i][j] = min(f[i][k] + f[k][j],f[i][j]);
			}
		}
	}
	int ans = INF;
	for (int x = 1;x <= n;x++){
		for (int y = 1;y <= n;y++){
			for (int i = 1;i <= n;i++){
				for (int j = 1;j <= n;j++){
					d[i][j] = f[i][j];
				}
			}
			d[x][y] = d[y][x] = 0;
			for (int i = 1;i <= n;i++){
				for (int j = 1;j <= n;j++){
					d[i][j] = min(d[i][j],d[i][x] + d[x][j]);
				}
			}
			for (int i = 1;i <= n;i++){
				for (int j = 1;j <= n;j++){
					d[i][j] = min(d[i][j],d[i][y] + d[y][j]);
				}
			}
			int sum = 0;
			for (int i = 1;i <= n;i++){
				for (int j = 1;j < i;j++){
					sum += d[i][j];
				}
			}
			ans = min(sum,ans);
		}
	}
	cout << ans;
	return 0;
}