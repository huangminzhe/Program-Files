#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 15;
int n,m;
bool a[N][N];
set<vector<vector<bool>>> s;
int main(int argc, char **argv){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			char c;
			cin >> c;
			a[i][j] = c == '#';
		}
	}
	for (int i = 1;i <= n - m + 1;i++){
		for (int j = 1;j <= n - m + 1;j++){
			vector<vector<bool>> t(m,vector<bool>(m));
			for (int k = 0;k < m;k++){
				for (int h = 0;h < m;h++){
					t[k][h] = a[i + k][j + h];
				}
			}
			s.insert(t);
		}
	}
	cout << s.size();
	return 0;
}