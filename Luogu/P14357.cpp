#include <bits/stdc++.h>
using namespace std;
priority_queue<int> a;
int main(int argc, char **argv){
#ifdef LOCAL
	bool isin,isout;
	cin >> isin >> isout;
	if (isin)
#endif
	freopen("number.in","r",stdin);
#ifdef LOCAL
	if (isout)
#endif
	freopen("number.out","w",stdout);
	
	char c;
	c = getchar();
	while (c != EOF){
		if (c >= '0' && c <= '9')	a.push(c - '0');
		c = getchar();
	}
	while (!a.empty()){
		cout << a.top();
		a.pop();
	}
	return 0;
}

