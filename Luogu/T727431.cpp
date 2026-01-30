#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		map<char,ll> a;
		int n;
		cin >> n;
		string s;
		cin >> s;
		for (int i = 1;i <= n;i++){
			char c,d;
			ll x;
			cin >> c >> d >> x;
			a[c] = x;
		}
		ll r = 0,l = 0;
		bool op = 1;
		for (int i = 0;i < s.size();i++){
			if (s[i] == '+')	op = 1;
			else if (s[i] == '-')	op = 0;
			else if (s[i] == '=')	l = r,r = 0,op = 1;
			else if (s[i] >= 'a' && s[i] <= 'z'){
				r += op?a[s[i]]:-a[s[i]];
			}else{
				ll num = 0;
				while (s[i] >= '0' && s[i] <= '9')	num = num * 10 + s[i] - '0',i++;
				r += op?num:-num;
			}
		}
		if (l == r){
			cout << "Yes\n";
		}else{
			cout << "No\n";
		}
	}
	return 0;
}