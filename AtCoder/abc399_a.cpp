#include <bits/stdc++.h>
using namespace std;
string s,t;
int cnt;
int main(int argc, char **argv){
	int n;
	cin >> n >> s >> t;
	for (int i = 0;i < n;i++){
		if (s[i] != t[i])	cnt++;
	}
	cout << cnt;
	return 0;
}