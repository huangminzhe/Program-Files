#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
vector<int> a[N];	// 图
int dia[N],dia1,dia2;	// 直径路径和它的两个端点
int dis[N];	// 与指定点的距离
int centre;	// 树的中心
void dfs(int u,int f){
	for (int i = 0;i < a[u].size();i++){
		int v = a[u][i];
		if (v != f){
			dis[v] = dis[u] + 1;
			if (dis[v] > dis[dia1])	dia1 = v;
			dia[v] = u;
			dfs(v,u);
		}
	}
}
// 每个点到中心的距离，和每个点到它子辈中离它最远的叶结点的距离
void calc(int u,int f){
	for (int i = 0;i < a[u].size();i++){
		int v = a[u][i];
		if (v != f){
			calc(v,u);
			dis[u] = max(dis[u],dis[v] + 1);
		}
	}
}
int main(int argc, char **argv){
	int n,k;
	cin >> n >> k;
	for (int i = 1;i < n;i++){
		int u,v;
		cin >> u >> v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	// 找直径
	// 当前指定点为 dia1
	dfs(1,0);
	dia2 = dia1,dis[dia1] = 0,dia[dia1] = 0;
	dfs(dia1,0);

	// 找中心
	centre = dia1;
	int len = (dis[dia1] + 1) / 2;
	while (len--)	centre = dia[centre];

	// 每个点到中心的距离
	// 当前指定点为：以 i 为根时，它到离它最远的叶结点的距离
	memset(dis,0,sizeof dis);
	calc(centre,0);
	// printf("%d\n",centre);
	// for (int i = 1;i <= n;i++){
	// 	printf("%d ",dis[i]);
	// }

	// 这里越大的 dis[i] 越靠近中心城市，排掉 k 个中心城市就是最大的到中心城市的距离。
	// +1 就是到中心城市的距离
	sort(dis + 1,dis + n + 1);
	cout << dis[n - k] + 1;
	return 0;
}