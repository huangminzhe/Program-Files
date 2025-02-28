#include <bits/stdc++.h>
using namespace std;
const int N = 50;
int dep,ans[N],t[N];
void gcd(int &a,int &b){
	int g = __gcd(a,b);
	a /= g,b /= g;
}
bool dfs(int x,int a,int b){
	for (int i = max(ans[x - 1] + 1,(a + b - 1) / b);i <= ;i++){}
}
int main(int argc, char **argv){
	int a,b;
	cin >> a >> b;
	gcd(a,b);

	dep = 1,t[0] = ceil(1.0 * b / a);
	while (!dfs(1,a,b))	dep++;

	for (int i = 1;i <= dep;i++)	cout << ans[i] << ' ';
	return 0;
}