#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N = 1e5 + 5;
int n,m,sx,sy,tot;
int dx[] = {-1,1,0,0},dy[] = {0,0,-1,1};
set<pii> blks,pts;	// 障碍物；关键点
set<int> blkx[N],blky[N];	// x=i的障碍物；y=i的障碍物
map<pii,int> id;	// 关键点编号
vector<int> g[N * 4];

int main(int argc, char **argv){
	cin >> n >> m >> sx >> sy;
	for (int i = 1;i <= n;i++){
		int x,y;
		cin >> x >> y;
		blks.insert({x,y});
		blkx[x].insert(y);
		blky[y].insert(x);
	}
	pts.insert({sx,sy});
	for (auto [x,y] : blks){
	// for (auto i : blks){
	// 	int x = i.first,y = i.second;
		for (int i = 0;i < 4;i++){
			int xi = x + dx[i],yi = y + dy[i];
			if (blks.find({xi,yi}) == blks.end())	pts.insert({xi,yi});
		}
	}
	for (auto i : pts){
		int x = i.first,y = i.second;
		id[i] = ++tot;
		for (int I = 0;I < 4;I++){
			int xi = x + dx[I],yi = y + dy[I];
			if (blks.find({xi,yi}) == blks.end()){
			}
		}
	}
	return 0;
}