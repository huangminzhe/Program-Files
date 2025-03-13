#include <bits/stdc++.h>
using namespace std;
const int N = 8e2 + 5;
struct node{
	int x,y;
};
int n,m;
char a[N][N];
int bx,by,gx,gy;
int gst[N][N],tim[N][N][2];
int dx[] = {-1,1,0,0},dy[] = {0,0,-1,1};	// 女生方向数组
int dbx[] = {-1,1,0,0,-2,2,0,0,-1,1,1,-1,-3,3,0,0,-2,2,1,-1,-1,1,2,-2},dby[] = {0,0,-1,1,0,0,-2,2,-1,1,-1,1,0,0,-3,3,-1,1,-2,2,-2,2,-1,1};	// 男生方向数组
int dgx[] = {-1,1,0,0,-2,2,0,0,-1,1,1,-1},dgy[] = {0,0,-1,1,0,0,-2,2,-1,1,-1,1};	// 怪物方向数组
void bfsg(node g){
	queue<node> q;
	q.push(g);
	gst[g.x][g.y] = 0;
	while (!q.empty()){
		int x = q.front().x,y = q.front().y;
		q.pop();
		for (int i = 0;i < 12;i++){
			int xi = x + dgx[i],yi = y + dgy[i];
			if (xi < 1 || xi > n || yi < 1 || yi > m || gst[x][y] + 1 >= gst[xi][yi])	continue;
			gst[xi][yi] = gst[x][y] + 1;
			q.push({xi,yi});
		}
	}
}
int bfs(node b,node g){
	queue<node> q;
	q.push(g);	// 先搜女生
	tim[g.x][g.y][0] = 0;
	while (!q.empty()){
		int x = q.front().x,y = q.front().y;
		q.pop();
		for (int i = 0;i < 4;i++){
			int xi = x + dx[i],yi = y + dy[i];
			if (xi < 1 || xi > n || yi < 1 || yi > m || a[xi][yi] == '#' || tim[x][y][0] + 1 <= gst[xi][yi])	continue;
			tim[xi][yi][0] = tim[x][y][0] + 1;
			q.push({xi,yi});
		}
	}
	q.push(b);	// 再搜男生
	tim[b.x][b.y][1] = 0;
	while (!q.empty()){
		int x = q.front().x,y = q.front().y;
		q.pop();
		if (tim[x][y][1] == tim[x][y][0])	return tim[x][y][0];
		for (int i = 0;i < 24;i++){
			int xi = x + dbx[i],yi = y + dby[i];
			if (xi < 1 || xi > n || yi < 1 || yi > m || a[xi][yi] == '#' || tim[x][y][1] + 1 <= gst[xi][yi])	continue;
			tim[xi][yi][1] = tim[x][y][1] + 1;
			q.push({xi,yi});
		}
	}
	return -1;
}
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		memset(a,0,sizeof a);
		memset(gst,0x7f,sizeof gst);
		cin >> n >> m;
		for (int i = 1;i <= n;i++){
			string s;
			cin >> s;
			for (int j = 1;j <= m;j++){
				int si = j - 1;
				a[i][j] = s[si];
				if (a[i][j] == 'M'){
					bx = i;
					by = j;
				}
				if (a[i][j] == 'G'){
					gx = i;
					gy = j;
				}
				if (a[i][j] == 'Z'){
					bfsg({i,j});
				}
			}
		}
		cout << bfs({bx,by},{gx,gy}) << '\n';
	}
	return 0;
}