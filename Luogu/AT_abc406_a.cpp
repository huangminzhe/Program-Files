#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int a,b,c,d;
	cin >> a >> b >> c >> d;
	if (a == c){
		if (b > d)
			cout << "Yes";
		else
			cout << "No";
	}else if (a > c)
		cout << "Yes";
	else
		cout << "No";
	return 0;
}