#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
int n,a[N],cnt;
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	for (int i = 1;i <= a[n];i++){
		int j = n;
		while (j && a[j] >= i)	j--;
		cnt += n - j;
	}
	cout << cnt;
	return 0;
}