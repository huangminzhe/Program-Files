#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 5;
vector<int> a[N];
int n,root;	// 结点个数；重心
int sz[N],stsz[N] = {0x7fffffff};	// 树的大小；以 i 为根结点时最大子树的大小
int dis[N],sum;	// 每个点到重心的距离；距离和
// 找重心
void dfs(int u,int f){
	sz[u] = 1;
	for (int v : a[u]){
		if (v != f){
			dfs(v,u);
			sz[u] += sz[v];
			stsz[u] = max(stsz[u],sz[v]);
		}
	}
	stsz[u] = max(stsz[u],n - sz[u]);	// 父节点的子树
	if (stsz[u] < stsz[root] || stsz[u] == stsz[root] && u < root)	root = u;
}
// 计算每个点到重心的距离
void bfs(int root){
	queue<pair<int,int>> q;
	q.push({root,0});
	while (!q.empty()){
		int u = q.front().first,f = q.front().second;
		q.pop();
		for (int v : a[u]){
			if (v != f){
				dis[v] = dis[u] + 1;
				sum += dis[v];
				q.push({v,u});
			}
		}
	}
}
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i < n;i++){
		int u,v;
		cin >> u >> v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	dfs(1,0);	// 找重心
	bfs(root);	// 计算每个点到重心的距离
	cout << root << ' ' << sum;
	return 0;
}