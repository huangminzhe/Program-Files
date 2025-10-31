#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N = 1e5 + 5;
int n,m,sx,sy,tot;
int dx[] = {-1,1,0,0},dy[] = {0,0,-1,1};
set<pii> blks,pts;	// 障碍物；关键点
set<int> blkx[N],blky[N];	// x=i的障碍物；y=i的障碍物
map<pii,int> id;	// 关键点编号
vector<int> g[N * 4],e;	// 图；终点

pii find_up(pii p){
	int x = p.first,y = p.second;
	auto it = lower_bound(blky[y].begin(),blky[y].end(),x);
	if (it == blky[y].begin() || *(--it) == x)	return p;
	it--;
	return {*it + 1,y};
}
pii find_down(pii p){
	int x = p.first,y = p.second;
	auto it = upper_bound(blky[y].begin(),blky[y].end(),x);
	if (it == blky[y].end())	return p;
	it++;
	return {*it - 1,y};
}
pii find_left(pii p){
	int x = p.first,y = p.second;
	auto it = lower_bound(blkx[x].begin(),blkx[x].end(),y);
	if (it == blkx[x].begin() || *(--it) == y)	return p;
	it--;
	return {x,*it + 1};
}
pii find_right(pii p){
	int x = p.first,y = p.second;
	auto it = upper_bound(blkx[x].begin(),blkx[x].end(),y);
	if (it == blkx[x].end())	return p;
	it++;
	return {x,*it - 1};
}
pii (*fdnxt[])(pii) = {find_up,find_down,find_left,find_right};

int main(int argc, char **argv){
	cin >> n >> m >> sx >> sy;
	// 输入，存障碍物
	for (int i = 1;i <= n;i++){
		int x,y;
		cin >> x >> y;
		blks.insert({x,y});
		blkx[x].insert(y);
		blky[y].insert(x);
	}
	// 根据障碍物存关键点
	pts.insert({sx,sy});
	for (auto [x,y] : blks){
	// for (auto i : blks){
	// 	int x = i.first,y = i.second;
		for (int i = 0;i < 4;i++){
			int xi = x + dx[i],yi = y + dy[i];
			if (blks.find({xi,yi}) == blks.end())	pts.insert({xi,yi});
		}
	}
	for (int i = 1;i <= m;i++){
		int x,y;
		cin >> x >> y;
		e.push_back({x,y});
	}
	// 给关键点编号
	for (auto i : pts){
		id[i] = ++tot;
	}
	// 建图
	for (auto i : blks){
		int x = i.first,y = i.second;
		for (int I = 0;I < 4;I++){
			int xi = x + dx[I],yi = y + dy[I];
			pii nxt = fdnxt[I]({xi,yi});
			if (nxt != make_pair(xi,yi)){
				g[id[i]].push_back(id[nxt]);
			}
		}
	}
	return 0;
}