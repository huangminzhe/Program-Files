#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 5;
struct node{
	int x,y;
};
int n,m;
char a[N][N];
int dx[] = {-1,1,1,-1},dy[] = {-1,1,-1,1},gx[] = {0,1,1,0},gy[] = {0,1,0,1};
char gc[] = {'\\','\\','/','/'};
int stp[N][N];
void bfs(int sx,int sy){
	memset(stp,0x3f,sizeof stp);
	stp[sx][sy] = 0;
	deque<node>	q;
	q.push_back({sx,sy});
	while (!q.empty()){
		int x = q.front().x,y = q.front().y;
		q.pop_front();
		for (int i = 0;i < 4;i++){
			int xi = x + dx[i],yi = y + dy[i];
			if (xi < 0 || xi > n || yi < 0 || yi > m)
				continue;
			int xg = x + gx[i],yg = y + gy[i];
			if (a[xg][yg] != gc[i]){
				if (stp[x][y] + 1 < stp[xi][yi]){
					stp[xi][yi] = stp[x][y] + 1;
					q.push_back({xi,yi});
				}
			}else
				if (stp[x][y] < stp[xi][yi]){
					stp[xi][yi] = stp[x][y];
					q.push_front({xi,yi});
				}
		}
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	if (n + m & 1){
		cout << "NO SOLUTION";
		return 0;
	}
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= m;j++){
			cin >> a[i][j];
		}
	}
	bfs(0,0);
	cout << stp[n][m];
	return 0;
}