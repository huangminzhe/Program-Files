#include <bits/stdc++.h>
using namespace std;
priority_queue<int> q;
int main(int argc, char **argv){
	int n;
	cin >> n;
	while (n--){
		int op;
		cin >> op;
		if (op == 1){
			int x;
			cin >> x;
			q.push(-x);
		}else{
			cout << -q.top() << '\n';
			q.pop();	
		}
	}
	return 0;
}