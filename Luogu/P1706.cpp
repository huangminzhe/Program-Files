#include <bits/stdc++.h>
using namespace std;
const int N = 10;
int n,a[N];
bool f[N];
void dfs(int u){
	if (u > n){
		for (int i = 1;i <= n;i++){
			printf("%5d",a[i]);
		}
		cout << '\n';
		return ;
	}
	for (int i = 1;i <= n;i++){
		if (f[i])	continue;
		f[i] = 1;
		a[u] = i;
		dfs(u + 1);
		f[i] = 0;
	}
}
int main(int argc, char **argv){
	cin >> n;
	dfs(1);
	return 0;
}