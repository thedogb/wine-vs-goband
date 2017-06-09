#include<iostream>
#include<iomanip>
using namespace std;

class Judge
{
public:
	Judge( int k );
	bool longlink( Table T );
	int fivelink( Table T );
	int si( Table T );
	int huosan( Table T );
/*	int chongsan( Table T );
	int huoer( Table T );
	int chonger( Table T );
	int huoyi( Table T );
	int chongyi( Table T );*/
	friend class Table ;
	friend class Ai ;
private:
	int color ;
	int anticolor ;
};