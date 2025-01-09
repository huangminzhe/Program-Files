#include <bits/stdc++.h>
using namespace std;
const int N = 4e4 + 5,SQRTN = 205;
int n,m,a[N];	// 原
int bn,bs,pos[N],bl[SQRTN],br[SQRTN];	// 分块
int sd;	// 解码
inline void decl(int &l){l = ((l + sd - 1) % n + 1);}
inline void decr(int &r){r = ((r + sd - 1) % n + 1);}
void init(){
	bs = sqrt(n);
	bn = n / bs + (n % bs?1:0);
	for (int i = 1;i <= bn;i++){
		bl[i] = br[i - 1] + 1;
		br[i] = bl[i] + bs - 1;
	}
	br[bn] = n;
	for (int i = 1;i <= bn;i++){
		for (int j = bl[i];j <= br[i];j++){
			pos[j] = i;
		}
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	init();
	return 0;
}