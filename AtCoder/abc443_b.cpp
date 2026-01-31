#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int n,k;
	cin >> n >> k;
	int cnt = n,ans = n;
	while (cnt < k)
		cnt += ++ans;
	cout << ans - n;
	return 0;
}