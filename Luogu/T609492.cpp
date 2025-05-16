#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int k;
	cin >> k;
	cout << (256 - k) * (257 - k) * (513 - 2 * k) / 6;
	return 0;
}