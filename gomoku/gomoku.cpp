#include <bits/stdc++.h>
using namespace std;

typedef signed char int8;
const int8 BOARD_SIZE = 15;
class Gomoku{
	private:
		int8 board[BOARD_SIZE][BOARD_SIZE];
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
};

int main(int argc, char **argv){
	
	return 0;
}