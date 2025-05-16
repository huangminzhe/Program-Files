#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 55,INF = 0x7fffffff;
int n,a[N * 2],dpx[N * 2][N * 2],dpn[N * 2][N * 2],mx;
bool edges[N * 2];
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		char c;
		cin >> c >> a[i];
		if (c == 'x')	edges[i] = 1;
		a[n + i] = a[i],edges[n + i] = edges[i];
	}
	fill(&dpx[0][0],&dpx[n * 2][n * 2],-INF / 2);
	fill(&dpn[0][0],&dpn[n * 2][n * 2],INF / 2);
	for (int i = 1;i <= 2 * n;i++){
		dpx[i][i] = dpn[i][i] = a[i];
	}
	for (int k = 1;k < n;k++){
		for (int i = 1;i <= 2 * n - k;i++){
			int j = i + k;
			for (int h = i;h < j;h++){
				if (edges[h + 1]){
					dpx[i][j] = max({dpx[i][j],
									 dpx[i][h] * dpx[h + 1][j],
									 dpx[i][h] * dpn[h + 1][j],
									 dpn[i][h] * dpx[h + 1][j],
									 dpn[i][h] * dpn[h + 1][j]});
					dpn[i][j] = min({dpn[i][j],
									 dpx[i][h] * dpx[h + 1][j],
									 dpx[i][h] * dpn[h + 1][j],
									 dpn[i][h] * dpx[h + 1][j],
									 dpn[i][h] * dpn[h + 1][j]});
				}else{
					dpx[i][j] = max(dpx[i][j],dpx[i][h] + dpx[h + 1][j]);
					dpn[i][j] = min(dpn[i][j],dpn[i][h] + dpn[h + 1][j]);
				}
			}
		}
	}
	for (int i = 1;i <= n;i++){
		// printf("%d\n",dpx[i][n + i - 1]);
		mx = max(mx,dpx[i][n + i - 1]);
	}
	cout << mx << '\n';
	for (int i = 1;i <= n;i++){
		if (dpx[i][n + i - 1] == mx)	cout << i << ' ';
	}
	return 0;
}