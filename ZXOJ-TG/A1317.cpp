#include <bits/stdc++.h>
using namespace std;
const int N = 25;
int n,r,a[N];
void dfs(int x,int u){
	if (u > r){
		for (int i = 1;i <= r;i++){
			printf("%d ",a[i]);
		}
		cout << '\n';
		return ;
	}
	for (int i = x + 1;i <= n;i++){
		a[u] = i;
		dfs(i,u + 1);
	}
}
int main(int argc, char **argv){
	cin >> n >> r;
	dfs(0,1);
	return 0;
}