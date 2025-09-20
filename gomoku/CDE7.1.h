/*
CDE7.1版本 

*/
#ifndef CDEx_H
#define CDEx_H
#include<bits/stdc++.h>
#include<windows.h>
#define KEYDOWN(name) (((GetAsyncKeyState(name)&0x8000)?1:0) && now_window==GetForegroundWindow())
using namespace std;
HWND now_window=GetForegroundWindow();//当前窗口
bool init_flag=0;
struct xy
{
	int x,y;
	bool operator == (const xy nxt)const
	{
		return x==nxt.x && y==nxt.y;
	}
	bool operator != (const xy nxt)const
	{
		return x!=nxt.x || y!=nxt.y;
	}
	xy operator + (const xy nxt)const
	{
		return {x+nxt.x,y+nxt.y};
	}
	xy operator - (const xy nxt)const
	{
		return {x-nxt.x,y-nxt.y};
	}
	int to_quadrant(xy p)
	{
		if(p.x<=x && p.y>y)return 1;
		if(p.x<x && p.y<=y)return 2;
		if(p.x>=x && p.y<y)return 3;
		if(p.x>x && p.y>=y)return 4;
		return 0;
	}
	char out(string s=",")
	{
		cout<<x<<s<<y;
		return '\0';
	}
};
xy EDGE={30,120};
struct picture
{
	int l,h;
	vector<string>g;
};
xy py_xy={0,0};
void tset(xy p)
{
	py_xy=p;
}
xy tget()
{
	return py_xy;
}
xy tcde(xy p)
{
	return p+py_xy;
}
xy tdef(xy p)
{
	return p-py_xy;
}
namespace Tool
{
	void init_screen()
	{
		if(!init_flag)
		{
			CONSOLE_CURSOR_INFO cciCursor;
			HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
			if(GetConsoleCursorInfo(hStdOut,&cciCursor))
			{
				cciCursor.bVisible=FALSE;
				SetConsoleCursorInfo(hStdOut,&cciCursor);
			}
			HANDLE hStdin=GetStdHandle(STD_INPUT_HANDLE);
			DWORD mode;
			GetConsoleMode(hStdin,&mode);
			mode&=~ENABLE_QUICK_EDIT_MODE;
			SetConsoleMode(hStdin,mode);
			system("color 07");
			init_flag=1;
		}
	}
	void sleep(int ms)
	{
		Sleep(ms);
	}
	bool mouse_down(int left,int mid,int right)//是否按下鼠标 
	{
		bool flag=1;
		if(left)
			flag=flag && KEYDOWN(VK_LBUTTON);
		if(mid)
			flag=flag && KEYDOWN(VK_MBUTTON);
		if(right)
			flag=flag && KEYDOWN(VK_RBUTTON);
		return flag;
	}
	xy mousexy()//获取鼠标字符位置 
	{
		init_screen();
		HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
		if(hOutput==INVALID_HANDLE_VALUE)
			return {0,0};
		CONSOLE_FONT_INFO ft_size;
		if(!GetCurrentConsoleFont(hOutput,FALSE,&ft_size))
			return {0,0};
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(GetForegroundWindow(),&p);
		return {p.y/ft_size.dwFontSize.Y,p.x/ft_size.dwFontSize.X};
	}
	string getRGB(int r,int g,int b)
	{
		return "[38;2;"+to_string(r)+";"+to_string(g)+";"+to_string(b)+"m";
	}
	string getbRGB(int r,int g,int b)
	{
		return "[48;2;"+to_string(r)+";"+to_string(g)+";"+to_string(b)+"m";
	}
	string get033RGB(string x)
	{
		return "["+x+"m";
	}
	string getNONERGB()
	{
		return "\033[0m";
	}
	string getstrRGB(string s)
	{
		if(s.size()<9)return s;
		if(s[0]=='R' && s[1]=='G' && s[2]=='B' && s[3]=='_')
		{
			int i=3;string r="",g="",b="";
			for(i++;i<s.size();i++)
				if(s[i]=='_')break;else r+=s[i];
			for(i++;i<s.size();i++)
				if(s[i]=='_')break;else g+=s[i];
			for(i++;i<s.size();i++)
				b+=s[i];
			return getRGB(stoi(r),stoi(g),stoi(b));
		}
		if(s[0]=='b' && s[1]=='R' && s[2]=='G' && s[3]=='B' && s[4]=='_')
		{
			int i=4;string r="",g="",b="";
			for(i++;i<s.size();i++)
				if(s[i]=='_')break;else r+=s[i];
			for(i++;i<s.size();i++)
				if(s[i]=='_')break;else g+=s[i];
			for(i++;i<s.size();i++)
				b+=s[i];
			return getbRGB(stoi(r),stoi(g),stoi(b));
		}
		if(s[0]=='\\' && s[1]=='0' && s[2]=='3' && s[3]=='3' && s[4]=='_')
		{
			int i=4;string x="";
			for(i++;i<s.size();i++)
				x+=s[i];
			return get033RGB(x);
		}
		return s;
	}
	void clear_screen_cls()
	{
		init_screen();
		system("cls");
	}
	void set_screen_size(short hei,short len)
	{
		init_screen();
		string s="mode con cols="+to_string(len)+" lines="+to_string(hei);
		system(s.c_str());
		EDGE={hei,len};
	}
	void set_screen_title(string title)
	{
		init_screen();
		string temp="title "+title;
		system(temp.c_str());
	}
	void lock_screen_size()
	{
		init_screen();
		SetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE,GetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	}
	void gotoxy(xy po)//移动字符位置 
	{
//		init_screen();
		COORD pos={(short)po.y,(short)po.x};
		HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hOut,pos);
	}
	void clear_screen_space()
	{
		for(int i=0;i<=EDGE.x;i++)
			for(int j=0;j<=EDGE.y;j++)
			{
				gotoxy({i,j});
				cout<<" ";
			}
	}
	void quit_screen()
	{
		system("pause>nul");
		exit(0);
	}
}
class Item
{
	private:
		void gotoxy(xy po)//移动字符位置 
		{
			Tool::gotoxy(po);
		}
		void init()
		{
			Tool::init_screen();
		}
		string turn(string str)
		{
			string s=str;
			for(int i=0;i<(int)s.size();i++)
			{
				if(s[i]=='`')//空格 
					s[i]=' ';
			}
			return s;
		}
		void load(string file)
		{
			ifstream fin(file);
			ng="";
			fin>>len>>hei;
			for(int i=1;i<=len;i++)
			{
				string str;fin>>str;
				ng+=str;
				str=turn(str);
				g.push_back(str);
			}
			fin.close();
		}
		string strs(string s,int times)
		{
			string str="";
			for(int i=1;i<=times;i++)
				str+=s;
			return str;
		}
	protected:
		xy pxy;
		int len,hei,hidemode,fac;
		vector<string>g;
		string color="";
		string ng;
		//克隆组 
		vector<Item>clone;
		vector<int>vis;
		bool killmode;
		//图片组 
		map<string,picture>group;
		map<string,string>group_c;
		//动画组 
		map<string,vector<string> >anime;
		map<string,int>anime_frame;
		int clone_clear_v()
		{
			for(int i=vis.size()-1;i>=0;i--)
				if(!vis[i])clone.pop_back(),vis.pop_back();
				else break;
			return vis.size();
		}
		Item jc_item()
		{
			Item p(pxy,1);
			p.code_load(len,hei,ng);
			if(hidemode)p.hide();
			else p.show();
			p.fac=fac;
			p.color=color;
			p.group=group;
			p.group_c=group_c;
			p.T_int=T_int;
			p.T_double=T_double;
			p.T_string=T_string;
			p.Tmap_int=Tmap_int;
			p.Tmap_double=Tmap_double;
			p.Tmap_string=Tmap_string;
			return p;
		}
		#define PI 3.14159265369
		double sin_(double x)
		{
			return sin(x*PI/180);
		}
		double cos_(double x)
		{
			return cos(x*PI/180);
		}
		double tan_(double x)
		{
			return tan(x*PI/180);
		}
		double asin_(double x)
		{
			return asin(x)*180/PI;
		}
		double acos_(double x)
		{
			return acos(x)*180/PI;
		}
		double atan_(double x)
		{
			return atan(x)*180/PI;
		}
		#undef PI
	public:
		//本体变量组 
		vector<int>T_int;
		vector<double>T_double;
		vector<string>T_string;
		map<string,int>Tmap_int;
		map<string,double>Tmap_double;
		map<string,string>Tmap_string;
		//初始化组 
		Item(xy p,int hide=0)
		{
			pxy=p;
			hidemode=hide;
			killmode=0;
			fac=0;
			init();
		}
		Item(xy p,vector<string>str,int hide=0)
		{
			pxy=p;
			hidemode=hide;
			killmode=0;
			fac=0;
			init();
			code_load(str);
		}
		Item()
		{
			pxy={0,0};
			hidemode=0;
			killmode=0;
			fac=0;
			init();
			code_load({""});
		}
		//获取组 
		xy get_xy()
		{
			return pxy;
		}
		int get_len()
		{
			return len;
		}
		int get_hei()
		{
			return hei;
		}
		int get_hidemode()
		{
			return hidemode;
		}
		int get_facing()
		{
			return fac;
		}
		vector<string> get_g()
		{
			return g;
		}
		string get_gline(int line)
		{
			return g[line-1];
		}
		xy get_mousexy()
		{
			return Tool::mousexy();
		}
		bool get_killmode()
		{
			return killmode;
		}
		map<string,picture> get_group()
		{
			return group;
		}
		picture get_groupline(string name)
		{
			return group[name];
		}
		vector<Item> get_clone()
		{
			vector<Item>v;
			for(int i=0;i<(int)clone.size();i++)
				if(vis[i])
					v.push_back(clone[i]);
			return v;
		}
		xy get_center()//获取图片的中心位置 
		{
			xy acenter={len/2,hei/2};
			return pxy+acenter;
		}
		double get_to_facing(xy p)
		{
			int F=pxy.to_quadrant(p);
			int xs=abs(pxy.x-p.x);
			int ys=abs(pxy.y-p.y);
			if(F==1) return atan_(1.0*ys/xs);
			if(F==4) return 90+atan_(1.0*xs/ys);
			if(F==3) return 180+atan_(1.0*ys/xs);
			if(F==2) return 270+atan_(1.0*xs/ys);
			return 0;
		}
		xy get_len_xy(double len,double block_mode=2)
		{
			bool flag=0;
			if(len<0)
				flag=1,len=-len,left(180);
			block_mode=abs(block_mode);
			int nx=pxy.x,ny=pxy.y;
			int nf=fac%90;
			if(fac>=0 && fac<90)
				nx-=round(cos_(nf)*len),ny+=round(block_mode*sin_(nf)*len);
			if(fac>=90 && fac<180)
				nx+=round(sin_(nf)*len),ny+=round(block_mode*cos_(nf)*len);
			if(fac>=180 && fac<270)
				nx+=round(cos_(nf)*len),ny-=round(block_mode*sin_(nf)*len);
			if(fac>=270 && fac<360)
				nx-=round(sin_(nf)*len),ny-=round(block_mode*cos_(nf)*len);
			if(flag)
				left(180);
			return xy{nx,ny};
		}
		double get_to_facing(Item p,bool facing_center=1)
		{
			if(facing_center)
				return get_to_facing(p.get_center());
			return get_to_facing(p.get_xy());
		}
		//导入组 
		void file_load(string file,string s="")
		{
			clear();
			file+=".cditem";
			g.clear();
			load(file);
			draw();
			if(s!="")
				group_load(s);
		}
		void code_load(int l,int h,string str,string s="")
		{
			clear();
			g.clear();
			len=l,hei=h;
			ng="";
			for(int i=0;i<l*h;i+=h)
			{
				string s="";
				for(int j=i;j<i+h;j++)
					s+=str[j];
				ng+=s;
				g.push_back(turn(s));
			}
			draw();
			if(s!="")
				group_load(s);
		}
		void code_load(int l,string str,string s="")
		{
			clear();
			g.clear();
			int h=str.size()/l;
			len=l,hei=h;
			ng="";
			for(int i=0;i<l*h;i+=h)
			{
				string s="";
				for(int j=i;j<i+h;j++)
					s+=str[j];
				ng+=s;
				g.push_back(turn(s));
			}
			draw();
			if(s!="")
				group_load(s);
		}
		void code_load(vector<string>str,string s="")
		{
			int l=str.size(),mal=0;
			string k="";
			for(auto i:str)
				if(i.size()>mal)
					mal=i.size();
			for(auto i:str)
			{
				string temp=i;
				while(temp.size()<mal)
					temp+=" ";
				k+=temp;
			}
			code_load(l,k,s);
		}
		void code_load(vector<string>str,string group,string group_color)
		{
			code_load(str,group);
			group_load(group,group_color);
			group_use(group);
		}
		//绘制组 
		void draw()
		{
			if(!hidemode && !crash_edge())
			{
				for(int i=0;i<(int)g.size();i++)
				{
					gotoxy({pxy.x+i,pxy.y});
					cout<<color;
					cout<<g[i];
					cout<<Tool::getNONERGB();
				}
			}
		}
		void clear()
		{
			if(!crash_edge())
			{
				for(int i=0;i<(int)g.size();i++)
				{
					gotoxy({pxy.x+i,pxy.y});
					cout<<strs(" ",(int)g[i].size());
				}
			}
		}
		void color_load(string cl)
		{
			color=cl;
			draw();
		}
		//动作组 
		bool goto_xy(xy p,xy py={0,0})
		{
			clear();
			p=p+py;
			if(crash_edge(p))
				return 0;
			pxy=p;
			draw();
			return 1;
		}
		bool goto_item(Item p,xy py={0,0})
		{
			return goto_xy(p.get_xy(),py);
		}
		bool move_xy(int x,int y)
		{
			clear();
			if(crash_edge({pxy.x+x,pxy.y+y}))
				return 0;
			pxy={pxy.x+x,pxy.y+y};
			draw();
			return 1;
		}
		bool move_xy(xy p,xy py={0,0})
		{
			return move_xy(p.x+py.x,p.y+py.y);
		}
		void towards(int new_fac)
		{
			new_fac%=360;
			if(new_fac<0)new_fac=360+new_fac;
			fac=new_fac;
		}
		void towards(Item p,bool facing_center=1)
		{
			towards(round(get_to_facing(p,facing_center)));
		}
		void towards(xy p)
		{
			towards(round(get_to_facing(p)));
		}
		void left(int ang)
		{
			towards(fac-ang);
		}
		void right(int ang)
		{
			towards(fac+ang);
		}
		bool forward(double lens,double block_mode=2)
		{
			return goto_xy(get_len_xy(lens,block_mode));
		}
		bool forward_run(double lens,void *fun(xy),double block_mode=2)
		{
			xy p=pxy;
			bool flag=1;
			for(int i=0;i<=abs(lens);i++)
			{
				forward((lens<0?-i:i),block_mode),fun(pxy),flag=goto_xy(p);
				if(!flag)return 0;
			}
			return 1;
		}
		bool backward(double lens,double block_mode=2)
		{
			return forward(-lens,block_mode);
		}
		bool backward_run(double lens,void *fun(xy),double block_mode=2)
		{
			return forward_run(-lens,fun,block_mode);
		}
		void hide()
		{
			hidemode=1;
			clear();
		}
		void show()
		{
			hidemode=0;
			draw();
		}
		void kill()
		{
			killmode=1;
			clear();
		}
		//克隆组 
		void clone_this()//克隆自己 
		{
			Item p=jc_item();
			int u=-1;
			for(int i=0;i<(int)vis.size();i++)
				if(!vis[i])u=i;
			if(u==-1)
				clone.push_back(p),vis.push_back(1);
			else
				clone[u]=p,vis[u]=1;
			clone_clear_v();
		}
		void clone_item(Item p)//克隆图片 
		{
			int u=-1;
			for(int i=0;i<(int)vis.size();i++)
				if(!vis[i])u=i;
			if(u==-1)
				clone.push_back(p),vis.push_back(1);
			else
				clone[u]=p,vis[u]=1;
			clone_clear_v();
		}
		void clone_run(Item (*fun)(Item))
		{
			for(int i=0;i<(int)clone.size();i++)
				if(vis[i])
				{
					clone[i]=fun(clone[i]);
					if(clone[i].get_killmode())
						vis[i]=0;
				}
			clone_clear_v();
		}
		void clone_clear()
		{
			for(int i=0;i<(int)clone.size();i++)
				if(vis[i])
					clone[i].clear();
			clone.clear();
			vis.clear();
		}
		int clone_size()
		{
			int sum=0;
			for(int i=0;i<(int)clone.size();i++)
				if(vis[i])
					sum++;
			return sum;
		}
		//图片组 
		void group_load(string name,string group_color="")
		{
			group[name]=(picture){len,hei,g};
			group_c[name]=group_color;
		}
		void group_item(string name,Item p)
		{
			group[name]=(picture){p.get_len(),p.get_hei(),p.get_g()};
			group_c[name]=color;
		}
		void group_use(string name)
		{
			clear();
			picture p=group[name];
			len=p.l,hei=p.h;
			g=p.g;
			color_load(group_c[name]);
			draw();
		}
		void group_erase(string name)
		{
			group.erase(name);
			group_c.erase(name);
		}
		void group_set(map<string,picture>p)
		{
			group=p;
		}
		void group_color_set(map<string,string>group_color)
		{
			group_c=group_color;
		}
		//动画组 
		void frame_add(string name,string pname)
		{
			anime[name].push_back(pname);
			anime_frame[name]=0;
		}
		void frame_clear(string name)
		{
			anime[name].clear();
			anime_frame[name]=0;
		}
		void frame_use(string name,int start)
		{
			start=(start-1)%anime[name].size();
			anime_frame[name]=start;
			group_use(anime[name][anime_frame[name]]);
		}
		void frame_next(string name)
		{
			anime_frame[name]=(anime_frame[name]+1)%anime[name].size();
			group_use(anime[name][anime_frame[name]]);
		}
		/*暂不提供此函数 
		void frame_set(string name,int index,string pname)
		{
			index=(index-1)%anime[name].size();
			anime[name][index]=pname;
			if(index==anime_frame[name])
				group_use(anime[name][anime_frame[name]]);
		}
		*/
		vector<string> frame_get(string name)
		{
			return anime[name];
		}
		int frame_get_frame(string name)
		{
			return anime_frame[name];
		}
		//碰撞组 
		bool crash_mouse(bool must_show=1)//鼠标是否碰到图片矩形部分 
		{
			xy mp=Tool::mousexy();
			if(!hidemode || !must_show)
				if(mp.x>=pxy.x && mp.y>=pxy.y && mp.x<pxy.x+len && mp.y<pxy.y+hei)
					return 1;
			return 0;
		}
		bool crash_mouse_block(bool must_show=1)//鼠标是否碰到图片非空格部分 
		{
			if(!crash_mouse())return 0;
			xy mp=Tool::mousexy();
			mp=(xy){mp.x-pxy.x,mp.y-pxy.y};
			if(!hidemode || !must_show)
				if(g[mp.x][mp.y]!=' ')
					return 1;
			return 0;
		}
		bool crash_item(Item anitem,bool must_show=1)//某个其他图片是否碰到图片矩形部分 
		{
			if(must_show && (hidemode || anitem.get_hidemode()))
				return 0;
			xy p=anitem.get_xy();
			int l=anitem.get_len();
			int h=anitem.get_hei();
			for(int i=pxy.x;i<pxy.x+len;i++)
				for(int j=pxy.y;j<pxy.y+hei;j++)
					if(i>=p.x && j>=p.y && i<p.x+l && j<p.y+h)
						return 1;
			return 0;
		}
		bool crash_item_block(Item anitem,bool must_show=1)//某个其他图片是否碰到图片非空格部分 
		{
			if(must_show && (hidemode || anitem.get_hidemode()))
				return 0;
			xy p=anitem.get_xy();
			int l=anitem.get_len();
			int h=anitem.get_hei();
			for(int i=pxy.x;i<pxy.x+len;i++)
				for(int j=pxy.y;j<pxy.y+hei;j++)
					for(int k=p.x;k<p.x+l;k++)
						for(int m=p.y;m<p.y+h;m++)
							if(i==k && j==m && g[i-pxy.x][j-pxy.y]!=' ' && anitem.get_g()[k-p.x][m-p.y]!=' ')
								return 1;
			return 0;
		}
		bool crash_item_clone(Item anitem,bool must_show=1)
		{
			bool flag=0;
			for(auto i:anitem.get_clone())
				flag=flag || crash_item(i,must_show);
			return flag;
		}
		bool crash_item_clone_block(Item anitem,bool must_show=1)
		{
			bool flag=0;
			for(auto i:anitem.get_clone())
				flag=flag || crash_item_block(i,must_show);
			return flag;
		}
		bool crash_edge(xy np={-1,-1})
		{
			xy newp,p=EDGE;
			newp=(np==(xy){-1,-1}?pxy:np);
			if(newp.x>=0 && newp.y>=0 && newp.x+len<=p.x && newp.y+hei<=p.y)
				return 0;
			return 1;
		}
		//工具组 
		bool move_key(bool w,bool s,bool a,bool d,int speed=1)
		{
			bool f=1;
			if(w && KEYDOWN('W'))
				f=min(1,(int)move_xy(-speed,0));
			if(s && KEYDOWN('S'))
				f=min(1,(int)move_xy(speed,0));
			if(a && KEYDOWN('A'))
				f=min(1,(int)move_xy(0,-speed));
			if(d && KEYDOWN('D'))
				f=min(1,(int)move_xy(0,speed));
			return (bool)f;
		}
		bool move_key(int speed=1)
		{
			return move_key(1,1,1,1,speed);
		}
		bool move_key_def(bool i,bool b,int l,int r,char w,char s,char a,char d,int speed=1)
		{
			bool f=1;
			if(i && KEYDOWN(w))
				f=min(1,(int)move_xy(-speed,0));
			if(b && KEYDOWN(s))
				f=min(1,(int)move_xy(speed,0));
			if(l && KEYDOWN(a))
				f=min(1,(int)move_xy(0,-speed));
			if(r && KEYDOWN(d))
				f=min(1,(int)move_xy(0,speed));
			return (bool)f;
		}
		bool move_key_def(char w,char s,char a,char d,int speed=1)
		{
			return move_key_def(1,1,1,1,w,s,a,d,speed);
		}
		void print(xy p)
		{
			xy fp=pxy;
			pxy=p;
			draw();
			pxy=fp;
		}
};
Item FEItem(xy pos,int len,string picture,int hidemode=0)
{
	Item p(pos,hidemode);
	p.code_load(len,picture);
	return p;
}
template<typename T_item=Item>
class Main
{
	private:
		map<string,T_item>back;
		map<string,T_item>front;
		map<string,T_item>top;
	public:
		void add_back(string name,T_item p)
		{
			back[name]=p;
		}
		void add_front(string name,T_item p)
		{
			front[name]=p;
		}
		void add_top(string name,T_item p)
		{
			top[name]=p;
		}
		void run_back(vector<string>name,T_item (*fun)(Item))
		{
			for(auto i:name)
			{
				back[i]=fun(back[i]);
				if(back[i].get_killmode())
					back.erase(i);
			}
		}
		void run_front(vector<string>name,T_item (*fun)(Item))
		{
			for(auto i:name)
			{
				front[i]=fun(front[i]);
				if(front[i].get_killmode())
					front.erase(i);
			}
		}
		void run_top(vector<string>name,T_item (*fun)(Item))
		{
			for(auto i:name)
			{
				top[i]=fun(top[i]);
				if(top[i].get_killmode())
					top.erase(i);
			}
		}
		void run_back_all(T_item (*fun)(T_item))
		{
			vector<string>name;
			for(auto i:back)
				name.push_back(i.first);
			run_back(name,fun);
		}
		void run_front_all(T_item (*fun)(T_item))
		{
			vector<string>name;
			for(auto i:front)
				name.push_back(i.first);
			run_front(name,fun);
		}
		void run_top_all(T_item (*fun)(T_item))
		{
			vector<string>name;
			for(auto i:top)
				name.push_back(i.first);
			run_top(name,fun);
		}
		void draw()
		{
			for(auto i:back)
				i.second.draw();
			for(auto i:front)
				i.second.draw();
			for(auto i:top)
				i.second.draw();
		}
};

namespace Physics
{
	double p_g=9.8;
	class EP_Item:public Item//Easy_Physics_Item
	{
		protected:
			int p_m;//质量g
			int p_zq;//周期 
			int p_L;
		public:
			EP_Item(xy p,int m)
			{
				pxy=p,p_m=m,p_zq=0,p_L=p_g*100/p_m;
			}
			void p_down()
			{
				if(++p_zq<p_L)return;
				p_zq=0;
				if(!crash_edge(pxy+(xy){1,0}))
					move_xy({1,0});
			}
	};
}
#endif