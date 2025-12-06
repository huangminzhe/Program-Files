#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 55;
int n,a[N],b[N],cnt;
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		b[i] = b[i - 1] + a[i];
	}
	for (int i = 1;i <= n;i++){
		for (int j = i;j <= n;j++){
			for (int k = i;k <= j;k++){
				if ((b[j] - b[i - 1]) % a[k] == 0)	goto noadd;
			}
			cnt++;
			noadd:
		}
	}
	cout << cnt;
	return 0;
}