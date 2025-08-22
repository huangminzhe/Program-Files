#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n,fu[N],zh[N],fen[N],sum;
int main(int argc, char **argv){
	cin >> n;
	for (int i = 1;i <= n;i++)	cin >> fu[i];
	for (int i = 1;i <= n;i++)	cin >> zh[i];
	for (int i = 1;i <= n;i++)	cin >> fen[i];
	for (int i = 1;i <= n;i++)	sum += max(0,fen[i] - abs(fu[i] - zh[i]));
	cout << sum;
	return 0;
}