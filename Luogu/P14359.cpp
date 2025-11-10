#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int n,k,a[N],b[N],to[N * 3],cnt,l;
int main(int argc, char **argv){
	cin >> n >> k;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		b[i] = b[i - 1] ^ a[i];
	}
	memset(to,-1,sizeof to);
	to[0] = 0;
	for (int i = 1;i <= n;i++){
		if (to[b[i] ^ k] >= l)
			cnt++,l = i;
		to[b[i]] = i;
	}
	cout << cnt;
	return 0;
}