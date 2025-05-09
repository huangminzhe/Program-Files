#include <bits/stdc++.h>
using namespace std;
const int N = 205;
map<char,int> cti;
bool d[5][5][5],dp[N][N][5],f = 1;
int main(int argc, char **argv){
	cti['W'] = 1;
	cti['I'] = 2;
	cti['N'] = 3;
	cti['G'] = 4;
	int n[5];
	cin >> n[1] >> n[2] >> n[3] >> n[4];
	for (int I = 1;I <= 4;I++){
		for (int i = 1;i <= n[I];i++){
			char c1,c2;
			cin >> c1 >> c2;
			d[I][cti[c1]][cti[c2]] = 1;
		}
	}
	char s[N];
	scanf("%s",s + 1);
	int len = strlen(s + 1);
	for (int i = 1;i <= len;i++){
		dp[i][i][cti[s[i]]] = 1;
	}
	for (int k = 1;k < len;k++){
		for (int i = 1;i <= len - k;i++){
			int j = i + k;
			for (int h = i;h < j;h++){
				for (int z = 1;z <= 4;z++){	// 原来的字符
					for (int x = 1;x <= 4;x++){	// 变出来的字符1
						for (int y = 1;y <= 4;y++){	// 变出来的字符2
							if (d[z][x][y] && dp[i][h][x] && dp[h + 1][j][y]){
								dp[i][j][z] = 1;
							}
						}
					}
				}
			}
		}
	}
	if (dp[1][len][cti['W']])
		f = 0,
		cout << 'W';
	if (dp[1][len][cti['I']])
		f = 0,
		cout << 'I';
	if (dp[1][len][cti['N']])
		f = 0,
		cout << 'N';
	if (dp[1][len][cti['G']])
		f = 0,
		cout << 'G';
	if (f)
		cout << "The name is wrong!";
	return 0;
}