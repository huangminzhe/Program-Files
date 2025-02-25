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
	int lr = r[x - 1],lh = h[x - 1];
	// 体积过大或表面积超过之前的最小值
	if (v > n || s >= ans)	return ;
	// 拼尽全力无法完成目标
	if (v + lr * lr * lh * (m - x + 1) < n)	return;
	if (x > m){
		if (v == n)
			ans = s;
			// ans = min(ans,s);
		return ;
	}
	// 圆柱体积：PI*r^2*h
	// 圆柱侧面积：PI*2*r*h
	for (int ir = lr - 1;ir > m - x;ir--){
		for (int ih = lh - 1;ih > m - x;ih--){
			v += ir * ir * ih;
			s += 2 * ir * ih + (x == 1?ir * ir:0);
			r[x] = ir;
			h[x] = ih;
			dfs(x + 1,v,s);
			v -= ir * ir * ih;
			s -= 2 * ir * ih + (x == 1?ir * ir:0);
			r[x] = 0;
			h[x] = 0;
		}
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	h[0] = n,r[0] = 28;
	dfs(1,0,0);
	if (ans == INF)	cout << 0;
	else	cout << ans;
	return 0;
}