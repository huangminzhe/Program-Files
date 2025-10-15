#include <bits/stdc++.h>
using namespace std;
const int N = 505,INF = 0x7fffffff;
struct point{
	int v,w;
};
bool operator< (point b,point c){
	return b.w > c.w;
}
int a[N][N],d[N];
bool f[N];
int n,m,c,t;
vector<int> cows;
void djkstr(){
	fill(d + 1,d + n + 1,INF / 2);
	priority_queue<point> q;
	d[1] = 0;
	q.push({1,0});
	while (!q.empty()){
		int u = q.top().v;
		q.pop();
		if (f[u])	continue;
		f[u] = 1;
		for (int v = 1;v <= n;v++){
			if (a[u][v] == INF)	continue;
			int w = a[u][v];
			if (d[u] + w < d[v]){
				d[v] = d[u] + w;
				q.push({v,d[v]});
			}
		}
	}
}
int main(int argc, char **argv){
	cin >> n >> m >> c >> t;
	for (int i = 1;i <= n;i++)	fill(a[i] + 1,a[i] + n + 1,INF);
	for (int i = 1;i <= m;i++){
		int u,v,w;
		cin >> u >> v >> w;
		a[u][v] = a[v][u] = min(w,a[u][v]);
	}
	djkstr();
	for (int i = 1;i <= c;i++){
		int x;
		cin >> x;
		if (d[x] <= t)	cows.push_back(i);
	}
	cout << cows.size() << '\n';
	for (int i : cows){
		cout << i << '\n';
	}
	return 0;
}