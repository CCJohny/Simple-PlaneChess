//飞行棋
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

char table[53]="OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO", base[5]="YYYY"; //定义棋盘与玩家基地 
int a=-1, b=-1, c=-1, d=-1, color=0, i, circle=0, circleNum, point, lucky=6, A=-1, B=-1, C=-1, D=-1, E=-2; //四个玩家的步数、棋盘定位、回合、骰子点数、取6、位置、同位判断 
bool get6=false, termin=false; //判定是否已开始游戏以及到达终点 
string info="\n\n", FLY="", EATI=""; //步数及奖励信息 

void rule() //打印规则 
{
	cout << "欢迎运行简易飞行棋！" << endl << endl;
	cout << "为简化操作，每个玩家仅拥有1架飞机，" << endl;
	cout << "每局以先绕棋盘一圈返回基地的玩家胜" << endl;
	cout << "出（不要求点数恰好）。" << endl;
	cout << "1.骰子掷到数字6方可起飞。" << endl;
	cout << "2.遇到同色格子可前进至下一同色格。" << endl;
	cout << "3.遇到同色航线可沿航线飞行至对应的" << endl;
	cout << "格子。" << endl;
	cout << "4.遇到其他玩家的飞机，则将对方玩家" << endl;
	cout << "的飞机驱逐回基地。" << endl;
	cout << "5.掷到数字6可再掷一次。" << endl << endl;
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "玩家A(真人) ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "玩家B(电脑)" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "玩家D(电脑) ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "玩家C(真人)" << endl << endl; 
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "现在轮到玩家A，要掷骰子，";
	system("pause");
}

void color_judge_table(int j) //判断格子输出颜色 
{
	//棋盘默认 
	if(j%4==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	if(j%4==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	if(j%4==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	if(j%4==0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	
	//棋子颜色 
	if(j==A) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	if(j==B) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	if(j==D) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	if(j==C) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
}
void color_judge_player(char j) //判断玩家输出颜色 
{
	if(j=='A') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	if(j=='B') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	if(j=='D') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	if(j=='C') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
}

void print_table() //打印棋盘 
{
	system("cls");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "玩家A(真人) ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "玩家B(电脑)" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "玩家D(电脑) ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "玩家C(真人)" << endl << endl; 
	
	//显示点数
	//cout << circleNum;
	char circleName=circleNum+65;
	color_judge_player(circleName);
	cout << "玩家" << circleName << "掷出了" << point << "点" << endl << endl;
	cout << FLY << info; 
	FLY="";
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << base[0];
	cout << "                             ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << base[1] << endl;
	cout << "  ";
	for(i=0;i<14;i++)
	{
		color_judge_table(i);
		cout << table[i] << ' ';
	}
	cout << endl;
	for(i=0;i<12;i++)
	{
		color_judge_table(51-i);
		cout << "  " << table[51-i];
		if(i<4)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			cout << "             | ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			cout << "|         ";
		}
		if(i==4)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			cout << "-------------+ ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			cout << "|         ";
		}
		if(i==5)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "---------+     ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			cout << "|         ";
		}
		if(i==6)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "         |     ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			cout << "+---------";
		}
		if(i==7)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "         | ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << "+-------------";
		}
		if(i>7)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "         | ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << "|             ";
		}
		color_judge_table(14+i);
		cout << table[14+i] << endl;
	}
	cout << "  ";
	for(i=0;i<14;i++)
	{
		color_judge_table(39-i);
		cout << table[39-i] << ' ';
	}
	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << base[2];
	cout << "                             ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << base[3] << endl << endl;
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	cout << EATI;
	EATI="";
	
	if(termin)
	{
		cout << "游戏结束！" << endl;
		system("pause");
		abort();
	}
	
	circleNum=circleNum+66;
	if(circleNum==69) circleNum=65;
	circleName=circleNum;
	if(circleNum%2==0)
	{
		int downcount,rt1,rt2;
		srand( static_cast<unsigned int>(time(0)) );
		rt1=rand()%1000;
		rt2=rand()%1000;
		downcount=(rt1*rt2)%4000+2000;
		//downcount=1;
		cout << "现在轮到玩家" << circleName << "，将在" << downcount << "毫秒后掷骰子";
		Sleep(downcount);
	}
	else
	{
		cout << "现在轮到玩家" << circleName << "，要掷骰子，";
		system("pause");
	}
}

void get_point() //掷色子 
{
	srand( static_cast<unsigned int>(time(0)));
	point=1+rand()%6;
}

