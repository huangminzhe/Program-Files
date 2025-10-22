#include <bits/stdc++.h>
using namespace std;
const int N = 155;
const double INF = DBL_MAX;

struct point{
	double x,y;
}a[N];

int fa[N];
int find(int x){
	if (fa[x] == x)	return x;
	return fa[x] = find(fa[x]);
}
void merge(int x,int y){
	fa[find(y)] = find(x);
}

int n;
double d[N][N],dia[N],mx[N],ans = INF;
inline double calc(int u,int v){
	return sqrt((a[u].y - a[v].y) * (a[u].y - a[v].y) + (a[u].x - a[v].x) * (a[u].x - a[v].x));
}
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i].x >> a[i].y;
	}
	for (int i = 1;i <= n;i++)	fa[i] = i,fill(d[i] + 1,d[i] + n + 1,INF / 2);
	for (int i = 1;i <= n;i++){
		string s;
		cin >> s;
		for (int j = 1;j <= n;j++){
			int sj = j - 1;
			if (s[sj] - '0' || i == j){
				d[i][j] = calc(i,j);
				merge(i,j);
			}
		}
	}
	for (int k = 1;k <= n;k++)
		for (int i = 1;i <= n;i++)
			for (int j = 1;j <= n;j++)
				d[i][j] = min(d[i][j],d[i][k] + d[k][j]);
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			if (d[i][j] != INF / 2)
				mx[i] = max(mx[i],d[i][j]);
		}
		dia[find(i)] = max(dia[find(i)],mx[i]);
	}
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			if (find(i) != find(j)){
				ans = min(ans,
						  max({dia[find(i)],dia[find(j)],mx[i] + calc(i,j) + mx[j]}));
			}
		}
	}
	printf("%.6f",ans);
	return 0;
}