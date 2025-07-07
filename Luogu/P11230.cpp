#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N = 1e5 + 5,INF = 1e9;
int n,k,len[N];
bool dp[105][N * 2];
vector<int> a[N],f[N];
vector<int> f2[N];
queue<pii> st,ed;
void init(){
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= len[i];j++){
			if (a[i][j])	f2[i][j] = 1;
		}
	}
}
void bfs(){
	for (int t = 1;t <= 100;t++){
		for (int i = 1;i <= n;i++){
			int fl = -INF;
			for (int j = 1;j <= len[i];j++){
				f[i][j] = -1;
				if (j - fl < k){	// j-fl+1<=k，检测长度是否<=k
					ed.push({i,j});
					dp[t][a[i][j]] = 1;
				}
				if (f2[i][j])	fl = j,f2[i][j] = 0;	// 细节更新起点放后面，使长度>=2
			}
		}
		while (!ed.empty()){
			int i = ed.front().first,j = ed.front().second;
			ed.pop();
			if (f[i][j] == -1)	f[i][j] = i;
			else if (f[i][j] != i)	f[i][j] = 0;
		}

		for (int i = 1;i <= n;i++){
			for (int j = 1;j <= len[i];j++){
				if (~f[i][j] && f[i][j] != i)	// ~f[i][j] == (f[i][j]!=-1)
					st.push({i,j});
			}
		}
		while (!st.empty()){
			f2[st.front().first][st.front().second] = 1;
			st.pop();
		}
	}
}
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		int q;
		cin >> n >> k >> q;
		for (int i = 1;i <= n;i++){
			cin >> len[i];
			a[i] = vector<int>(len[i] + 1);
			f[i] = vector<int>(len[i] + 1);
			f2[i] = vector<int>(len[i] + 1);
			for (int j = 1;j <= len[i];j++){
				cin >> a[i][j];
			}
		}
		init();
		bfs();
		while (q--){
			int r,c;
			cin >> r >> c;
			cout << dp[r][c] << '\n';
		}
	}
	return 0;
}