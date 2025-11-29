#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int r,x;
	cin >> r >> x;
	if (x == 1 && r >= 1600 && r <= 2999 || 
		x == 2 && r >= 1200 && r <= 2399)
		cout << "Yes";
	else
		cout << "No";
	return 0;
}