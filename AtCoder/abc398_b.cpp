#include <bits/stdc++.h>
using namespace std;
int a[15];
bool f3,f2;
int main(int argc, char **argv){
	for (int i = 1;i <= 7;i++){
		int x;
		cin >> x;
		a[x]++;
	}
	for (int i = 1;i <= 13;i++){
		if (!f3 && a[i] >= 3)	f3 = 1;
		else if (a[i] >= 2)	f2 = 1;
	}
	if (f3 && f2)	cout << "Yes";
	else	cout << "No";
	return 0;
}