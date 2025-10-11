#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int a[N][N];
vector<int> pa;
int main(int argc, char **argv){
	int n,p;
	cin >> n;
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			cin >> a[i][j];
		}
	}
	cin >> p;
	for (int i = 1;i <= p;i++){
		int x;
		cin >> x;
		pa.push_back(x);
	}

	for (int k = 1;k <= n;k++){
		for (int i = 1;i <= n;i++){
			for (int j = 1;j <= n;j++){
				
			}
		}
	}
	return 0;
}