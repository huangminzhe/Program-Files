#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n,m,k,a[N],b[N],cnt;
int main(int argc, char **argv){
	cin >> n >> m >> k;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	for (int i = 1;i <= m;i++){
		cin >> b[i];
	}
	sort(a + 1,a + n + 1);
	sort(b + 1,b + m + 1);
	for (int i = 1,j = 1;i <= n && j <= m;){
		if (a[i] <= b[j])	cnt++,i++,j++;
		else	j++;
	}
	if (cnt >= k)	cout << "Yes";
	else	cout << "No";
	return 0;
}