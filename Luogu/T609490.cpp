#include <bits/stdc++.h>
using namespace std;
bool f = 1;
int main(int argc, char **argv){
	string s;
	cin >> s;
	long long n = s.size();
	if (n & 1){
		s = '0' + s;
		n++;
	}
	for (long long i = n;i > 0;i -= 2){
		long long si = i - 1;
		if (f && s[si - 1] == '0' && s[si] == '0')	continue;
		if (f && s[si - 1] == '0')
			cout << s[si];
		else
			cout << s[si - 1] << s[si];
		f = 0;
	}
	if (f)	cout << 0;
	return 0;
}