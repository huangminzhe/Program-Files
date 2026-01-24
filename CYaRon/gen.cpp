#include <bits/c++0x_warning.h>
#include <bits/stdc++.h>
#include <windows.h>
#include <random>
using namespace std;
random_device seed;
mt19937_64 gen(seed());
int rdint(int l,int r){
	uniform_int_distribution<int> rd(l,r);
	return rd(gen);
}
double rddouble(double l,double r){
	uniform_real_distribution<> rd(l,r);
	return rd(gen);
}

int main(int argc, char **argv){
	system("g++ std.cpp -o std");
	for (int id = 1;id <= 10;id++){
		string inp = "./data/pack" + to_string(id) + ".in",out = "./data/pack" + to_string(id) + ".out";
		freopen(inp.c_str(),"w",stdout);

		int n = rdint(2,3);
		printf("%d\n",n);
		for (int i = 1;i <= n;i++){
			printf("%d %d\n",rdint(1,5),rdint(1,6));
		}
		int m = rdint(3,4);
		printf("%d\n",m);
		for (int i = 1;i <= m;i++){
			printf("%d %d %d %d\n",rdint(1,3),rdint(1,100000000),rdint(1,4),rdint(1,4));
		}

		fclose(stdout);
		system(("std.exe < " + inp + " > " + out).c_str());
	}
	for (int id = 11;id <= 20;id++){
		string inp = "./data/pack" + to_string(id) + ".in",out = "./data/pack" + to_string(id) + ".out";
		freopen(inp.c_str(),"w",stdout);

		int n = rdint(3,4);
		printf("%d\n",n);
		for (int i = 1;i <= n;i++){
			printf("%d %d\n",rdint(1,5),rdint(1,9));
		}
		int m = 4;
		printf("%d\n",m);
		for (int i = 1;i <= m;i++){
			printf("%d %d %d %d\n",rdint(1,3),rdint(1,100000000),rdint(1,4),rdint(1,4));
		}

		fclose(stdout);
		system(("std.exe < " + inp + " > " + out).c_str());
	}
	return 0;
}
/*
C++ <random> 库中的一些常见分布包括：
std::uniform_int_distribution：产生一个给定范围内的均匀整数分布。
std::uniform_real_distribution：产生一个给定范围内的均匀实数分布。
std::normal_distribution：产生一个正态分布的随机数。
std::exponential_distribution：产生一个指数分布的随机数。
*/