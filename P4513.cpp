#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5,INF = 0x7fffffff;
/**
 @brief mx：连续子序列的最大值；
 @brief sum：该序列的和；
 @brief lmx：以左端点为开头的连续子序列的最大值；
 @brief rmx：以右端点为结尾的连续子序列的最大值。
*/
struct SGT{
	ll mx,sum,lmx,rmx;
}d[4 * N];
int a[N];
void up(int p){ // 核心代码
	d[p].sum = d[p * 2].sum + d[p * 2 + 1].sum;
	d[p].lmx = max(d[p * 2].lmx,d[p * 2].sum + d[p * 2 + 1].lmx);
	d[p].rmx = max(d[p * 2 + 1].rmx,d[p * 2].rmx + d[p * 2 + 1].sum);
	d[p].mx = max({d[p * 2].mx,d[p * 2 + 1].mx,d[p * 2].rmx + d[p * 2 + 1].lmx});
}
void build(int l,int r,int p){
	d[p].mx = d[p].lmx = d[p].rmx = -INF;
	if (l == r){
		d[p].mx = d[p].lmx = d[p].rmx = d[p].sum = a[l];
		return ;
	}
	int mid = l + (r - l >> 1);
	build(l,mid,p * 2);
	build(mid + 1,r,p * 2 + 1);
	up(p);
}
void mod(int i,int l,int r,int p,int x){
	if (l == i && i == r){
		d[p].mx = d[p].lmx = d[p].rmx = d[p].sum = x;
		return ;
	}
	int mid = l + (r - l >> 1);
	if (i <= l)	mod(i,l,mid,p * 2,x);
	else	mod(i,mid + 1,r,p * 2 + 1,x);
	up(p);
}
SGT query(int tl,int tr,int l,int r,int p){
	if (tl <= l && r <= tr)	return d[p];
	int mid = l + (r - l >> 1);
	if (tr <= mid)	return query(tl,tr,l,mid,p * 2);	// 全在左边
	else if (tl > mid)	return query(tl,tr,mid + 1,r,p * 2 + 1);	//全在右边
	else{	// 两边都有
		SGT res,ls = query(tl,tr,l,mid,p * 2),rs = query(tl,tr,mid + 1,r,p * 2 + 1);
		res.lmx = max(ls.lmx,ls.sum + rs.lmx);
		res.rmx = max(rs.rmx,ls.rmx + rs.sum);
		res.mx = max({ls.mx,rs.mx,ls.rmx + rs.lmx});
		return res;
	}
}
int main(int argc, char **argv){
	// freopen("C:/Users/Administrator/Downloads/P4513_2.in","r",stdin);
	// freopen("C:/Users/Administrator/Downloads/P4513_2.ans","w",stdout);
	int n,m;
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		scanf("%d",a + i);
	}
	build(1,n,1);
	while (m--){
		int op,l,r;
		scanf("%d %d %d",&op,&l,&r);
		if (op == 1){
			if (l > r)	swap(l,r);
			printf("%d\n",query(l,r,1,n,1).mx);
		}
		else	mod(l,1,n,1,r);
	}
	return 0;
}