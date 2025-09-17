#include <bits/stdc++.h>
#include "CDE7.h"
using namespace std;

typedef signed char int8;
typedef short int16;
class Gomoku{
	private:
		static const int8 BOARD_SIZE = 15;
		static const int INF = INT_MAX;
		int8 board[BOARD_SIZE][BOARD_SIZE];
		bool aicolor;	// 0为黑，1为白
		static const int LIVE5 = 100000;	// 活5
		static const int LIVE4 = 10000;		// 活4
		static const int ONE4  = 1000;		// 4
		static const int LIVE3 = 1000;		// 活3
		static const int ONE3  = 100;		// 3
		static const int LIVE2 = 100;		// 活2
		static const int ONE2  = 10;		// 2

		/**
		 *  @return 是否超出边界
		 */
		bool check_edge(int x,int y){
			if (x < 1 || x > BOARD_SIZE || 
				y < 1 || y > BOARD_SIZE)	return 1;
			return 0;
		}

		int evadir(int8 dir,int8 d,bool live){
			if (d == 5)	return LIVE5;
			if (d == 4){

			}
		}
	public:
		Gomoku(){
			for (int8 i = 1;i <= BOARD_SIZE;i++){
				for (int8 j = 1;j <= BOARD_SIZE;j++){
					board[i][j] = 0;
				}
			}
		}

		bool place(int8 x,int8 y,int8 p){
			if (check_edge(x,y) || board[x][y] != 0)
				return 0;
			board[x][y] = p;
			return 1;
		}
		// 检查胜负
		int8 check(){
			// 横向
			for (int8 i = 1;i <= BOARD_SIZE;i++){
				for (int8 j = 1;j <= BOARD_SIZE - 4;j++){
					int8 p = board[i][j] & board[i][j + 1] & board[i][j + 2] & board[i][j + 3] & board[i][j + 4];
					if (p)
						return p;
				}
			}
			// 竖向
			for (int8 i = 1;i <= BOARD_SIZE - 4;i++){
				for (int8 j = 1;j <= BOARD_SIZE;j++){
					int8 p = board[i][j] & board[i + 1][j] & board[i + 2][j] & board[i + 3][j] & board[i + 4][j];
					if (p)
						return p;
				}
			}
			// 左上-右下
			for (int8 i = 1;i <= BOARD_SIZE - 4;i++){
				for (int8 j = 1;j <= BOARD_SIZE - 4;j++){
					int8 p = board[i][j] & board[i + 1][j + 1] & board[i + 2][j + 2] & board[i + 3][j + 3] & board[i + 4][j + 4];
					if (p)
						return p;
				}
			}
			// 右上-左下
			for (int8 i = 1;i <= BOARD_SIZE - 4;i++){
				for (int8 j = 4;j <= BOARD_SIZE;j++){
					int8 p = board[i][j] & board[i + 1][j - 1] & board[i + 2][j - 2] & board[i + 3][j - 3] & board[i + 4][j - 4];
					if (p)
						return p;
				}
			}
			return 0;
		}

		int evaall(){
			// 0：横向；1：左上-右下；2：竖向；3：右上-左下
			int8 dx[] = {0,1,1,1},dy[] = {1,1,0,-1};
			bool f[BOARD_SIZE][BOARD_SIZE];
			memset(f,0,sizeof f);
			
			for (int8 i = 1;i <= BOARD_SIZE;i++){
				for (int8 j = 1;j <= BOARD_SIZE;j++){
					if (board[i][j] && !f[i][j]){
						for (int8 I = 0;I < 4;I++){
							int8 xi = i + dx[I],yi = j + dy[I],
								 xj = i - dx[I],yj = j - dy[I];
							if (check_edge(xi,yi))	continue;
							if (board[xj][yj] && board[xj][yj] != board[i][j] || 
								check_edge(xj,yj))	evadir(I,2,0);
							else
								evadir(I,2,1);
						}
					}
				}
			}
		}
		/**
		 *  @param d 深度
		 *  @param isAI 是否到AI落子
		 *  @param alpha AI当前能获得的最大分数
		 *  @param beta AI当前能获得的最小分数
		 *  
		 *  预判函数，AI会选择对自己最有利的下法，玩家会选择对AI最不利的下法
		 *  alpha：玩家选择时，若返回值小于等于该值，则剪枝（AI不会选择这个分支）
		 *  beta：AI选择时，若返回值大于等于该值，则剪枝（玩家不会选择这个分支）
		 */
		int astar(int8 d,bool isAI,int alpha,int beta){
			if (d == 0 || check()){
				return evaall();
			}
			if (isAI){	// 到AI下，则选择对自己最有利的下法
				int mx = -INF;
				for (int8 i = 1;i <= BOARD_SIZE;i++){
					for (int8 j = 1;j <= BOARD_SIZE;j++){
						if (board[i][j])	continue;
						board[i][j] = 2;
						mx = max(mx,astar(d - 1,0,alpha,beta));
						board[i][j] = 0;

						alpha = max(alpha,mx);
						if (alpha >= beta)
							break;
					}
				}
				return mx;
			}else{	// 到玩家下，则选择对AI最不利的下法
				int mn = INF;
				for (int8 i = 1;i <= BOARD_SIZE;i++){
					for (int8 j = 1;j <= BOARD_SIZE;j++){
						if (board[i][j])	continue;
						board[i][j] = 1;
						mn = min(mn,astar(d - 1,1,alpha,beta));
						board[i][j] = 0;

						beta = min(alpha,mn);
						if (beta <= alpha)
							break;
					}
				}
				return mn;
			}
		}
};

int main(int argc, char **argv){
	
	return 0;
}