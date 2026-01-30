#include <bits/stdc++.h>
using namespace std;
int a[5][5],x,y;
bool f[5];
int main(int argc, char **argv){
	for (int i = 1;i <= 4;i++){
		for (int j = 1;j <= 4;j++){
			cin >> a[i][j];
			if (!a[i][j])	x = i,y = j;
		}
	}
	for (int i = 1;i <= 4;i++){
		f[a[x][i]] = 1;
	}
	for (int i = 1;i <= 4;i++){
		if (!f[i]){
			cout << i;
			return 0;
		}
	}
	return 0;
}