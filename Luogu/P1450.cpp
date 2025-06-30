#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int n,c[5],d[5],s;
ll dp[N];
int main(int argc, char **argv){
	for (int i = 1;i <= 4;i++)	cin >> c[i];
	dp[0] = 1;
	for (int i = 1;i <= 4;i++){
		for (int j = c[i];j <= 1e5;j++){
			dp[j] += dp[j - c[i]];
		}
	}
	cin >> n;
	while (n--){
		for (int i = 1;i <= 4;i++)	cin >> d[i];
		cin >> s;
		ll ans = dp[s];
		for (int i = 1;i < 16;i++){
			ll sum = 0;
			int cnt = 0;
			for (int j = 1;j <= 4;j++){
				if (i >> (j - 1) & 1){
					cnt++;
					sum += c[j] * (d[j] + 1);
				}
			}
			if (s >= sum)
				if (cnt & 1)	ans -= dp[s - sum];
				else	ans += dp[s - sum];
		}
		cout << ans << '\n';
	}
	return 0;
}