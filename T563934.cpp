#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int a,b;
	cin >> a >> b;
	a %= 10;
	if (b < a)	printf("%d",b + 10 - a);
	else	printf("%d",b - a);
	return 0;
}