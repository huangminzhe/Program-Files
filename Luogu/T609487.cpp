#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int w,f,a,r;
	cin >> w >> f >> a >> r;
	if (w < r || 1.0 * f / w > 0.2 || 1.0 * a / w > 0.3)
		cout << "Rejected";
	else
		cout << "Accepted";
	return 0;
}