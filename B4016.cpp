#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
vector<pair<int,int>> a[N];
int mx,mxi;
void dfs(int u,int f,int sum){
	for (int i = 0;i < a[u].size();i++){
		if (a[u][i].first != f){
			if (mx < sum + a[u][i].second){
				mx = sum + a[u][i].second;
				mxi = a[u][i].first;
			}
			dfs(a[u][i].first,u,sum + a[u][i].second);
		}
	}
}
void bfs(int u){
	//          u        f  sum
	queue<pair<int,pair<int,int>>> q;
	q.push({u,{0,0}});
	while (!q.empty()){
		int v = q.front().first,f = q.front().second.first,sum = q.front().second.second;
		// v 其实是 u，是当前结点。
		q.pop();
		for (int i = 0;i < a[v].size();i++){
			if (a[v][i].first != f){
				if (mx < sum + a[v][i].second){
					mx = sum + a[v][i].second;
					mxi = a[v][i].first;
				}
				q.push({a[v][i].first,{v,sum + a[v][i].second}});
			}
		}
	}
}
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i < n;i++){
		int u,v,w;
		cin >> u >> v >> w;
		a[u].push_back({v,w});
		a[v].push_back({u,w});
	}
	dfs(1,0,0);
	mx = 0;
	dfs(mxi,0,0);
	// bfs(1);
	// mx = 0;
	// bfs(mxi);
	cout << mx;
	return 0;
}