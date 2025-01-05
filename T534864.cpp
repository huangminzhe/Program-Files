#include <bits/stdc++.h>
using namespace std;
map<int,int> t;
int main(int argc, char **argv){
	int T;
	cin >> T;
	while (T--){
		t.clear();
		bool f = 1;
		int n,s,e;
		cin >> n >> s;
		t[s]++;
		for (int i = 2;i < n;i++){
			int x;
			cin >> x;
			t[x]++;
			if (t[x] > 1)	f = 0;
		}
		if (n > 1) cin >> e,t[e]++;
		if (f)	printf("%d\n",n);
		else if (s == e)	printf("1\n");
		else if (t[s] == 1 && t[e] == 1)	printf("3\n");
		else	printf("2\n");
	}
	return 0;
}
