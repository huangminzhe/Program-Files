#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n,cnt[N * 2];ll sum;
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		int x;
		cin >> x;
		if (i > x)	sum += cnt[i - x];
		cnt[x + i]++;
	}
	cout << sum;
	return 0;
}