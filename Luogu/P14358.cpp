#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n,m,a[N];
int main(int argc, char **argv){
#ifdef LOCAL
	bool isin,isout;
	cin >> isin >> isout;
	if (isin)
#endif
	freopen("seat.in","r",stdin);
#ifdef LOCAL
	if (isout)
#endif
	freopen("seat.out","w",stdout);
	
	cin >> n >> m;
	for (int i = 1;i <= n * m;i++){
		cin >> a[i];
	}
	int xm = a[1];
	sort(a + 1,a + n * m + 1);
	reverse(a + 1,a + n * m + 1);
	int pm = find(a + 1,a + n * m + 1,xm) - a;
	int c = (pm - 1) / n + 1,r = (pm - 1) % n + 1;
	cout << c << ' ' << (c & 1?r:n - r + 1);
	return 0;
}

