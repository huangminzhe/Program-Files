#include <bits/stdc++.h>
using namespace std;
set<string> a;
int main(int argc, char **argv){
	a.insert("123");
	a.insert("456");
	a.insert("56+");
	a.insert("789");
	a.insert("89+");
	a.insert("/*-");
	a.insert("741");
	a.insert("410");
	a.insert("/85");
	a.insert("852");
	a.insert("520");
	a.insert("*96");
	a.insert("963");
	a.insert("63.");
	string s;
	cin >> s;
	if (a.find(s) != a.end())	cout << "Yes";
	else{
		reverse(s.begin(),s.end());
		if (a.find(s) != a.end())	cout << "Yes";
		else	cout << "No";
	}
	return 0;
}