#include <bits/stdc++.h>
using namespace std;
string d[3][2][2] = {
	{{"A320"},{"A350","A380"}},	// AIR
	{{"B737"},{"B787","B747"}},	// BOYIN
	{{"C919"}}	// CHN
};
int main(int argc, char **argv){
	char a,b;
	int c;
	cin >> a >> b >> c;
	cout << d[a - 'A'][b == 'W'][(c >> 1) - 1];
	return 0;
}