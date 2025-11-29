#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5,INF = 1e9;
int n,mxx,mnx = INF,mxy,mny = INF;
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		int x,y;
		cin >> x >> y;
		mxx = max(mxx,x);
		mnx = min(mnx,x);
		mxy = max(mxy,y);
		mny = min(mny,y);
	}
	cout << (max(mxx - mnx,mxy - mny) + 1 >> 1);
	return 0;
}