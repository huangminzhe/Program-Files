#ifndef __INT128_HPP
#define __INT128_HPP

#include <iostream>
using namespace std;
typedef __int128 lll;
ostream& operator<<(ostream& out,lll b){
	if (b < 0){
		out << '-';
		out << -b;
		return out;
	}
	if (b == 0){
		out << '0';
		return out;
	}
	if (b >= 10)
		out << b / 10;
	out << "0123456789"[b % 10];
	return out;
}
istream& operator>>(istream& in,lll x){
	char c;
	do{
		c = in.get();
	}while (c != '-' && !isdigit(c));	// isdigit检测字符c是否为数字
	if (c == '-'){
		c = in.get();
		x = '0' - c;
		while (isdigit(c = getchar())){
			x *= 10;
			x += '0' - c;
		}
	}else{
		x = c - '0';
		while (isdigit(c = in.get())){
			x *= 10;
			x -= '0' - c;
		}
	}
	return in;
}

#endif