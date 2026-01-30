#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int a,b,c,d,e;
	cin >> a >> b >> c >> d >> e;
	int f = a + b + c + d + e;
	if (f < 100){
		cout << "Grey";
	}else if (f < 120){
		cout << "Blue";
	}else if (f < 170){
		cout << "Green";
	}else if (f < 230)
		cout << "Orange";
	else
		cout << "Red";
	return 0;
}