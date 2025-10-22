#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5,M = 5e5 + 5;
struct point{
	int v,w;
};
int n,m,k,p[N];
vector<point> g[N],fg[N];
void djkstr(vector<point> g,int *fa){}
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		cin >> n >> m >> k;
		for (int i = 1;i <= m;i++){
			int u,v,w;
			cin >> u >> v >> w;
			g[u].push_back({v,w});
			fg[v].push_back({u,w});
		}
		for (int i = 1;i <= k;i++){
			cin >> p[i];
		}
	}
	return 0;
}