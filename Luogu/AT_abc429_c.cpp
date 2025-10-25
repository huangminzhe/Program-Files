#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n;
ll sum;
unordered_map<int,int> t;
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		int x;
		cin >> x;
		t[x]++;
	}
	for (auto [i,ci] : t){
		if (ci >= 2){
			ll c = (ll)ci * (ci - 1) / 2;	// C^{ci}_{2};
			sum += c * (n - ci);
		}
	}
	cout << sum;
	return 0;
}