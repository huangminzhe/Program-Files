#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N = 1e6 + 5,INF = 0x7fffffff;
pii a[N];
int r = 1,cnt,cf[N],sum,mn = INF;
bool cmp(pii b,pii c){
	if (b.second == c.second)	return b.first < c.first;
	return b.second < c.second;
}
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		cin >> a[i].first >> a[i].second;
		cf[a[i].first]++,cf[a[i].second + 1]--;
	}
	// sort(a + 1,a + n + 1,cmp);
	// for (int i = 1;i <= m;i++){
	// 	if (r < a[i].first){
	// 		cout << 0;
	// 		return 0;
	// 	}
	// }
	for (int i = 1;i <= n;i++){
		sum += cf[i];
		mn = min(mn,sum);
	}
	cout << mn;
	return 0;
}