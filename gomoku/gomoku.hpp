#ifndef GOMOKU_HPP
#define GOMOKU_HPP

#include <bits/stdc++.h>
typedef signed char int8;
typedef short int16;

class Gomoku{
	private:
		static const int8 BOARD_SIZE = 16;
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
		static const int LIVE1 = 10;		// 活1
		static const int ONE1  = 1;			// 1
		int8 dx[4],dy[4];	// 方向数组

		/**
		 *  @return 是否超出边界
		 */
		bool check_edge(int x,int y){
			return x < 1 || x > BOARD_SIZE || y < 1 || y > BOARD_SIZE;
		}
		/**
		 *  @return (x,y) 的棋子是否和 (xi,yi) 的棋子颜色相同
		 */
		bool check_piece(int x,int y,int xi,int yi){
			return board[xi][yi] && board[xi][yi] == board[x][y];
		}

		int evadir(int8 x,int8 y,int8 dir,int8 d,bool live){
			if (d == 5)	return LIVE5;
			int8 xi = x + dx[dir],yi = y + dy[dir];
			if (check_edge(xi,yi) || !check_piece(x,y,xi,yi)){	// 堵住了
				if (live){
					if (d == 1)	return ONE1;
					if (d == 2)	return ONE2;
					if (d == 3)	return ONE3;
					if (d == 4)	return ONE4;
				}
				return 0;
			}
			if (board[xi][yi] == 0){	// 空了
				if (live){
					if (d == 1)	return LIVE1;
					if (d == 2)	return LIVE2;
					if (d == 3)	return LIVE3;
					if (d == 4)	return LIVE4;
				}else{
					if (d == 1)	return ONE1;
					if (d == 2)	return ONE2;
					if (d == 3)	return ONE3;
					if (d == 4)	return ONE4;
				}
			}
			return evadir(xi,yi,dir,d + 1,live);
		}
	public:
		Gomoku(bool aicolor){
			this->aicolor = aicolor;

			// 0：横向；1：左上-右下；2：竖向；3：右上-左下
			dx[0] = 0,dx[1] = dx[2] = dx[3] = 1;
			dy[0] = dy[1] = 1,dy[2] = 0,dy[3] = -1;

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
			bool f[BOARD_SIZE][BOARD_SIZE];
			memset(f,0,sizeof f);
			int score = 0;
			
			for (int8 i = 1;i <= BOARD_SIZE;i++){
				for (int8 j = 1;j <= BOARD_SIZE;j++){
					if (board[i][j] && !f[i][j]){
						f[i][j] = 1;
						for (int8 I = 0;I < 4;I++){
							int8 xi = i - dx[I],yi = j - dy[I];
							bool live = !check_edge(xi,yi) || board[xi][yi] == 0;	// 注：不可能等于上一个，因为已经被标记了
							score += board[i][j] == aicolor?evadir(i,j,I,1,live):-evadir(i,j,I,1,live);
						}
					}
				}
			}
			return score;
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

#endif