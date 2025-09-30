#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int cf[N],sum,mx;
int main(int argc, char **argv){
	int n;
	cin >> n;
	while (n--){
		int a,b;
		cin >> a >> b;
		cf[a]++,cf[b + 1]--;
	}
	for (int i = 0;i <= 1e6;i++){
		sum += cf[i];
		mx = max(sum,mx);
	}
	cout << mx;
	return 0;
}