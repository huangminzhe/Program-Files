#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5,INF = 0x7fffffff;
int n,m,q,u,v,t;
int a[N];
queue<int> hp[3];
int main(int argc, char **argv){
	cin >> n >> m >> q >> u >> v >> t;
	for (int i = 1;i <= n;i++){
		scanf("%d",a + i);
	}
	sort(a + 1,a + n + 1);
	reverse(a + 1,a + n + 1);
	for (int i = 1;i <= n;i++)	hp[0].push(a[i]);
	for (int i = 0;i < m;i++){
		pair<int,int> x = max({make_pair(hp[0].empty()?-INF:hp[0].front(),0),
							   make_pair(hp[1].empty()?-INF:hp[1].front(),1),
							   make_pair(hp[2].empty()?-INF:hp[2].front(),2)});
		hp[x.second].pop();
		ll len = x.first + q * i;
		if ((i + 1) % t == 0)	printf("%d ",len);
		hp[1].push(len * u / v - q - q * i);
		hp[2].push(len - len * u / v - q - q * i);
	}
	cout << '\n';
	for (int i = 1;i <= n + m;i++){
		pair<int,int> x = max({make_pair(hp[0].empty()?-INF:hp[0].front(),0),
							   make_pair(hp[1].empty()?-INF:hp[1].front(),1),
							   make_pair(hp[2].empty()?-INF:hp[2].front(),2)});
		hp[x.second].pop();
		ll len = x.first + q * m;
		if (i % t == 0)	printf("%d ",len);
	}
	return 0;
}