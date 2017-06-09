#include "decision.h"
#include "WineAI.h"
#include "tools.h"


WineAI wine;
int mytable[15][15];


char* GetPos(char pos[], char WorB)
{
    static int init_flag = 0;
    int size = 15;
    if (init_flag == 0){
        init_flag ++;
        wine.SetSize(size);

    }

    int x, y;
    read_table("ChessLog.txt", x, y);
    cout << "上一局电脑落子位置：" << x << y;
    getchar();

	if (WorB == 'b')
	{

		//int x, y;
        Pos best, input;
        if (x == -1){
            //我方先走
            best = wine.TurnBest();
            wine.TurnMove(best);
        }else{
            //我方后走
            input.x = x;
            input.y = y;
            wine.TurnMove(input);
            best = wine.TurnBest();
            wine.TurnMove(best);
        }

        wine.Display();

        getchar();
        mytable[best.x][best.y]=2;


		//cin >> x >> y;
		//cin.clear();
		//cin.ignore(10, '\n');
		pos[0] = best.x;
		pos[1] = best.y;

		return pos;
	}
	else if (WorB == 'w')
	{
        //int x, y;
        Pos best, input;
        if (x == -1){
            //我方先走
            best = wine.TurnBest();
            wine.TurnMove(best);
        }else{
            //我方后走
            input.x = x;
            input.y = y;
            wine.TurnMove(input);
            best = wine.TurnBest();
            wine.TurnMove(best);
        }
        wine.Display();
        getchar();

        //cin >> x >> y;
        //cin.clear();
        //cin.ignore(10, '\n');
        pos[0] = best.x;
        pos[1] = best.y;
        mytable[best.x][best.y]=1;

        return pos;
	}
	else
	{
		pos[0] = 0;
		pos[1] = 0;

		return pos;
	}
}