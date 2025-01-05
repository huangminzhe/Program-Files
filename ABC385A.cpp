#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int a,b,c;
	cin >> a >> b >> c;
	if ((a == b && b == c) || 
		(a + b == c) || 
		(a + c == b) || 
		(b + c == a)){
		printf("Yes");
	}else	printf("No");
	return 0;
}
