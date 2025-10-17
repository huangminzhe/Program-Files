#include <bits/stdc++.h>
using namespace std;
const int N = 155;
struct point{
	int v;
	double w;
}a[N];
bool operator< (point b,point c){
	return b.w > c.w;
}
vector<point> g[N];
int n;
inline double calc(int u,int v){
	return sqrt((a[u].w - a[v].w) * (a[u].w - a[v].w) + (a[u].v - a[v].v) * (a[u].v - a[v].v));
}
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i].v >> a[i].w;
	}
	for (int i = 1;i <= n;i++){
		string s;
		cin >> s;
		for (int j = 1;j <= n;j++){
			int sj = j - 1;
			if (s[sj] - '0'){
				g[i].push_back({j,calc(i,j)});
			}
		}
	}
	
	return 0;
}