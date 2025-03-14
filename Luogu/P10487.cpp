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
int dx[] = {-1,1,0,0},dy[] = {0,0,-1,1};	// 方向数组
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
		if (tim[x][y][0] + 1 >= gst[x][y])	continue;	// 被鬼追上了
		q.pop();
		for (int i = 0;i < 4;i++){
			int xi = x + dx[i],yi = y + dy[i];
			if (xi < 1 || xi > n || yi < 1 || yi > m || 
				a[xi][yi] == '#' || 
				tim[x][y][0] + 1 >= gst[xi][yi] || 	// 鬼先到了
				tim[x][y][0] + 1 >= tim[xi][yi][0])	continue;
			tim[xi][yi][0] = tim[x][y][0] + 1;
			q.push({xi,yi});
		}
	}
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= m;j++){
			printf("%d ",tim[i][j][0]);
		}
		printf("\n");
	}
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= m;j++){
			printf("%d ",gst[i][j]);
		}
		printf("\n");
	}
	q.push(b);	// 再搜男生
	tim[b.x][b.y][1] = 0;
	while (!q.empty()){
		for (int tt = 3;tt;tt--){
			for (int len = q.size();len;len--){
				int x = q.front().x,y = q.front().y;
				q.pop();
				if (tim[x][y][1] + 1 >= gst[x][y])	continue;	// 同上
				if (tim[x][y][1] == tim[x][y][0])	return tim[x][y][0];
				for (int i = 0;i < 4;i++){
					int xi = x + dx[i],yi = y + dy[i];
					if (xi < 1 || xi > n || yi < 1 || yi > m || 
						a[xi][yi] == '#' || 
						tim[x][y][1] + 1 >= gst[xi][yi] || 
						tim[x][y][1] + 1 >= tim[xi][yi][1])	continue;
					tim[xi][yi][1] = tim[x][y][1] + 1;
					q.push({xi,yi});
				}
			}
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
		memset(tim,0x7f,sizeof tim);
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