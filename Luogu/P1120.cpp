#include <bits/stdc++.h>
using namespace std;
const int N = 70;
int w[N],n,m,ans,sum,nxt[N];
bool f[N];
/*
x：拼到第几根
l：当前木棍长度
pv：用到第几根
*/
bool dfs(int x,int l,int pv){
	if (x > ans)	return 1;
	if (l == m)	return dfs(x + 1,0,1);
	int no = 0;	// 相同木棍长度不行直接跳过（排过序，所以不会有问题）
	for (int i = pv;i <= n;i++){
		// 用过或超长或跟上次失败长度一样
		if (f[i] || l + w[i] > m || no == w[i])	continue;
		f[i] = 1;
		if (dfs(x,l + w[i],i + 1))	return 1;
		no = w[i];
		f[i] = 0;
		// 如果是第一根，在后面也会作为第一根（排了序），所以一定失败
		// 如果是最后一根，那么剩下怎么拼也拼不出来了（后面会是相同情况）
		if (!l || l + w[i] == m)	return 0;
		i = nxt[i];
	}
	return 0;
}
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> w[i];
		sum += w[i];
	}
	sort(w + 1,w + n + 1);
	reverse(w + 1,w + n + 1);
	nxt[n] = n;
	for (int i = n - 1;i > 0;i--){
		nxt[i] = i;
		if (w[i] == w[i + 1])	nxt[i] = nxt[i + 1];
	}
	for (int i = w[1];i <= sum;i++){
		if (sum % i)	continue;
		m = i;	// 原始长度
		ans = sum / i;	// 多少根
		if (dfs(1,0,1))	break;
		memset(f,0,sizeof f);
	}
	cout << m;
	return 0;
}