#include <bits/stdc++.h>
using namespace std;
const int N = 2.5e3 + 5;
int mi[N];
int main(int argc, char **argv){
	for (int i = 1;i <= 2.5e3;i++)	mi[i] = i * i;
	int n,m;
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		int a,b,c;
		cin >> a >> b >> c;
		int delta = b * b - 4 * a * c;
		if (delta < 0)	cout << "NO\n";
		else{	// 有解
			int fenmu = 2 * a;
			double fenzi = -b + (a > 0?__builtin_sqrt(delta):-__builtin_sqrt(delta)),jie = fenzi / fenmu;
			if (int(jie) == jie)	cout << int(jie) << '\n';
			else{	// 非整数解
				if ((int)__builtin_sqrt(delta) == __builtin_sqrt(delta)){	// 小（分）数解
					if (a < 0)	fenzi = -fenzi,fenmu = -fenmu;
					int gcd = abs(__gcd(int(fenzi),fenmu));
					// printf(" %d %d %d\n",(int)fenzi,fenmu,gcd);
					cout << fenzi / gcd << '/' << fenmu / gcd << '\n';
				}else{	// 无理数解
					bool ylsfl = 0;
					if (b){	// 有有理数部分
						ylsfl = 1;
						if (1.0 * -b / (2 * a) == int(-b / (2 * a)))	cout << -b / (2 * a);
						else{
							int gcd = abs(__gcd(b,2 * a));
							int a_ = a < 0?-a:a,b_ = a < 0?-b:b;
							cout << -b_ / gcd << '/' << 2 * a_ / gcd;
						}
					}
					int zheng = 0;
					for (int i = __builtin_sqrt(delta);i > 0;i--)
						if (delta % mi[i] == 0){
							zheng = i;
							delta /= mi[i];
							break;
						}
					if (a < 0)	a = -a;
					int gcd = abs(__gcd(zheng,2 * a));
					if (ylsfl && zheng > 0)	cout << '+';
					if (zheng / gcd == -1)	cout << '-';
					else if (zheng / gcd != 1)	cout << zheng / gcd << '*';
					cout << "sqrt(" << delta << ')';
					if (2 * a != gcd)	cout << '/' << 2 * a / gcd;
					cout << '\n';
				}
			}
		}
	}
	return 0;
}