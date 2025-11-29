#include <bits/stdc++.h>
using namespace std;
int n;
stack<int> s;
int main(int argc, char **argv){
	for (int i = 1;i <= 100;i++){
		s.push(0);
	}
	cin >> n;
	while (n--){
		int op;
		cin >> op;
		if (op == 1){
			int x;
			cin >> x;
			s.push(x);
		}else{
			cout << s.top() << endl;
			s.pop();
		}
	}
	return 0;
}