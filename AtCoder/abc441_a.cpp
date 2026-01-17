#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int x,y,i,j;
	cin >> x >> y >> i >> j;
	if (i >= x && i <= x + 99 && 
		j >= y && j <= y + 99)
		cout << "Yes";
	else
		cout << "No";
	return 0;
}