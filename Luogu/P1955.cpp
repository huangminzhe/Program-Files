#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
struct op{
	int x,y;
	bool z;
}a[N];
unordered_map<int,int> h;
int fa[N * 2],tot;
bool cmp(op b,op c){
	return b.z > c.z;
}
int find(int x){
	if (fa[x] == x)	return x;
	return fa[x] = find(fa[x]);
}
void merge(int x,int y){
	fa[find(y)] = find(x);
}
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		h.clear();
		tot = 0;
		int n;
		cin >> n;
		bool f = 0;
		for (int i = 1;i <= n * 2;i++)	fa[i] = i;
		for (int i = 1;i <= n;i++){
			int x,y;
			cin >> x >> y >> a[i].z;
			if (h.find(x) == h.end())	h.insert({x,++tot});
			if (h.find(y) == h.end())	h.insert({y,++tot});
			a[i].x = h[x],a[i].y = h[y];
		}
		sort(a + 1,a + n + 1,cmp);
		for (int i = 1;i <= n;i++){
			if (a[i].z)
				merge(a[i].x,a[i].y);
			else if (find(a[i].x) == find(a[i].y)){
				f = 1;
			}
		}
		if (f)	cout << "NO\n";
		else	cout << "YES\n";
	}
	return 0;
}