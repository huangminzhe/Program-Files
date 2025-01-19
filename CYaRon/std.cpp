#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int a[N],cnt;
int main(int argc, char **argv){
	int n,m;
	cin >> n >> m;
	for (int i = 1;i <= n;i++)	cin >> a[i];
	if (m == 1){
		cnt = n;
		for (int i = 1;i <= n - 3;i++){
			if (a[i] == a[i + 1] && a[i + 1] == a[i + 2] && a[i + 2] == a[i + 3])	cnt++;
		}
	}else if (m == 2){
		for (int i = 1;i < n;i++){
			if (a[i] == a[i + 1])	cnt++;
		}
	}else if (m == 3){
		for (int i = 1;i <= n - 2;i++){
			if (a[i] == a[i + 1] && a[i + 1] + 1 == a[i + 2])	cnt++;
		}
		for (int i = 1;i < n;i++){
			if (a[i] == a[i + 1] + 1)	cnt++;
		}
	}else if (m == 4){
		for (int i = 1;i <= n - 2;i++){
			if (a[i] == a[i + 1] + 1 && a[i + 1] == a[i + 2])	cnt++;
		}
		for (int i = 1;i < n;i++){
			if (a[i] + 1 == a[i + 1])	cnt++;
		}
	}else if (m == 5){
		for (int i = 1;i <= n - 2;i++){
			if (a[i] == a[i + 1] && a[i + 1] == a[i + 2])	cnt++;
			if (a[i] == a[i + 2] && a[i] == a[i + 1] + 1)	cnt++;
		} 
		for (int i = 1;i < n;i++){
			if (a[i] + 1 == a[i + 1])	cnt++;
			if (a[i] == a[i + 1] + 1)	cnt++;
		}
	}else if (m == 6){
		for (int i = 1;i <= n - 2;i++){
			if (a[i] + 1 == a[i + 1] && a[i + 1] == a[i + 2])	cnt++;
			if (a[i] == a[i + 1] && a[i + 1] == a[i + 2])	cnt++;
		}
		for (int i = 1;i < n;i++){
			if (a[i] == a[i + 1])	cnt++;
			if (a[i] == a[i + 1] + 2)	cnt++;
		} 
	}else{
		for (int i = 1;i <= n - 2;i++){
			if (a[i] == a[i + 1] && a[i + 1] == a[i + 2] + 1)	cnt++;
			if (a[i] == a[i + 1] && a[i + 1] == a[i + 2])	cnt++;
		}
		for (int i = 1;i < n;i++){
			if (a[i] == a[i + 1])	cnt++;
			if (a[i] + 2 == a[i + 1])	cnt++;
		}
	}
	cout << cnt;
	return 0;
}