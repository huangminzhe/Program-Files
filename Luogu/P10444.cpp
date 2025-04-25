#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv){
	int T,ID;
	cin >> T >> ID;
	if (ID == 4){
		while (T--){
			int n,x;
			cin >> n;
			for (int i = 1;i <= n;i++)	cin >> x;
			if (n < 4)
				cout << "No\n";
			else
				cout << "Yes\n";
		}
		return 0;
	}
	while (T--){
		int n;
		map<int,int> a;
		scanf("%d",&n);
		for (int i = 1;i <= n;i++){
			int x;
			scanf("%d",&x);
			a[x]++;
		}
		auto s = a.begin();auto e = a.rbegin();
		if ((*s).second > 1 && (*e).second > 1){
			printf("Yes");
			continue;
		}
		auto i = s;auto j = e;
		bool f = 0;
		for (i++,j++;(*i).first != (*j).first;){
			long long cha1 = 1LL * (*i).first - (*s).first,
					  cha2 = 1LL * (*e).first - (*j).first;
			if (cha1 == cha2){
				f = 1;
				break;
			}
			if (cha1 < cha2)
				i++;
			else
				j++;
		}
		if ((*i).first - (*s).first == (*e).first - (*j).first && (*i).second > 1)
			f = 1;
		if (f)	printf("Yes\n");
		else	printf("No\n");
	}
	return 0;
}