#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int x,y,z,a;
	cin >> x >> y >> z >> a;
	cout << (a < y?min(x * a,y * z):a * z);
	return 0;
}