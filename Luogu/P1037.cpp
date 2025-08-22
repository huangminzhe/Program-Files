#include <bits/stdc++.h>
using namespace std;
typedef __int128 lll;
ostream& operator<<(ostream &out,lll x){
	if (x >= 10)	out << x / 10;
	out << int(x % 10);
	return out;
}

int t[10],sz[10];
bool a[10][10];
lll ans = 1;
int main(int argc, char **argv){
// 	freopen("gen.in","r",stdin);
// #ifndef LOCAL
// 	freopen("gen.ans","w",stdout);
// #endif
	string s;
	int n;
	cin >> s >> n;
	for (int i = 1;i <= n;i++){
		int x,y;
		cin >> x >> y;
		a[x][y] = 1;
	}
	for (int k = 1;k <= 9;k++)
		for (int i = 0;i <= 9;i++)
			for (int j = 1;j <= 9;j++)
				if (a[i][k] && a[k][j])	a[i][j] = 1;
	for (int i = 0;i <= 9;i++){
		a[i][i] = 1;
		for (int j = 0;j <= 9;j++){
			if (a[i][j])	sz[i]++;
		}
	}
	for (int i = 0;i < s.size();i++){
		ans *= sz[s[i] - '0'];
	}
	cout << ans;
	return 0;
}
