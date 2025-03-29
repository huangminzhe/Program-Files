#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int fa[N],cnt;
int find(int x){
	if (fa[x] == x)	return x;
	return fa[x] = find(fa[x]);
}
void merge(int x,int y){
	fa[find(y)] = find(x);
}
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	for (int i = 1;i <= n;i++)	fa[i] = i;
	for (int i = 1;i <= m;i++){
		int u,v;
		cin >> u >> v;
		if (find(u) == find(v)){
			cnt++;
			continue;
		}
		merge(u,v);
	}
	cout << cnt;
	return 0;
}