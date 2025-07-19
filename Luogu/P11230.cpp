#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N = 1e5 + 5,INF = 1e9;
int n,k,len[N];
bool dp[105][N * 2];
vector<int> a[N],f;
vector<bool> f2[N];
vector<pii> st,ed;
void bfs(){
	f = vector<int>(N * 2,-1);
	f[1] = 0;
	for (int t = 1;t <= 100;t++){
		// printf("%d:\n",t);
		st.clear();
		for (int i = 1;i <= n;i++){
			for (int j = 1;j <= len[i];j++){
				if (~f[a[i][j]] && f[a[i][j]] != i)	// ~f[a[i][j]] == (f[a[i][j]]!=-1)
					st.emplace_back(i,j);
			}
		}
		for (pii i : st)	f2[i.first][i.second] = 1;
		ed.clear();
		for (int i = 1;i <= n;i++){
			int fl = -INF;
			for (int j = 1;j <= len[i];j++){
				if (j - fl < k){	// j-fl+1<=k，检测长度是否<=k
					ed.emplace_back(i,j);
					dp[t][a[i][j]] = 1;
				}
				if (f2[i][j])	fl = j,f2[i][j] = 0;	// 细节更新起点放后面，使长度>=2
				// printf("  %d %d",dp[t][a[i][j]],a[i][j]);
			}
			// printf("\n");
		}
		f = vector<int>(N * 2,-1);
		for (pii x : ed){
			int i = x.first,j = a[i][x.second];
			if (f[j] == -1)	f[j] = i;
			else if (f[j] != i)	f[j] = 0;
		}
	}
}
int main(int argc, char **argv){
	ios::sync_with_stdio(0),cin.tie(0);
	int t;
	cin >> t;
	while (t--){
		memset(dp,0,sizeof dp);
		int q;
		cin >> n >> k >> q;
		for (int i = 1;i <= n;i++){
			cin >> len[i];
			a[i] = vector<int>(len[i] + 1,0);
			f2[i] = vector<bool>(len[i] + 1,0);
			for (int j = 1;j <= len[i];j++){
				cin >> a[i][j];
			}
		}
		bfs();
		while (q--){
			int r,c;
			cin >> r >> c;
			cout << dp[r][c] << '\n';
		}
	}
	return 0;
}