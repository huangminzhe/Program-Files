#include <bits/stdc++.h>
using namespace std;
int t[10],mn = 10;
int main(int argc, char **argv){
	char c = getchar();
	while (c != '\n'){
		if (c - '0')	mn = min(mn,c - '0');
		t[c - '0']++;
		c = getchar();
	}
	cout << mn;
	t[mn]--;
	for (int i = 0;i <= 9;i++){
		for (int j = 1;j <= t[i];j++){
			cout << i;
		}
	}
	return 0;
}