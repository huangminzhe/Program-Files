#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e3 + 5;
struct shop{
	int a,b,c;
}s[N];
int n,a,b,c;
ll dp[N][N];
bool cmp(shop b,shop c){
	if (b.a - b.b == c.a - c.b)	return b.b < c.b;
	return b.a - b.b < c.a - c.b;
}
int main(int argc, char **argv){
	freopen("furniture.in","r",stdin);
#ifndef LOCAL
	freopen("furniture.out","w",stdout);
#endif
	cin >> n >> a >> b >> c;
	for (int i = 1;i <= n;i++){
		cin >> s[i].a >> s[i].b >> s[i].c;
	}
	sort(s + 1,s + n + 1,cmp);
	memset(dp,0x3f,sizeof dp);
	dp[0][0] = 0;
	for (int i = 1;i <= n;i++){
		for (int j = 0;j <= c;j++){
			if (i - j <= a)	dp[i][j] = min(dp[i - 1][j - 1] + s[i].c,dp[i - 1][j] + s[i].a);
			else	dp[i][j] = min(dp[i - 1][j - 1] + s[i].c,dp[i - 1][j] + s[i].b);
		}
	}
	cout << dp[n][c];
	return 0;
}