#include <bits/stdc++.h>
using namespace std;
const int N = 4e4 + 5,SQRTN = 205;
int n,m,a[N];	// 原
int bn,bs,pos[N],bl[SQRTN],br[SQRTN],t[SQRTN][N],ans[SQRTN][SQRTN];	// 分块
/*
bn：块数；
bs：块长度；
pos[i]：a[i] 属于的块；
bl[i]：第 i 块的开头；
br[i]：第 i 块的结尾；
t[i][j]：第 1 块到第 i 块中，j 出现的次数；
ans[i][j]：第 i 块到第 j 块间的答案。
*/
int sd;	// 解码
inline void decl(int &l){l = ((l + sd - 1) % n + 1);}
inline void decr(int &r){r = ((r + sd - 1) % n + 1);}
void init(){
	bs = sqrt(n);
	bn = n / bs + (n % bs?1:0);
	for (int i = 1;i <= bn;i++){	// 初始化范围
		bl[i] = br[i - 1] + 1;
		br[i] = bl[i] + bs - 1;
	}
	br[bn] = n;
	for (int i = 1;i <= bn;i++)	// 初始化每个数属于的块
		for (int j = bl[i];j <= br[i];j++)
			pos[j] = i;

	for (int i = 1;i <= bn;i++){	// 初始化桶，但是用分块存成前缀和
		for (int j = 1;j <= n;j++)
			t[i][a[j]] = t[i - 1][a[j]];
		for (int j = bl[i];j <= br[i];j++)
			t[i][a[j]]++;
	}
	for (int i = 1;i <= bn;i++){	// 求第 i 到第 j 块的答案
		for (int j = i;j <= bn;j++){
			int mxi = bl[i],mx = 1;
			for (int k = bl[i];k <= br[i];k++){
				// 求第 i 到第 j 块 k 的出现次数（区间和）
				int sect = t[j][a[k]] - t[i - 1][a[k]];
				// 如果当前种类数量比最大值多，或数量相等，编号更小（要求）
				if (mx < sect || mx == sect && a[k] < a[mxi]){
					mxi = k;
					mx = sect;
				}
			}
			ans[i][j] = a[mxi];
		}
	}
}
int query(int l,int r){
	int tt[N] = {0};	// 没有分块的桶排序
	int lb = pos[l],rb = pos[r];	// l 属于的块，r 属于的块
	int mxi = l,mx = 0;
	if (rb - lb < 2){	// 防止 [lb + 1][rb - 1] RE
		for (int i = l;i <= r;i++)
			tt[a[i]]++;
		for (int i = l;i <= r;i++){
			if (tt[a[i]] > mx || tt[a[i]] == mx && a[i] < a[mxi]){
				mxi = a[i];
				mx = tt[a[i]];
			}
		}
		return a[mxi];
	}
	// 散块中出现的次数
	for (int i = l;i <= br[lb];i++)
		tt[a[i]]++;
	for (int i = bl[rb];i <= r;i++)
		tt[a[i]]++;
	// 记上中间的次数
	for (int i = l;i <= br[lb];i++){
		// ttai 是散块加中间，这里用区间和，算的是 [lb + 1][rb - 1]，下同
		// 注意：这里不能用 +=，避免这个数在散块重复出现。下同
		int ttai = tt[a[i]] + t[rb - 1][a[i]] - t[lb][a[i]];
		if (ttai > mx || ttai == mx && a[i] < a[mxi]){
			mxi = a[i];
			mx = ttai;
		}
	}
	for (int i = bl[rb];i <= r;i++){
		int ttai = tt[a[i]] + t[rb - 1][a[i]] - t[lb][a[i]];
		if (ttai > mx || ttai == mx && a[i] < a[mxi]){
			mxi = a[i];
			mx = ttai;
		}
	}
	// 中间
	// 当前的 mxi 是左散块和右散块的众数，mx 是众数出现的次数（包括中间）。
	// 现在把中间（不加散块）的众数和散块（已加中间）的比较
	int mid = ans[lb + 1][rb - 1];
	int ttai = tt[mid] + t[rb - 1][mid] - t[lb][mid];
	if (ttai > mx || ttai == mx && mid < a[mxi])
		mxi = mid;
	return mxi;
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		scanf("%d",a + i);
	}
	init();
	while (m--){
		int l,r;
		scanf("%d %d",&l,&r);
		decl(l),decr(r);
		if (l > r)	swap(l,r);
		sd = query(l,r);
		printf("%d\n",sd);
	}
	return 0;
}