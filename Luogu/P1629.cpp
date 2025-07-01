#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N = 1e3 + 5;
int n,m,dis[N][N],sum;
int main(int argc, char **argv){
	cin >> n >> m;
	memset(dis,0x3f,sizeof dis);
	for (int i = 1;i <= n;i++)
		dis[i][i] = 0;
	for (int i = 1;i <= m;i++){
		int u,v,w;
		cin >> u >> v >> w;
		dis[u][v] = min(dis[u][v],w);
	}
	for (int k = 1;k <= n;k++)
		for (int i = 1;i <= n;i++)
			for (int j = 1;j <= n;j++)
				dis[i][j] = min(dis[i][j],dis[i][k] + dis[k][j]);
	for (int i = 2;i <= n;i++){
		sum += dis[1][i] + dis[i][1];
	}
	cout << sum;
	return 0;
}