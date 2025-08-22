#include <bits/stdc++.h>
using namespace std;
int cnta,cntb;
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		int x;
		cin >> x;
		if (x == 1){
			cout << cnta + cntb << ' ' << cntb;
			return 0;
		}
		if (x)	cnta++;
		else	cntb++;
	}
	return 0;
}