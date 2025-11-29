#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	if (n == 1)	cout << m + 1;
	else{
		if (m >= 30)	cout << "inf";
		else{
			long long ans = 1,cnt = 1;
			for (int i = 1;i <= m;i++){
				cnt *= n;
				ans += cnt;
				if (ans > 1e9){
					cout << "inf";
					return 0;
				}
			}
			cout << ans;
		}
	}
	return 0;
}