#include <bits/stdc++.h>
using namespace std;
struct blk{
	int x,y,pt,stp;
};
const int N = 5e2 + 5,INF = 0x7fffffff;
int n,m;
char a[N][N];
int pt,sx,sy,mn;
int dx[5][5] = {{-2,1,0,0},
				{-1,1,0,0},
				{-1,2,0,0}},
	dy[5][5] = {{0,0,-2,1},
				{0,0,-1,2},
				{0,0,-1,1}},
	dpt[5][5] = {{2,2,1,1},
				 {1,1,0,0},
				 {0,0,1,1}};
int f[N][N][5];
void bfs(int sx,int sy,int spt){
	queue<blk> q;
	q.push({sx,sy,spt,0});
	while (!q.empty()){
		int x = q.front().x,y = q.front().y,pt = q.front().pt,stp = q.front().stp;
		q.pop();
		if (f[x][y][pt] < stp)	continue;
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	while (n || m){
		for (int i = 1;i <= n;i++){
			for (int j = 1;j <= m;j++){
				cin >> a[i][j];
				if (a[i][j] == 'X'){
					if (a[i][j - 1] == 'X')	sx = i,sy = j - 1,pt = 1;
					else if (a[i - 1][j] == 'X')	sx = i - 1,sy = j,pt = 2;
					else	sx = i,sy = j;
				}
			}
		}
		bfs(sx,sy,pt);
		cin >> n >> m;
	}
	return 0;
}

