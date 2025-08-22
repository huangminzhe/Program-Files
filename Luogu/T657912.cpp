#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
struct hb{
	string st,ed;
	int h,m;
	int hs;
	bool operator< (const hb a) const{
		return hs < a.hs;
	}
};
int n,m;
map<string,int> b;
map<hb,bool> f;
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= m;i++){
		int x;
		cin >> x;
		for (int j = 1;j <= x;j++){
			string s;
			cin >> s;
			b[s] = i;
		}
	}
	for (int i = 1;i <= n;i++){
		string s;
		cin >> s;
		hb x;
		string ha = s.substr(0,2);
		x.st = s.substr(7,3);
		x.ed = s.substr(11,3);
		x.h = stoi(s.substr(15,2));
		x.m = stoi(s.substr(18,2));
		x.hs = b[ha]?b[ha]:++m;
		f[x] = 1;
		printf("%s %s %d %d %d\n",x.st.c_str(),x.ed.c_str(),x.h,x.m,x.hs);
	}
	for (auto i : f){
		hb x = i.first;
		printf("%s %s %d %d %d\n",x.st.c_str(),x.ed.c_str(),x.h,x.m,x.hs);
	}
	cout << f.size();
	return 0;
}