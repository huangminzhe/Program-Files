#include <bits/stdc++.h>
using namespace std;
const int N = 105,INF = 0x7fffffff;
int a[N][N];
vector<int> pa;
int fact(int x){
	if (x == 0)	return 1;
	return x * fact(x - 1);
}
int main(int argc, char **argv){
	int n,p;
	cin >> n;
	for (int i = 1;i <= n;i++)	fill(a[i] + 1,a[i] + n + 1,INF / 2);
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			cin >> a[i][j];
		}
	}
	cin >> p;
	for (int i = 1;i <= p;i++){
		int x;
		cin >> x;
		pa.push_back(x);
	}

	for (int k = 1;k <= n;k++){
		for (int i = 1;i <= n;i++){
			for (int j = 1;j <= n;j++){
				a[i][j] = min(a[i][j],a[i][k] + a[k][j]);
			}
		}
	}

	int ans = INF;
	for (int I = 1;I <= fact(p);I++,next_permutation(pa.begin(),pa.end())){
		int sum = a[1][pa[0]] + a[pa[p - 1]][n];
		for (int i = 1;i < p;i++){
			sum += a[pa[i - 1]][pa[i]];
		}
		ans = min(ans,sum);
	}
	cout << ans;
	return 0;
}