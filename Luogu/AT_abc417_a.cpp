#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int n,a,b;string s;
	cin >> n >> a >> b >> s;
	for (int i = a;i < n - b;i++)	cout << s[i];
	return 0;
}