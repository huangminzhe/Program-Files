#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 55,M = 5e3 + 5;
int n,m,k,b[M];
set<int> s[N];
int main(int argc, char **argv){
	cin >> n >> m >> k;
	for (int i = 1;i <= m;i++)	s[0].insert(i);
	while (k--){
		int op,u,v;
		cin >> op >> u >> v;
		if (op == 1){
			s[b[u]].erase(u);
			s[v].insert(u);
			b[u] = v;
		}else{
			if (s[v].size() < u){
				cout << "-1\n";
				continue;
			}
			int i = 1;
			auto it = s[v].begin();
			for (;i < u;it++,i++);
			cout << *it << '\n';
		}
	}
	return 0;
}