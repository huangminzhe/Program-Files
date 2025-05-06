#include <bits/stdc++.h>
using namespace std;
const int INF = 0x7fffffff;
bool x[20][20],y[20][20];
int z[5][5][20],mn = INF;
int a[20][20],n;
void zig(int u,int v){
	int tmp[5][5] = {{0}},
		up = u * n - n + 1,dwn = u * n,
		lft = v * n - n + 1,rt = v * n;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			tmp[n - j + 1][i] = a[up + i - 1][lft + j - 1];
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
void dfs(int u,int v,int cnt){
	if (cnt >= mn)	return ;
	if 
}
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n * n;i++){
		for (int j = 1;j <= n * n;j++){
			char c;
			// printf("%d %d\n",i,j);
			cin >> c;
			if (c <= '9')
				a[i][j] = c - '0';
			else
				a[i][j] = c - 'A' + 10;
			if (z[(i - 1) / n + 1][(j - 1) / n + 1][a[i][j]]){
				cout << -1;
				return 0;
			}
			z[(i - 1) / n + 1][(j - 1) / n + 1][a[i][j]] = 1;
		}
	}
	dfs(1,1,0);
	if (mn == INF)	mn = -1;
	cout << mn;
	for (int i = 1;i <= mn;i++){
	}
	return 0;
}