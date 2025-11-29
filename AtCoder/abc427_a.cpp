#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	string s;
	cin >> s;
	for (int i = 0;i < s.size();i++){
		if (i == s.size() / 2)	continue;
		cout << s[i];
	}
	return 0;
}