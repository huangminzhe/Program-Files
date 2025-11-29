#include <bits/stdc++.h>
using namespace std;
bool sum[15][15],sub[10][10];
int a;
int main(int argc, char **argv){
	int x,y;
	cin >> x >> y;
	for (int i = 1;i <= 6;i++){
		for (int j = 1;j <= 6;j++){
			if (i + j >= x)	sum[i][j] = 1;
			if (abs(i - j) >= y)	sub[i][j] = 1;
		}
	}
	for (int i = 1;i <= 6;i++){
		for (int j = 1;j <= 6;j++){
			if (sum[i][j] || sub[i][j])	a++;
		}
	}
	printf("%.10f",1.0 * a / 36);
	return 0;
}