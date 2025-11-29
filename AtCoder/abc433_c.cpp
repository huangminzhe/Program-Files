#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
int R[N] = {-1},n,cnt;
string s;
int main(int argc, char **argv){
	cin >> s;
	for (int i = 1;i < s.size();i++){
		if (s[i] != s[i - 1])	R[++n] = i - 1;
	}
	R[++n] = s.size() - 1;
	for (int i = 1;i < n;i++){
		if (s[R[i]] + 1 == s[R[i + 1]])	cnt += min(R[i + 1] - R[i],R[i] - R[i - 1]);
	}
	cout << cnt;
	return 0;
}