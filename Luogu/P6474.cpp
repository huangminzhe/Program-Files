#include <bits/stdc++.h>
using namespace std;
const int N = 355,INF = 0x7fffffff;
struct point{
	int x,y;
	int c1,c2,stp;
};
bool operator< (point b,point c){
	if (b.stp == c.stp){
		if (b.c1 + b.c2 == c.c1 + c.c2)	return b.c1 < b.c2;
		return b.c1 + b.c2 < c.c1 + c.c2;
	}
	return b.stp < c.stp;
}
bool a[N][N],f[N][N];
int sdr[N][N],sx,sy,ex,ey,n,m,yin,uyyi,d,ans = INF,ans1 = INF,ans2 = INF;
// uyyi：瞬移次数 
int dx[] = {-1,1,0,0,-1,1,-1,1},dy[] = {0,0,-1,1,-1,-1,1,1};
inline bool check_edge(int x,int y){
	return x > 0 && x <= n && y > 0 && y <= m;
}
void kosj(int x,int y){	// 扩散 
	if (!sdr[x][y])	return ;
	for (int i = 0;i < 4;i++){
		int xi = x + dx[i],yi = y + dy[i];
		if (check_edge(xi,yi) && sdr[x][y] > sdr[xi][yi]){
			sdr[xi][yi] = sdr[x][y] - 1;
			kosj(xi,yi);
		}
	}
}
void bfs(){
	queue<point> q;
	q.push({sx,sy,0,0,0});
	while (!q.empty()){
		int x = q.front().x,y = q.front().y,
			stp = q.front().stp,c1 = q.front().c1,c2 = q.front().c2;
		q.pop();
		f[x][y] = 1;
		// printf("%d %d %d %d %d----\n",x,y,c1,c2,stp);
		if (stp > ans)	continue;
		else if (stp == ans)
			if (c1 + c2 > ans1 + ans2)	continue;
			else if (c1 + c2 == ans1 + ans2)
				if (c1 >= ans2)	continue;
		if (x == ex && y == ey){
			if (stp < ans)
				ans = stp,
				ans1 = c1,
				ans2 = c2;
			else if (stp == ans)
				if (c1 + c2 < ans1 + ans2 || c1 < ans1)
					ans1 = c1,
					ans2 = c2;
			continue;
		}
		for (int i = 0;i < 8;i++){
			int xi = x + dx[i],yi = y + dy[i];
			// printf("%d %d %d %d\n",xi,yi,!check_edge(xi,yi),f[xi][yi]);
			if (!check_edge(xi,yi) || 
				f[xi][yi] || 
				a[xi][yi])	continue;
			if (!sdr[xi][yi])
				q.push({xi,yi,c1,c2,stp + 1});
			else if (c1 < yin)
				q.push({xi,yi,c1 + 1,c2,stp + 1});
		}
		if (c2 < uyyi){
			for (int i = 0;i < 4;i++){
				int xi = x + d * dx[i],yi = y + d * dy[i];
				if (!check_edge(xi,yi) || 
					f[xi][yi] || 
					a[xi][yi])	continue;
				if (!sdr[xi][yi])
					q.push({xi,yi,c1,c2 + 1,stp + 1});
				else if (c1 < yin)
					q.push({xi,yi,c1 + 1,c2 + 1,stp + 1});
			}
		}
	}
}
int main(int argc, char **argv){
	cin >> n >> m >> yin >> uyyi >> d;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= m;j++){
			char c;
			cin >> c;
			if (c == 'S')	sx = i,sy = j;
			else if (c == 'T')	ex = i,ey = j;
			int num = 0;
			while (isdigit(c)){
				a[i][j] = 1;
				num *= 10;
				num += c - '0';
				c = getchar();
			}
			if (num > sdr[i][j])	sdr[i][j] = num,kosj(i,j);
		}
	}
	// for (int i = 1;i <= n;i++){
	// 	for (int j = 1;j <= m;j++){
	// 		printf("%d:%d ",a[i][j],sdr[i][j]);
	// 	}
	// 	printf("\n");
	// }
	bfs();
	if (ans == INF)	cout << -1;
	else	cout << ans << ' ' << ans1 << ' ' << ans2;
	return 0;
}