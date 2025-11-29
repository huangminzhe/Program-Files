#include <bits/stdc++.h>
using namespace std;
int d;
int main(int argc, char **argv){
	int s,a,b,x;
	cin >> s >> a >> b >> x;
	for (int i = 1;i <= x;i += b){
		for (int j = 1;i <= x && j <= a;i++,j++){
			d += s;
		}
	}
	cout << d;
	return 0;
}