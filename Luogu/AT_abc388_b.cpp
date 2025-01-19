#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int a[N],b[N];
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		cin >> a[i] >> b[i];
	}
	int mx;
	for (int i = 1;i <= m;i++){
		mx = 0;
		for (int j = 1;j <= n;j++){
			mx = max(mx,a[j] * (b[j] + i));
		}
		printf("%d\n",mx);
	}
	return 0;
}