#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
int n,m;
bool cf[N];
char s[N],t[N];
int main(int argc, char **argv){
	cin >> n >> m >> s + 1 >> t + 1;
	for (int i = 1;i <= m;i++){
		int l,r;
		cin >> l >> r;
		cf[l] = !cf[l];
		cf[r + 1] = !cf[r + 1];
	}
	bool zt = 0;
	for (int i = 1;i <= n;i++){
		if (cf[i])	zt = !zt;
		if (zt)	cout << t[i];
		else	cout << s[i];
	}
	return 0;
}