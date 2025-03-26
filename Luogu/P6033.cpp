#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int t[N];
queue<int> q1;
queue<ll> q2;
ll sum;
void read(int &x){
	x = 0;
	char c;
	do	c = getchar();
	while (c < '0' || c > '9');
	while (c >= '0' && c <= '9'){
		x *= 10;
		x += c - '0';
		c = getchar();
	}
}
int main(int argc, char **argv){
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++){
		int x;
		read(x);
		t[x]++;
	}
	for (int i = 1;i <= 1e5;i++){
		while (t[i]--)	q1.push(i);
	}
	for (int i = 1;i < n;i++){
		ll x = 0;
		if (!q1.empty() && q1.front() < q2.front() || q2.empty())	x += q1.front(),q1.pop();
		else	x += q2.front(),q2.pop();
		if (!q1.empty() && q1.front() < q2.front() || q2.empty())	x += q1.front(),q1.pop();
		else	x += q2.front(),q2.pop();
		sum += x;
		q2.push(x);
	}
	cout << sum;
	return 0;
}