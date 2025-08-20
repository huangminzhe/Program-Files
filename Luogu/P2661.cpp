#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int fa[N],in[N],mn = N,f[N];
void rm(int x){
	f[x] = 1;
	in[fa[x]]--;
	if (!in[fa[x]]){
		rm(fa[x]);
		fa[x] = x;
	}
}
void dfs(int x,int st,int stp){
	f[x] = 1;
	if (fa[x] == st){
		mn = min(mn,stp);
		return ;
	}
	dfs(fa[x],st,stp + 1);
}
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> fa[i];
		in[fa[i]]++;
	}
	for (int i = 1;i <= n;i++){
		if (!in[i] && !f[i]){
			rm(i);
		}
	}
	for (int i = 1;i <= n;i++){
		if (in[i] && !f[i]){
			dfs(i,i,1);
		}
	}
	cout << mn;
	return 0;
}