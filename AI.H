#include<iostream>
#include<iomanip>
using namespace std;

class Ai
{
public:
	Ai( int k );
	int score( Table T ,int i ,int j );
	int xiazi( Table T );
	friend class Table ;
	friend class Judge ;
private:
	int color ;
	int anticolor ;
};