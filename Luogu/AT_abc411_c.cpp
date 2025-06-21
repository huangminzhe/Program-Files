#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
int n,q,cnt;
bool L[N],R[N],a[N];
int main(int argc, char **argv){
	cin >> n >> q;
	while (q--){
		int x;
		cin >> x;
		if (a[x]){
			if (R[x] && L[x]){
				cnt--;
				L[x] = 0;
				R[x] = 0;
			}else if (L[x]){
				L[x] = 0;
				L[x + 1] = 1;
			}else if (R[x]){
				R[x] = 0;
				R[x - 1] = 1;
			}
		}else{
			if (R[x - 1] && L[x + 1]){
				cnt--;
				R[x - 1] = 0;
				L[x + 1] = 0;
			}else if (!R[x - 1] && !L[x + 1]){
				cnt++;
				L[x] = 1;
				R[x] = 1;
			}else if (R[x - 1]){
				R[x - 1] = 0;
				R[x] = 1;
			}else if (L[x + 1]){
				L[x + 1] = 0;
				L[x] = 1;
			}
		}
		a[x] = !a[x];
		cout << cnt << '\n';
	}
	return 0;
}