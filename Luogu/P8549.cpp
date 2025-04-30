#include <bits/stdc++.h>
using namespace std;
bool x[20][20],y[20][20];
int z[5][5];
int a[20][20],n;
void zig(int u,int v){
	int tmp[5][5] = {{0}},
		up = u * n - n + 1,dwn = u * n,
		lft = v * n - n + 1,rt = v * n;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			tmp[j][n - j + 1] = a[up + i - 1][lft + j - 1];
		}
	}
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			a[up + i - 1][lft + j - 1] = tmp[i][j];
		}
	}
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			printf("%d ",tmp[i][j]);
		}
		cout << '\n';
	}
}
bool dfs(int u,int v){
	if (u > n){
		int sum = 0;
		for (int i = 1;i <= n;i++)	
			for (int j = 1;j <= n;j++)
				sum += z[i][j];
		cout << sum << '\n';
		for (int i = 1;i <= n;i++){
			for (int j = 1;j <= n;j++){
				for (int k = 1;k <= z[i][j];k++){
					cout << i << ' ' << j << '\n';
				}
			}
		}
		return 1;
	}
	int up = u * n - n + 1,dwn = u * n,
		lft = v * n - n + 1,rt = v * n;
	bool f[4] = {0};
	for (int I = 0;I < 4;I++){
		// printf(" %d %d %d\n",u,v,I);
		for (int i = up;i <= dwn;i++){
			for (int j = lft;j <= rt;j++){
				if (x[i][a[i][j]] || 
					y[j][a[i][j]])
					f[I] = 1;
				x[i][a[i][j]] = y[j][a[i][j]] = 1;
			}
		}
		z[u][v] = I;
		if (!f[I])
			if (dfs(v == n?u + 1:u,v == n?1:v + 1))	return 1;
		for (int i = up;i <= dwn;i++){
			for (int j = lft;j <= rt;j++){
				x[i][a[i][j]] = y[j][a[i][j]] = 0;
			}
		}
		zig(u,v);
	}
	if (f[0] && f[1] && f[2] && f[3])	return 0;
}
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n * n;i++){
		for (int j = 1;j <= n * n;j++){
			char c;
			// printf("%d %d\n",i,j);
			cin >> c;
			if (c <= '9')	a[i][j] = c - '0';
			else	a[i][j] = c - 'A' + 10;
		}
	}
	if (!dfs(1,1))	cout << -1;
	return 0;
}