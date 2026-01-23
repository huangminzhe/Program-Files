#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 50;
int n,m,q;
bool s[N],t[N];
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		char x;
		cin >> x;
		s[x - 'a'] = 1;
	}
	for (int i = 1;i <= m;i++){
		char x;
		cin >> x;
		t[x - 'a'] = 1;
	}
	cin >> q;
	while (q--){
		string w;
		cin >> w;
		for (int i = 0;i < w.size();i++){
			if (s[w[i] - 'a'] && !t[w[i] - 'a']){
				goto tkhs;
			}else if (t[w[i] - 'a'] && !s[w[i] - 'a']){
				goto aoki;
			}
		}
		cout << "Unknown\n";
		goto end;
		tkhs:
		cout << "Takahashi\n";
		goto end;
		aoki:
		cout << "Aoki\n";
		end:
	}
	return 0;
}