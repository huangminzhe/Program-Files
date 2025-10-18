#include <bits/stdc++.h>
using namespace std;
stack<int> s1,s2;
int main(int argc, char **argv){
	int n;
	cin >> n;
	s1.push(0);
	s2.push(0);
	while (n--){
		int op;
		cin >> op;
		if (op == 1){
			char c;
			cin >> c;
			s1.push(s1.top() + (c == '('?1:-1));
			s2.push(min(s1.top(),s2.top()));
		}else{
			s1.pop();
			s2.pop();
		}
		cout << (s1.top() == 0 && s2.top() == 0?"Yes":"No") << '\n';
	}
	return 0;
}