#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int n;string s;
	cin >> n >> s;
	for (int i = 1;i <= n - s.size();i++){
		cout << 'o';
	}
	cout << s;
	return 0;
}