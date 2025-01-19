#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int a[N][N],x,y,cnt;
bool f[N][N];
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m >> x >> y;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= m;j++){
			char c;
			cin >> c;
			if (c == '.')	a[i][j] = 1;
			else if (c == '@')	a[i][j] = 2;
		}
	}
	string s;
	cin >> s;
	for (int i = 0;i < s.size();i++){
		if (s[i] == 'U'){
			if (a[x - 1][y])	x--;
		}else if (s[i] == 'D'){
			if (a[x + 1][y])	x++;
		}else if (s[i] == 'L'){
			if (a[x][y - 1])	y--;
		}else{
			if (a[x][y + 1])	y++;
		}
		if (a[x][y] == 2 && !f[x][y])	cnt++,f[x][y] = 1;
	}
	printf("%d %d %d",x,y,cnt);
	return 0;
}