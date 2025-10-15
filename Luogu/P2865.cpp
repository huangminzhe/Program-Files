#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 5,INF = 0x7fffffff;
struct point{
	int v,w;
};
bool operator< (point b,point c){
	return b.w > c.w;
}
int n,m,d[2][N];
vector<point> a[N];
void djkstr(){
	fill(d[0] + 1,d[0] + n + 1,INF / 2);
	fill(d[1] + 1,d[1] + n + 1,INF / 2);
	priority_queue<point> q;
	d[0][1] = 0;
	q.push({1,0});
	while (!q.empty()){
		int u = q.top().v,uw = q.top().w;
		q.pop();
		if (uw > d[1][u])	continue;
		for (auto [v,w] : a[u]){
		// for (auto i : a[u]){
		// 	int v = i.v,w = i.w;
			if (uw + w < d[0][v]){
				d[1][v] = d[0][v];
				d[0][v] = uw + w;
				q.push({v,d[0][v]});
			}else if (uw + w > d[0][v] && uw + w < d[1][v]){
				d[1][v] = uw + w;
				q.push({v,d[1][v]});
			}
		}
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		int u,v,w;
		cin >> u >> v >> w;
		a[u].push_back({v,w});
		a[v].push_back({u,w});
	}
	djkstr();
	cout << d[1][n];
	return 0;
}