#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n;
vector<int> a;
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++){
		int x;
		cin >> x;
		auto it = lower_bound(a.begin(),a.end(),x);
		a.emplace(it,x);
		// for (int j = 0;j < a.size();j++){
		// 	cout << a[j] << " ";
		// }
		// cout << endl;
		if (i & 1){
			cout << a[(i >> 1)] << endl;
		}
	}
	return 0;
}