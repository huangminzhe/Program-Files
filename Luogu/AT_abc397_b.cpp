#include <bits/stdc++.h>
using namespace std;
int cnt;
int main(int argc, char **argv){
	string s;
	cin >> s;
	for (int i = 0;i < s.size();i++){
		if (s[i] == 'i' && s[i + 1] != 'o')	cnt++;
		else if (s[i] == 'o')	cnt++;
		else	i++;
	}
	cout << cnt;
	return 0;
}