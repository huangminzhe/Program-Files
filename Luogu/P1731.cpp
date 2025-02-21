#include <bits/stdc++.h>
using namespace std;
const int N = 2e4 + 5,INF = 0x7fffffff;
int n,m,ans = INF;
int h[N],r[N];
/*
x：从下往上第几层
v：当前总体积/PI
s：当前总表面积
*/
void dfs(int x,int v,int s){
	if (x > m){
		if (v == n)
			ans = v;
			// ans = min(ans,v);
		return ;
	}
	for (int ir = r[x - 1] - 1;ir > 0;ir--){
		for (int ih = h[x - 1] - 1;ih > 0;ih--){
			v += ir * ir * ih;
			s += 2 * ir * ih + (x == 1?ir * ir:0);
			r[x] = ir;
			h[x] = ih;
			dfs(x + 1,v,s);
			v -= ir * ir * ih;
			s += 2 * ir * ih + (x == 1?ir * ir:0);
			r[x] = 0;
			h[x] = 0;
		}
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	h[0] = sqrt(n),r[0] = sqrt(n);
	dfs(1,0,0);
	if (ans == INF)	cout << 0;
	else	cout << ans;
	return 0;
}