#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N = 5e5 + 5;
int n,a[N],cnt;
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
	cnt = 1;
	for (int i = 1;i <= min(cnt,n);i++){
		cnt = max(cnt,i + a[i] - 1);
	}
	cout << min(n,cnt);
	return 0;
}