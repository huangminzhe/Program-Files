#include <bits/stdc++.h>
using namespace std;
const int N = 505,INF = 0x7fffffff;
struct point{
	int v,w;
};
bool operator< (point b,point c){
	return b.w < c.w;
}
int a[N][N],d[N];
int n,m,c,t;
void djkstr(){
	fill(d + 1,d + n + 1,INF / 2);
	priority_queue<point> q;
	d[1] = 0;
	q.push({1,0});
}
int main(int argc, char **argv){
	cin >> n >> m >> c >> t;
	for (int i = 1;i <= m;i++){
		int u,v,w;
		cin >> u >> v >> w;
		a[u][v] = a[v][u] = min(w,a[u][v]);
	}
	djkstr();
	return 0;
}