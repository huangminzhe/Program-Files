#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int a[N][N];
bool f[N][N];
int dx[] = {-1,1,0,0},dy[] = {0,0,-1,1};
int main(int argc, char **argv){
	int n,m,q;
	cin >> n >> m >> q;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= m;j++){
			cin >> a[i][j];
			a[i][j]--;
		}
	}
	while (q--){
		memset(f,0,sizeof f);
		int x,y;
		cin >> x >> y;
		int stp = 0;
		while (x && x <= n && y && y <= m && !f[x][y]){
			// printf("%d ",a[x][y]);
			f[x][y] = 1;
			int xi = x + dx[a[x][y]],yi = y + dy[a[x][y]];
			x = xi,y = yi;
			stp++;
		}
		if (f[x][y])	cout << "-1\n";
		else	cout << stp << '\n';
	}
	return 0;
}