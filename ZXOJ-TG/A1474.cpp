#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int n,m;
bool a[N][N];
int d[N][N],dx[] = {-1,1,0,0},dy[] = {0,0,-1,1};
queue<pair<int,int>> q;
void bfs(){
	while (!q.empty()){
		int x = q.front().first,y = q.front().second;
		q.pop();
		for (int i = 0;i < 4;i++){
			int xi = x + dx[i],yi = y + dy[i];
			if (xi >= 1 && xi <= n && yi >= 1 && yi <= m && d[xi][yi] > d[x][y] + 1){
				d[xi][yi] = d[x][y] + 1;
				q.push({xi,yi});
			}
		}
	}
}
int main(int argc, char **argv){
	memset(d,0x3f,sizeof d);
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		string s;
		cin >> s;
		for (int j = 1;j <= m;j++){
			a[i][j] = s[j - 1] - '0';
			if (a[i][j]){
				q.push({i,j});
				d[i][j] = 0;
			}
		}
	}
	bfs();
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= m;j++){
			cout << d[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}