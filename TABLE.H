#include<iostream>
#include<iomanip>

using namespace std;

class Table
{
public:
	Table(int input[15][15]);   //构造函数
	void display();            // 显示棋盘
	void displaygameover(int a , int b );
	bool set(int a ,int b ,int color );       //下子操作
	friend class Judge ;
	friend class Ai ;
private:
	int data[15][15];   //棋盘数据
};

