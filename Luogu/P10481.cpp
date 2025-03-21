#include <bits/stdc++.h>
using namespace std;
int8_t r[10],c[10],g[5][5];
int main(int argc, char **argv){
	int t;
	while (t--){
		for (int i = 1;i <= 9;i++){
			string s;
			cin >> s;
			for (int j = 1;j <= 9;j++){
				r[i] |= 1 << (s[j - 1] - '0');
				c[j] |= 1 << (s[j - 1] - '0');
				g[(i - 1) / 3 + 1][(j - 1) / 3 + 1] |= 1 << (s[j - 1] - '0');
			}
		}
	}
	return 0;
}