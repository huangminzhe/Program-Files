#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 5;
int a[N],b[N],t[N];
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		b[i] = a[i];
	}
	sort(b + 1,b + n + 1);
	reverse(b + 1,b + n + 1);
	for (int i = 1;i <= n;i++){
		if (b[i] == b[i - 1])	continue;
		t[b[i]] = i;
	}
	for (int i = 1;i <= n;i++){
		cout << t[a[i]] << endl;
	}
	return 0;
}