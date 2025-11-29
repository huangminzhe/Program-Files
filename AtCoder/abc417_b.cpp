#include <bits/stdc++.h>
using namespace std;
map<int,int> a;
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		int x;
		cin >> x;
		a[x]++;
	}
	for (int i = 1;i <= m;i++){
		int x;
		cin >> x;
		a[x]--;
		if (a[x] <= 0)	a.erase(x);
	}
	for (auto i : a)
		for (int j = 1;j <= i.second;j++)
			cout << i.first << ' ';
	return 0;
}