void move_judge() //步数判定 
{
	if(point==6)
	{
		switch(circleNum) //circle--是为了再掷一次 
		{
			case 0 :
				if(a==-1)
				{
					a=0;
					info="A起飞了\n\n";
					base[0]='O'; 
				}
				else
				{
					a=a+6;
					get6=true;
					if(a%4==2)
					{
						if(a==34)
						{
							a=a+12;
							FLY="A抵达了航线，飞行12步~";	
						} 
						else
						{
							a=a+4;
							FLY="A抵达了同色格子，前跳4步~";
						} 
					}
				}
				if(a>=52)
				{
					info="A到达了终点！\n\n";
					termin=true; 
					a=52; 
				}
				table[A]='O';
				A=a%52;
				table[A]='Y';
				E=A;
				break;
			case 1 :
				if(b==-1)
				{
					b=13;
					info="B起飞了\n\n";
					base[1]='O'; 
				}
				else 
				{
					b=b+6;
					get6=true;
					if(b%4==3)
					{
						if(b==47)
						{
							b=b+12;
							FLY="B抵达了航线，飞行12步~";	
						} 
						else
						{
							b=b+4;
							FLY="B抵达了同色格子，前跳4步~";
						} 
					}
				}
				if(b>=65)
				{
					info="B到达了终点！\n\n";
					termin=true; 
					b=65; 
				}
				table[B]='O';
				B=b%52;
				E=B;
				table[B]='Y';
				break;
			case 2 :
				if(c==-1) 
				{
					c=26;
					info="C起飞了\n\n";
					base[3]='O'; 
				}
				else 
				{
					c=c+6;
					get6=true;
					if(c%4==1)
					{
						if(c==60)
						{
							c=c+12;
							FLY="C抵达了航线，飞行12步~";	
						} 
						else
						{
							c=c+4;
							FLY="C抵达了同色格子，前跳4步~";
						} 
					}
				}
				if(c>=78)
				{
					info="C到达了终点！\n\n";
					termin=true; 
					c=78; 
				}
				table[C]='O';
				C=c%52;
				E=C;
				table[C]='Y';
				break;
			case 3 :
				if(d==-1) 
				{
					d=39;
					info="D起飞了\n\n";
					base[2]='O'; 
				}
				else 
				{
					d=d+6;
					get6=true;
					if(d%4==0)
					{
						if(d==73)
						{
							d=d+12;
							FLY="D抵达了航线，飞行12步~";	
						} 
						else
						{
							d=d+4;
							FLY="D抵达了同色格子，前跳4步~";
						} 
					}
				}
				if(d>=91)
				{
					info="D到达了终点！\n\n";
					termin=true; 
					d=91; 
				}
				table[D]='O';
				D=d%52;
				E=D;
				table[D]='Y';
				break;
			default :
				system("cls");
				cout << "游戏崩溃！非常抱歉！" << endl;
				system("pause");
				abort();
   		}
	}
	else
	{
		switch(circleNum)
		{
			case 0 :
				if(a==-1) 
				{
					info="A未能起飞\n\n";
				}
				else 
				{
					a=a+point;
					info="\n\n";
					if(a%4==2)
					{
						if(a==34)
						{
							a=a+12;
							FLY="A抵达了航线，飞行12步~";	
						} 
						else
						{
							a=a+4;
							FLY="A抵达了同色格子，前跳4步~";
						} 
					}
				}
				if(a>=52)
				{
					info="A到达了终点！\n\n";
					termin=true; 
					a=52; 
				}
				table[A]='O';
				A=a%52;
				E=A;
				table[A]='Y';
				break;
			case 1 :
				if(b==-1) 
				{
					info="B未能起飞\n\n";
				}
				else 
				{
					b=b+point;
					info="\n\n";
					if(b%4==3)
					{
						if(b==47)
						{
							b=b+12;
							FLY="B抵达了航线，飞行12步~";	
						} 
						else
						{
							b=b+4;
							FLY="B抵达了同色格子，前跳4步~";
						} 
					}
				}
				if(b>=65)
				{
					info="B到达了终点！\n\n";
					termin=true; 
					b=65; 
				}
				table[B]='O';
				B=b%52;
				E=B;
				table[B]='Y';
				break;
			case 2 :
				if(c==-1) 
				{
					info="C未能起飞\n\n";
				}
				else 
				{
					c=c+point;
					info="\n\n";
					if(c%4==1)
					{
						if(c==60)
						{
							c=c+12;
							FLY="C抵达了航线，飞行12步~";	
						} 
						else
						{
							c=c+4;
							FLY="C抵达了同色格子，前跳4步~";
						} 
					}
				}
				if(c>=78)
				{
					info="C到达了终点！\n\n";
					termin=true; 
					c=78; 
				}
				table[C]='O';
				C=c%52;
				E=C;
				table[C]='Y';
				break;
			case 3 :
				if(d==-1) 
				{
					info="D未能起飞\n\n";
				}
				else 
				{
					d=d+point;
					info="\n\n";
					if(d%4==0)
					{
						if(d==73)
						{
							d=d+12;
							FLY="D抵达了航线，飞行12步~";	
						} 
						else
						{
							d=d+4;
							FLY="D抵达了同色格子，前跳4步~";
						} 
					}
				}
				if(d>=91)
				{
					info="D到达了终点！\n\n";
					termin=true; 
					d=91; 
				}
				table[D]='O';
				D=d%52;
				E=D;
				table[D]='Y';
				break;
			default :
				system("cls");
				cout << "游戏崩溃！非常抱歉！" << endl;
				system("pause");
				abort();
   		}
	}
}

void eat_judge(int ej, char ejc)
{
	if(ej!=-1)
	{
		if(ej==A && ejc!='A')
		{
			E=-2;
			A=-1;
			a=-1;
			base[0]='Y';
			EATI="噢，A被驱逐回基地了……\n\n";
		}
		if(ej==B && ejc!='B')
		{
			E=-2;
			B=-1;
			b=-1;
			base[1]='Y';
			EATI="噢，B被驱逐回基地了……\n\n";
		}
		if(ej==C && ejc!='C')
		{
			E=-2;
			C=-1;
			c=-1;
			base[3]='Y';
			EATI="噢，C被驱逐回基地了……\n\n";
		}
		if(ej==D && ejc!='D')
		{
			E=-2;
			D=-1;
			d=-1;
			base[2]='Y';
			EATI="噢，D被驱逐回基地了……\n\n";
		}
	}
}

int main()
{
	rule(); 
	
	while(1)
	{
		circleNum=circle%4;
		get_point();
		move_judge();
		if(get6)
		{
			cout << "恭喜，你掷到了6，可以再掷一次！";
			if(circleNum%2==0) system("pause");
			while(point==6) get_point();
			move_judge();
			point=point+6;
			get6=false;
		}
		eat_judge(E, circleNum+65);
		//cout << circleNum;
		print_table(); 
		circle++;
		//system("pause");
	}
	
	return 0;
}
