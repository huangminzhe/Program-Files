#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int t[N],cnt;
int main(int argc, char **argv){
	int n,a,b,c;
	cin >> n >> a;
	for (int i = 0;i < a;i++){
		int x;
		cin >> x;
		t[x]++;
	}
	cin >> b;
	for (int i = 0;i < b;i++){
		int x;
		cin >> x;
		t[x]++;
	}
	cin >> c;
	for (int i = 0;i < c;i++){
		int x;
		cin >> x;
		t[x]++;
	}
	for (int i = 1;i <= n;i++){
		if (t[i] != 1)	cnt++;
	}
	cout << cnt;
	return 0;
}
