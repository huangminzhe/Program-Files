#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
bool a[N];
int cnt;
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	cnt = n - m;
	for (int i = 1;i <= m;i++){
		int x;
		cin >> x;
		if (a[x])	cnt--;
		a[x] = 1;
	}
	printf("%d\n",cnt);
	for (int i = 1;i <= n;i++){
		if (!a[i])	printf("%d ",i);
	}
	return 0;
}