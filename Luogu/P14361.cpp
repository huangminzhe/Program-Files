#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
struct person{
	int a,b,c;
}a[N];
int n,b[N],ans,cnt1,cnt2,cnt3;
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		cin >> n;
		for (int i = 1;i <= n;i++){
			cin >> a[i].a >> a[i].b >> a[i].c;
		}
		for (int i = 1;i <= n;i++){
			if (a[i].a >= max(a[i].b,a[i].c)){
				b[i] = 1,ans += a[i].a,cnt1++;
			}else if (a[i].b >= max(a[i].a,a[i].c)){
				b[i] = 2,ans += a[i].b,cnt2++;
			}else{
				b[i] = 3,ans += a[i].c,cnt3++;
			}
		}
	}
	return 0;
}