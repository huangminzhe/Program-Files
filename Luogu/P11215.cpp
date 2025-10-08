#include <bits/stdc++.h>
using namespace std;
const int N = 3e3 + 5,M = 1e5 + 5;
struct block{
	bool lake,tree;
}a[N][N];
struct tr{
	int x,y,t;
	bool evt;	// 0 生成，1 死亡
};
bool operator< (tr b,tr c){
	return b.t < c.t;
}
int n,m,q,r,k;
// q：湖个数
// r：手动种树次数
// k：树在多少秒后死亡 
priority_queue<tr> evts;
int dx[] = {-1,1,0,0},dy[] = {0,0,-1,1};
inline bool check_edge(int x,int y){
	return x > 0 && x <= n && y > 0 && y <= m;
}
inline bool check_land(int x,int y){
	return !a[x][y].lake && !a[x][y].tree;
}
int main(int argc, char **argv){
#ifdef LOCAL
	// freopen("lake5.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin >> n >> m >> q >> r >> k;
	for (int I = 1;I <= q;I++){
		int x1,y1,x2,y2;
		cin >> x1 >> y1 >> x2 >> y2;
		for (int i = x1;i <= x2;i++){
			for (int j = y1;j <= y2;j++){
				a[i][j].lake = 1;
			}
		}
	}
	for (int i = 1;i <= r;i++){
		int x,y,t;
		cin >> t >> x >> y;
		evts.push({x,y,t,0});
	}

	while (!evts.empty()){
		int x = evts.top().x,y = evts.top().y,t = evts.top().t,evt = evts.top().evt;
		evts.pop();

		if (evt){
			bool f = 1;
			for (int i = 0;i < 4;i++){
				int xi = x + dx[i],yi = y + dy[i];
				if (!check_land(xi,yi)){
					f = 0;
					break;
				}
			}
			if (f)	a[x][y].tree = 0;
		}else{
			a[x][y].tree = 1;
			evts.push({x,y,t + k,1});

			for (int i = 0;i < 4;i++){
				int xi = x + dx[i],yi = y + dy[i];
				bool f = 0;
				for (int j = 0;j < 4;j++){
					int xj = xi + dx[j],yj = yi + dy[j];
					if (a[xj][yj].lake){
						f = 1;
						break;
					}
				}
				if (f && check_land(xi,yi))
					evts.push({xi,yi,t + 1,0});
			}
		}
	}
	int ans = 0;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= m;j++){
			if (a[i][j].tree)	ans++;
		}
	}
	cout << ans;
	return 0;
}
