#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105,M = 2.5e3 + 5;
struct edge{
	int v,w,next;
}edges[M * 2];
int head[N],tot;
void add(int u,int v,int w){
	edges[++tot] = {v,w,head[u]};
	head[u] = tot;
}

ll zt[N],yz[N];
int n,m,in[N],out[N],f[N];
bool check(){
	for (int i = 1;i <= n;i++){
		if (!in[i])	return 1;
	}
	return 0;
}
void bfs(){
	queue<int> q;
	for (int i = 1;i <= n;i++){
		if (!in[i])	q.push(i),f[i] = 1;
	}
	while (!q.empty()){
		int u = q.front();
		q.pop();
		zt[u] -= yz[u];
		if (zt[u] <= 0)	continue;
		for (int i = head[u];i;i = edges[i].next){
			int v = edges[i].v,w = edges[i].w;
			zt[v] += zt[u] * w;
			if (!f[v])	f[v] = 1,q.push(v);
		}
	}
}
int main(int argc, char **argv){
// 	freopen("network.in","r",stdin);
// #ifndef LOCAL
// 	freopen("network.ans","w",stdout);
// #endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		cin >> zt[i] >> yz[i];
		if (zt[i])	zt[i] += yz[i];
	}
	for (int i = 1;i <= m;i++){
		int u,v,w;
		cin >> u >> v >> w;
		add(u,v,w);
		out[u]++;
		in[v]++;
	}
	bfs();
	// for (int i = 1;i <= n;i++){
	// 	printf("%d ",zt[i]);
	// }
	// printf("\n");
	bool f = 1;
	for (int i = 1;i <= n;i++){
		if (!out[i] && zt[i] > 0)	cout << i << ' ' << zt[i] << '\n',f = 0;
	}
	if (f)	cout << "NULL";
	return 0;
}

