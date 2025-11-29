#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
int n;
deque<pii> q;
int main(int argc, char **argv){
	cin >> n;
	while (n--){
		int op,x;
		cin >> op >> x;
		if (op == 1){
			int num;
			cin >> num;
			q.push_back({num,x});
		}else{
			ll sum = 0;
			while (x > q.front().second){
				x -= q.front().second;
				sum += (ll)q.front().first * q.front().second;
				q.pop_front();
			}
			int nw = q.front().second - x,num = q.front().first;
			sum += (ll)x * num;
			q.pop_front();
			q.push_front({num,nw});
			cout << sum << '\n';
		}
	}
	return 0;
}