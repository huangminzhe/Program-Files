#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100;
int n,a[N][N],tot;
void write(int x,int y,int val){
	tot++;
	a[x][y] = val;
	if (tot == n * n)	return ;
	if (!a[(x + n - 1) % n][(y + 1) % n]){
		write((x + n - 1) % n,(y + 1) % n,val + 1);
	}else{
		write((x + 1) % n,y,val + 1);
	}
}
int main(int argc, char **argv){
	cin >> n;
	write(0,n / 2,1);
	for (int i = 0;i < n;i++){
		for (int j = 0;j < n;j++){
			cout << a[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}