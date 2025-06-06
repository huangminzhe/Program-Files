#include <bits/stdc++.h>
using namespace std;
const int N = 15,M = 105;
int b[N][N][M];
void init(int mod){
}
int solve(int x,int mod){
}
int main(int argc, char **argv){
	int A,B,mod;
	while (cin >> A >> B >> mod){
		init(mod);
		cout << solve(B,mod) - solve(A - 1,mod) << '\n';
	}
	return 0;
}