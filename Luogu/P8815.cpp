#include <bits/stdc++.h>
using namespace std;
int op = -1,y,h;
bool x;
int main(int argc, char **argv){
	char c;
	while (cin >> c){
		if (op == -1){
			if (c == '0')	x = 0;
			else if (c == '1')	x = 1;
			else if (c == '&' && !x){
				op = 0;
				y++;
			}else if (c == '|' && x){
				op = 1;
				h++;
			}/*else if (c==&,x=1)交给后面
						c==|,x=0 交给后面
						c==()	 无用括号*/
		}else{	// 上面两种情况
			if (c == '('){
				int kuohao = 1;
				while (kuohao){
					cin >> c;
					if (c == '(')	kuohao++;
					else if (c == ')')	kuohao--;
				}
			}else if (c == ')' || c == '|' && !op)	op = -1;
			// 机器思维
			else if (c == '&' && !op)	y++;
			else if (c == '|' && op)	h++;
		}
	}
	cout << x << '\n' << y << ' ' << h;
	return 0;
}