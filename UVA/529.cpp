#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n,dep,a[N];
bool f[N];
bool dfs(int x){
	if (a[x] << (dep - x) < n)	return 0;
	if (x == dep)	return a[x] == n;
	memset(f,0,sizeof f);
	for (int i = x;i;i--){
		for (int j = i;j;j--){
			int nw = a[i] + a[j];
			if (nw > n || nw <= a[x] || f[nw])	continue;
			a[x + 1] = nw;
			if (dfs(x + 1))	return 1;
			f[nw] = 1;
		}
	}
	return 0;
}
int main(int argc, char **argv){
	a[1] = 1;
	cin >> n;
	while (n){
		dep = 1;
		while(!dfs(1))	dep++;
		for (int i = 1;i < dep;i++){
			cout << a[i] << ' ';
		}
		cout << n << '\n';
		cin >> n;
	}
	return 0;
}