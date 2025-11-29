#include <bits/stdc++.h>
using namespace std;
map<int,int> t,a;
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		int x;
		cin >> x;
		t[x]++;
		a[x] = i;
	}
	for (auto i = t.rbegin();i != t.rend();i++){
		if (i->second == 1){
			cout << a[i->first];
			return 0;
		}
	}
	cout << -1;
}