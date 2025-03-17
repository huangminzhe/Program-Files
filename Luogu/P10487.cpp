#include <bits/stdc++.h>
using namespace std;
const int N = 8e2 + 5;
struct node{
	int x,y;
};
int n,m;
char a[N][N];
int bx,by,gx,gy;
int gst[N][N];	// 鬼到的时间
bool f[N][N][2];	// 是否走过
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
	queue<node> qb,qg;
	qb.push(b);
	qg.push(g);
	f[g.x][g.y][0] = 1;
	f[b.x][b.y][1] = 1;
	int t = 0;
	while (!qb.empty() && !qg.empty()){
		t++;
		for (int len = qg.size();len;len--){
			int x = qg.front().x,y = qg.front().y;
			qg.pop();
			if (gst[x][y] <= t)	continue;	// 被鬼追上了
			// printf("g:t=%d x=%d y=%d\n",t,x,y);
			for (int i = 0;i < 4;i++){
				int xi = x + dx[i],yi = y + dy[i];
				if (xi < 1 || xi > n || yi < 1 || yi > m || 
					a[xi][yi] == 'X' || 
					t >= gst[xi][yi] || 	// 鬼先到了
					f[xi][yi][0])	continue;
				f[xi][yi][0] = 1;
				if (f[xi][yi][1])	return t;
				qg.push({xi,yi});
			}
		}
		for (int tt = 3;tt;tt--){
			for (int len = qb.size();len;len--){
				int x = qb.front().x,y = qb.front().y;
				qb.pop();
				if (gst[x][y] <= t)	continue;	// 被鬼追上了
				// printf("b:t=%d x=%d y=%d\n",t,x,y);
				for (int i = 0;i < 4;i++){
					int xi = x + dx[i],yi = y + dy[i];
					if (xi < 1 || xi > n || yi < 1 || yi > m || 
						a[xi][yi] == 'X' || 
						t >= gst[xi][yi] || 	// 鬼先到了
						f[xi][yi][1])	continue;
					f[xi][yi][1] = 1;
					if (f[xi][yi][0])	return t;
					qb.push({xi,yi});
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
		memset(f,0,sizeof f);
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