#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int x,y;
	cin >> x >> y;
	cout << (x + y - 1) % 12 + 1;
	return 0;
}