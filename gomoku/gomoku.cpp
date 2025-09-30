#include <bits/stdc++.h>
#include "CDE7.1.h"
#include "gomoku.hpp"
using namespace std;
const int8 OPCNT = 2;

Item a[OPCNT];
void show(){
	system("cls");
	for (int8 i = 0;i < OPCNT;i++){
		a[i].show();
	}
}
void help(){
	system("cls");
	cout << "按Enter键返回\n"
			"使用“W”“S”“↑”“↓”或移动鼠标进行选择\n"
			"使用“Enter”或鼠标左键进行确认\n";
	while (!KEYDOWN(VK_RETURN));
}
void choose(int8 op){
	if (op == 0){
		help();
		show();
	}else if (op == 1){}
}
int main(int argc, char **argv){
	// a[0]：帮助
	a[0].goto_xy({0,0});
	a[0].code_load({"0.帮助"},"selected",Tool::getbRGB(255,255,255) + Tool::getRGB(0,0,0));
	a[0].code_load({"0.帮助"},"unselected",Tool::getbRGB(0,0,0) + Tool::getRGB(255,255,255));
	// a[1]：单人模式
	a[1].goto_xy({1,0});
	a[1].code_load({"1.单人模式"},"selected",Tool::getbRGB(255,255,255) + Tool::getRGB(0,0,0));
	a[1].code_load({"1.单人模式"},"unselected",Tool::getbRGB(0,0,0) + Tool::getRGB(255,255,255));

	int8 op = 1;
	a[1].group_use("selected");
	show();
	while (1){
		if (KEYDOWN(VK_UP) || KEYDOWN('W')){
			a[op].group_use("unselected");
			op = (op - 1 + OPCNT) % OPCNT;
			a[op].group_use("selected");
			Sleep(25);
		}
		if (KEYDOWN(VK_DOWN) || KEYDOWN('S')){
			a[op].group_use("unselected");
			op = (op + 1) % OPCNT;
			a[op].group_use("selected");
			Sleep(25);
		}
		if (KEYDOWN(VK_RETURN)){
			choose(op);
		}

		if (KEYDOWN('0')){
			help();
		}

		xy mxy = Tool::get_mouse_xy();
		if (mxy.x >= 0 && mxy.x <= 6 && mxy.y == 0){
			a[op].group_use("unselected");
			op = 0;
			a[op].group_use("selected");
			if (Tool::mouse_down(1,0,0)){
				help();
			}
		}

		Sleep(75);
	}
	return 0;
}