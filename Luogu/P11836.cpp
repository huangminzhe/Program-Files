#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 5;
int n,m,sum;
bool a[N][N];
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			char c = getchar();
			if (c == '#')	a[i][j] = 1,sum++;
		}
		getchar();
	}
	int ans;
	for (ans = 1;ans <= min(sum,n * n - sum);ans++){
		int mx = 0;
		for (int i = 1;i <= n / 2;i++){
			for (int j = 1;j <= n / 2;j++){
				int cnt = a[i][j] + a[n - i + 1][1] + a[1][n - i + 1] + a[n - i + 1][n - i + 1];
				mx += min(cnt,4 - cnt);
				if (mx > ans)	break;
			}
			if (mx > ans)	break;
		}
		if (mx == ans)	break;
	}
	cout << ans << '\n';
	while (m--){
		int x,y;
		cin >> x >> y;
		a[x][y] = !a[x][y];
		for (ans = 1;ans <= min(sum,n * n - sum);ans++){
			int mx = 0;
			for (int i = 1;i <= n / 2;i++){
				for (int j = 1;j <= n / 2;j++){
					int cnt = a[i][j] + a[n - i + 1][1] + a[1][n - j + 1] + a[n - i + 1][n - j + 1];
					mx += min(cnt,4 - cnt);
					if (mx > ans)	break;
				}
				if (mx > ans)	break;
			}
			if (mx == ans)	break;
		}
		cout << ans << '\n';
	}
	return 0;
}