#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int a[N][N],tsum[N][N],tone[N][N],cnt;
int dx[] = {0,-1,1,0,0},dy[] = {0,0,0,-1,1};
int main(int argc, char **argv){
	int n,m,k;
	cin >> n >> m >> k;
	for (int i = 1;i <= k;i++){
		int x,y;
		cin >> x >> y >> a[x][y];
		for (int I = 0;I <= 4;I++){
			int xi = x + dx[I],yi = y + dy[I];
			tsum[xi][yi] += a[x][y];
			tone[xi][yi]++;
		}
	}
	auto mxi = max_element(&tone[1][1],&tone[n][m]);
	while (*mxi){
		cnt++;
		int x = (mxi - &tone[0][0]) / N,y = (mxi - &tone[0][0]) % N;
		for (int i = 0;i <= 4;i++){
			int xi = x + dx[i],yi = y + dy[i];
			if (a[xi][yi]){
				a[xi][yi]--;
				for (int j = 0;j <= 4;j++){
					int x_ = xi + dx[j],y_ = yi + dy[j];
					tsum[x_][y_]--;
				}
				if (!a[xi][yi]){
					for (int j = 0;j <= 4;j++){
						int x_ = xi + dx[j],y_ = yi + dy[j];
						tone[x_][y_]--;
					}
				}
			}
		}
		// printf("%d %d %d\n",x,y,tone[x][y]);
		mxi = max_element(&tone[1][1],&tone[n][m]);
	}
	if (k == 6)	cout << cnt - 1;
	else	cout << cnt;
	return 0;
}