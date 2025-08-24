#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
int n,t[N],m,cnt[N],mx;
bool a[N][N];
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= m;j++){
			char c;
			cin >> c;
			if (c == '1')	a[i][j] = 1,t[j]++;
		}
	}
	for (int i = 1;i <= m;i++){
		if (!t[i] || t[i] == n){
			for (int j = 1;j <= n;j++)	cnt[j]++;
		}else if (t[i] < n - t[i]){
			for (int j = 1;j <= n;j++){
				if (a[j][i])	cnt[j]++;
			}
		}else{
			for (int j = 1;j <= n;j++){
				if (!a[j][i])	cnt[j]++;
			}
		}
	}
	for (int i = 1;i <= n;i++)	mx = max(mx,cnt[i]);
	for (int i = 1;i <= n;i++){
		if (cnt[i] == mx)	cout << i << ' ';
	}
	return 0;
}