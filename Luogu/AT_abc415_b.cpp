#include <bits/stdc++.h>
using namespace std;
bool f;
int main(int argc, char **argv){
	string s;
	cin >> s;
	for (int i = 1;i <= s.size();i++){
		int si = i - 1;
		if (s[si] == '#'){
			cout << i;
			if (f)	cout << '\n',f = 0;
			else	cout << ',',f = 1;
		}
	}
	return 0;
}