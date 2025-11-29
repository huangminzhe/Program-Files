#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	for (int i = 1;i <= min(n,m);i++){
		cout << "OK\n";
	}
	for (int i = m;i < n;i++){
		cout << "Too Many Requests\n";
	}
	return 0;
}