#include <bits/stdc++.h>
using namespace std;
const int INF = 0x7fffffff;
int z[5][5][20],mn = INF;
int a[20][20],n;
pair<int,int> p[50],ans[50];
void zig(int x,int y){
	int tmp[5][5] = {{0}},
		up = x * n - n + 1,dwn = x * n,
		lft = y * n - n + 1,rt = y * n;
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
	printf("%d %d\n",x,y);
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			printf("%d ",tmp[i][j]);
		}
		cout << '\n';
	}
}
bool check(int u,int v){
	int up = u * n - n + 1,dwn = u * n,
		lft = v * n - n + 1,rt = v * n;
	bool x[20][20] = {{0}},y[20][20] = {{0}};
	for (int i = 1;i <= dwn;i++){
		for (int j = 1;j <= rt;j++){
			if (x[i][a[i][j]] || y[j][a[i][j]])
				return 0;
			x[i][a[i][j]] = y[j][a[i][j]] = 1;
		}
	}
	return 1;
}
void dfs(int x,int y,int cnt){
	if (cnt >= mn)	return ;
	if (x > n){
		mn = cnt;
		for (int i = 1;i <= cnt;i++)
			ans[i] = p[i];
		return ;
	}
	for (int i = 0;i < 4;i++){
		p[cnt + i] = {x,y};
		if (check(x,y))
			dfs((y == n?x + 1:x),((y == n?1:y + 1)),cnt + i);
		zig(x,y);
	}
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
	cout << mn << '\n';
	for (int i = 1;i <= mn;i++){
		cout << ans[i].first << ' ' << ans[i].second << '\n';
	}
	return 0;
}