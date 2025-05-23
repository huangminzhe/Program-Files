#include <bits/stdc++.h>
using namespace std;
const int N = 6e3 + 5;
int a[N],fa[N];
vector<int> g[N];
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	for (int i = 1;i <= n;i++){
		int e,f;
		cin >> e >> f;
		fa[e] = f;
		g[f].push_back(e);
	}
	return 0;
}