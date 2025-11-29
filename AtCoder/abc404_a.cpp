#include <bits/stdc++.h>
using namespace std;
int a[30];
int main(int argc, char **argv){
	char c;
	while ((cin >> c) && c){
		a[c - 'a']++;
	}
	for (int i = 0; i < 26; i++){
		if (!a[i]){
			cout << char('a' + i);
			return 0;
		}
	}
	return 0;
}