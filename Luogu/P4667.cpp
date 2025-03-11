#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 5;
struct node{
	int x,y,stp;
};
int n,m;
char a[N][N];
int dx[] = {-1,1,-1,1},dy[] = {-1,1,1,-1};
char dc[] = {'\\','\\','/','/'};
int bfs(int sx,int sy,int sstp){
	deque<node>	q;
	q.push_back({sx,sy,sstp});
	while (!q.empty()){
		int x = q.front().x,y = q.front().y,stp = q.front().stp;
		q.pop_front();
		if (x == n && y == m)
			return stp;
		for (int i = 0;i < 4;i++){}
	}
}
int main(int argc, char **argv){
	cin >> n >> m;
	if ((n + m) & 1){
		cout << "NO SOLUTION";
		return 0;
	}
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= m;j++){
			cin >> a[i][j];
		}
	}
	cout << bfs(0,0,0);
	return 0;
}