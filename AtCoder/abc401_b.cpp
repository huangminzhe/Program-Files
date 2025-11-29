#include <bits/stdc++.h>
using namespace std;
bool f;
int cnt;
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		string s;
		cin >> s;
		if (s == "login")	f = 1;
		else if (s == "logout")	f = 0;
		else if (s == "private"){
			if (!f)	cnt++;
		}
	}
	cout << cnt;
	return 0;
}