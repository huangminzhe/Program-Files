#include <bits/stdc++.h>
using namespace std;
queue<int> q;
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		int op;
		cin >> op;
		if (op == 1){
			int x;
			cin >> x;
			q.push(x);
		}else if (!q.empty()){
			cout << q.front() << '\n';
			q.pop();
		}
	}
	return 0;
}