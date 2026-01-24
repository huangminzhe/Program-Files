#include <bits/stdc++.h>
using namespace std;
// #define decode(st) {0,st & 3,st >> 2 & 3,st >> 4 & 3,st >> 6 & 3}
const int N = 5,M = 10;
// N：物品/分区个数；M：边界

struct block{
	int x,y;
}blks[N];
struct item{
	int c,v,x,y;
}a[N];
struct state{	// 组合状态
	bool ok;
	int v,b;
	// ok：是否可行；v：方案价值；b：剩余格数
	bool operator<(const state c)const{
		if (ok == c.ok){
			if (v == c.v)	return b < c.b;
			return v < c.v;
		}
		return c.ok;
	}
};

int n,m,ansst;
int tot;	// 状态数
vector<state> st[N],dp[N];

array<int,N> decode(int);	// 每个物品有多少个（将状态解码）
bool canplace(vector<vector<bool>>&,array<int,N>,int,int,int);	// il的物品组合是否能放入分区bi内
vector<state> init(int);

int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> blks[i].x >> blks[i].y;
	}
	cin >> m;
	for (int i = 1;i <= m;i++){
		cin >> a[i].c >> a[i].v >> a[i].x >> a[i].y;
	}

	tot = 1;
	for (int i = 1;i <= m;i++)	tot *= 4;
	// 计算每个分区的组合情况
	for (int i = 1;i <= n;i++){
		st[i] = init(i);
	}

	// DP
	for (int i = 0;i <= n;i++)	dp[i] = vector<state>(tot);
	dp[0][0].ok = 1;
	for (int i = 1;i <= n;i++){
		dp[i][0].ok = 1;
		dp[i][0].b = dp[i - 1][0].b + blks[i].x * blks[i].y;
	}
	for (int i = 1;i <= n;i++){
		for (int j = 0;j < tot;j++){	// 上一轮状态
			if (!dp[i - 1][j].ok)	// 如果上一轮的j状态无法使用，那么无法加新的状态
				continue;

			for (int k = 0;k < tot;k++){	// 要加上的状态
				if (!st[i][k].ok){	// 如果第i分区的k状态不可用，那么j+k是不合法的
					continue;
				}
				auto dej = decode(j),dek = decode(k);
				// 数量检测
				for (int I = 1;I <= m;I++){
					if (dej[I] + dek[I] > a[I].c)	goto cont;
				}

				// 由于进行过数量检测，所以可以直接相加，没有进位问题
				dp[i][j + k] = max(dp[i][j + k],{1,dp[i - 1][j].v + st[i][k].v,dp[i - 1][j].b + st[i][k].b});

				cont:
			}
		}
	}

	for (int i = 0;i < tot;i++){
		if (dp[n][ansst] < dp[n][i])	ansst = i;
	}
	auto ans = decode(ansst);
	for (int i = 1;i <= m;i++){
		cout << ans[i] << '\n';
	}
	return 0;
}
vector<state> init(int bi){
	int bx = blks[bi].x,by = blks[bi].y;

	vector<state> res(tot);
	for (int st = 0;st < tot;st++){
		int zgs = 0,zv = 0;
		// zgs：总格数；zv：总价值
		int sti = 1;	// sti：开始物品种类
		vector<vector<bool>> f(M,vector<bool>(M));

		// 检测数量是否合法
		auto dec = decode(st);
		for (int j = 1;j <= m;j++){
			zv += dec[j] * a[j].v;
			if (dec[j] > a[j].c)
				goto cont;
		}

		// 检测空间是否足够
		for (int j = 1;j <= m;j++){
			zgs += a[j].x * a[j].y * dec[j];
		};
		if (zgs > bx * by)
			goto cont;

		while (!dec[sti] && sti <= m)	sti++;
		if (canplace(f,dec,bi,sti,0)){
			res[st] = {1,zv,bx * by - zgs};
		}

		cont:
	}
	return res;
}
array<int,N> decode(int st){	// 可使用define代替
	array<int,N> res = {0};
	for (int i = 1;i <= m;i++){
		res[i] = st & 3;
		st >>= 2;
	}
	return res;
}
bool canplace(vector<vector<bool>> &f,array<int,N> il,int bi,int idx,int num){	// il：物品数量数组
	if (idx > m){
		return 1;
	}

	int bx = blks[bi].x,by = blks[bi].y;
	int cx = a[idx].x,cy = a[idx].y;
	start:
	if (cx > blks[bi].x || 
		cy > blks[bi].y)
		goto end;
	
	// 搜索
	for (int i = 1;i <= bx - cx + 1;i++){
		for (int j = 1;j <= by - cy + 1;j++){
			int ni = idx,nn = num + 1;
			// 检测是否能放入
			for (int x = i;x < i + cx;x++){
				for (int y = j;y < j + cy;y++){
					if (f[x][y])
						goto cont;
				}
			}

// printf("%d %d %d %d %d %d\n",bi,idx,num,il[idx],i,j);
			for (int x = i;x < i + cx;x++){
				for (int y = j;y < j + cy;y++){
					f[x][y] = 1;
				}
			}
			if (nn == il[idx]){
				ni++,nn = 0;
				while (ni <= m && !il[ni])	ni++;
			}
			if (canplace(f,il,bi,ni,nn))
				return 1;
			// 回溯
			for (int x = i;x < i + cx;x++){
				for (int y = j;y < j + cy;y++){
					f[x][y] = 0;
				}
			}

			cont:
		}
	}
	end:
	swap(cx,cy);	// 旋转物品
	if (cx != a[idx].x && cy != a[idx].y)
		goto start;
	return 0;
}