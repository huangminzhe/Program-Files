#include <bits/stdc++.h>
using namespace std;

typedef signed char int8;
typedef short int16;
class Gomoku{
	private:
		static const int8 BOARD_SIZE = 15;
		static const int INF = INT_MAX;
		int8 board[BOARD_SIZE][BOARD_SIZE];
		static const int LIVE5 = 100000;	// 活5
		static const int LIVE4 = 10000;		// 活4
		static const int ONE4  = 1000;		// 4
		static const int LIVE3 = 1000;		// 活3
		static const int ONE3  = 100;		// 3
		static const int LIVE2 = 100;		// 活2
		static const int ONE2  = 10;		// 2
	public:
		Gomoku(){
			for (int8 i = 1;i <= BOARD_SIZE;i++){
				for (int8 j = 1;j <= BOARD_SIZE;j++){
					board[i][j] = 0;
				}
			}
		}

		bool place(int8 x,int8 y,int8 p){
			if (x < 1 || x > BOARD_SIZE || 
				y < 1 || y > BOARD_SIZE || 
				board[x][y] != 0)
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

		int evaall(){}
		/**
		 * @param d 深度
		 * @param isAI 是否到AI落子
		 * @param alpha AI最少能获得的分数
		 * @param beta 玩家最多能获得的分数
		 */
		int astar(int d,bool isAI,int alpha,int beta){
			if (d == 0 || check()){
				return evaall();
			}
			if (isAI){
				int mx = -INF;
				for (int i = 1;i <= BOARD_SIZE;i++){
					for (int j = 1;j <= BOARD_SIZE;j++){
						if (board[i][j])	continue;
						board[i][j] = 1 + isAI;
						mx = max(mx,astar(d - 1,0,alpha,beta));
						board[i][j] = 0;

						alpha = max(alpha,mx);

					}
				}
			}
		}
};

int main(int argc, char **argv){
	
	return 0;
}