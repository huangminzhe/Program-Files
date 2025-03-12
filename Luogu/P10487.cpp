#include <bits/stdc++.h>
using namespace std;
const int N = 8e2 + 5;
struct node{
	int x,y;
};
int n,m;
char a[N][N];
int bx,by,gx,gy;
void bfs(node b,node g){
	queue<node> qb,qg;
	qb.push(b);
	qg.push(g);
	while (!qb.empty() && !qg.empty()){
	}
}
int main(int argc, char **argv){
	int t;
	cin >> t;
	while (t--){
		cin >> n >> m;
		for (int i = 1;i <= n;i++){
			string s;
			cin >> s;
			for (int j = 1;j <= m;j++){
				int si = j - 1;
				a[i][j] = s[si];
				if (a[i][j] == 'M'){
					bx = i;
					by = j;
				}
				if (a[i][j] == 'G'){
					gx = i;
					gy = j;
				}
			}
		}
		bfs({bx,by},{gx,gy});
	}
	return 0;
}