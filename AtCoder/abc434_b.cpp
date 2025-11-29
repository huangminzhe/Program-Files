#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
int n,t[N],sum[N],m;
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		int a,b;
		cin >> a >> b;
		t[a]++;
		sum[a] += b;
	}
	for (int i = 1;i <= m;i++){
		printf("%.5f\n",1.0 * sum[i] / t[i]);
	}
	return 0;
}