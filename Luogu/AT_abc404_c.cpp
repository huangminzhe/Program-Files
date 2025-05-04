#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
bool f[N];
vector<int> g[N];
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	if (n != m){
		cout << "No";
		return 0;
	}
	for (int i = 1;i <= m;i++){
		int x,y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for (int i = 1,tot = 1;tot < n;tot++){
		if (g[i].size() != 2 || f[i] || f[g[i][0]] && f[g[i][1]]){
			// printf("%d %d %d %d %d\n",i,g[i].size(),f[i],f[g[i][0]],f[g[i][1]]);
			cout << "No";
			return 0;
		}
		f[i] = 1;
		if (f[g[i][0]]){
			i = g[i][1];
		}else{
			i = g[i][0];
		}
	}
	cout << "Yes";
	return 0;
}