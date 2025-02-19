#include <bits/stdc++.h>
using namespace std;
const int N = 10;
int n;
bool a[N];
void dfs(int u){
	if (u > n){
		for (int i = 1;i <= n;i++){
			if (a[i])	cout << 'Y';
			else	cout << 'N';
		}
		cout << '\n';
		return ;
	}
	dfs(u + 1);
	a[u] = 1;
	dfs(u + 1);
	a[u] = 0;
}
int main(int argc, char **argv){
	cin >> n;
	dfs(1);
	return 0;
}