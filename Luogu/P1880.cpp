#include <bits/stdc++.h>
using namespace std;
const int N = 105,INF = 0x7fffffff;
int a[N * 2],dpn[N * 2][N * 2],dpx[N * 2][N * 2],b[N * 2],mn = INF,mx;
int main(int argc, char **argv){
	memset(dpn,0x3f,sizeof(dpn));
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		a[i + n] = a[i];
	}
	for (int i = 1;i <= n * 2;i++){
		b[i] = b[i - 1] + a[i];
		dpn[i][i] = 0;
	}
	for (int k = 1;k < n;k++){
		for (int i = 1;i <= 2 * n - k;i++){
			int j = i + k;
			for (int k = i;k < j;k++){
				dpn[i][j] = min(dpn[i][j],dpn[i][k] + dpn[k + 1][j] + b[j] - b[i - 1]);
				dpx[i][j] = max(dpx[i][j],dpx[i][k] + dpx[k + 1][j] + b[j] - b[i - 1]);
			}
		}
	}
	for (int i = 1;i <= n;i++){
		mn = min(mn,dpn[i][i + n - 1]);
		mx = max(mx,dpx[i][i + n - 1]);
	}
	cout << mn << '\n' << mx;
	return 0;
}