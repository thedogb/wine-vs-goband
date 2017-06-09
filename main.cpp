#include "TABLE.H"
#include "JUDGE.H"
#include "AI.H"
#include "decision.h"

char cycle()
{
	cout << "先输入行数（纵坐标），再输入列数（横坐标），中间用空格隔开;" << endl;
	cout << "A - E 对应 10 - 14，请勿输入字母" << endl << endl;
	int input[15][15];
	for(int i = 0 ; i < 15 ; i++ ){
		for(int j = 0 ; j < 15 ; j++ ){
			input[i][j] = 0 ;
		}
	}
	Table fivetable(input);
	fivetable.display();

	cout<<"\n请选择模式:\n\t1. P v E.\n\t2. P v P."<<endl;
    int mode;
	cin >> mode;
	cin.clear();
	cin.ignore(10, '\n');
	//mode = 1 or 2;      固定模式

	Judge judgeblack( 2 ) ;
	Judge judgewhite( 1 ) ;

	int count = 1 ;
	int line , column ;


////////////////////////////////    双人游戏模式      ///////////////////////////////////
	if( mode == 2 )
	{
		while( 225-count > 0 ){
			if( count%2 ){
				cout<<"黑棋下子"<<endl ;
				do{
					char pos[2];
					GetPos(pos, 'b');
					line = pos[0];
					column = pos[1];
				}while( !fivetable.set( line, column, 2) );   //2是黑棋  1是白棋
				if( judgeblack.longlink( fivetable ) ){
					fivetable.displaygameover( line ,column );
					cout << "黑棋长连禁手，白棋胜" << endl;
					return 0;
				}
				if( judgeblack.fivelink( fivetable ) ){
					fivetable.displaygameover( line ,column );
					cout<<"黑棋五连，黑棋胜"<<endl ;
					return 0;
				}
				if( judgeblack.huosan( fivetable ) > 1 ){
		            fivetable.displaygameover( line ,column );
					cout<<"黑棋三三禁手，白棋胜"<<endl ;
					return 0;
				}
				if( judgeblack.si( fivetable ) > 1 ){
				    fivetable.displaygameover( line ,column );
					cout<<"黑棋四四禁手，白棋胜"<<endl ;
					return 0;
				}
				fivetable.display();
			}
			else{
				cout<<"白棋下子"<<endl ;
				do{
					char pos[2];
					GetPos(pos, 'w');
					line = pos[0];
					column = pos[1];
				}while( !fivetable.set( line, column, 1) );
				if( judgewhite.fivelink( fivetable ) ){
					fivetable.displaygameover( line ,column );
					cout<<"白棋五连，白棋胜"<<endl ;
					return 0;
				}
		//		cout<<judgewhite.si( fivetable )<<endl ;
				fivetable.display();
			}
			count++ ;
		}
		cout<<"和棋"<<endl ;
		return 0;
	}

/////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////    单人游戏模式      ///////////////////////////////////
	if( mode == 1 )
	{
		cout<<"1.玩家先下\n2.电脑先下"<<endl ;
		int xianshou ;
		cin>>xianshou ;
		cin.clear();
		cin.ignore(10, '\n');
		

		int position ;

		/////////////////  玩家先手 //////////////////
		if( xianshou == 1 )
		{
			Ai white( 1 ) ;
			fivetable.display();
			while( 225-count > 0 ){
				if( count%2 ){
					do{
						char pos[2];
						GetPos(pos, 'b');
						line = pos[0];
						column = pos[1];
					}while( !fivetable.set( line, column, 2) );
			    	if( judgeblack.longlink( fivetable ) ){
					    fivetable.displaygameover( line ,column );
					    cout<<"黑棋长连禁手，you lose"<<endl ;
					    return 0;
					}
				    if( judgeblack.fivelink( fivetable ) ){
				    	fivetable.displaygameover( line ,column );
				    	cout<<"黑棋五连，you win"<<endl ;
					    return 0;
					}
			    	if( judgeblack.huosan( fivetable ) > 1 ){
		                fivetable.displaygameover( line ,column );
				    	cout<<"黑棋三三禁手，you lose"<<endl ;
					    return 0;
					}
			    	if( judgeblack.si( fivetable ) > 1 ){
				        fivetable.displaygameover( line ,column );
				    	cout<<"黑棋四四禁手，you lose"<<endl ;
					    return 0;
					}
			    	fivetable.display();
				}

		    	else{
					position = white.xiazi( fivetable ) ;
					line = position / 100 ;
					column = position % 100 ;
					fivetable.set( line, column, 1 ) ;
					if( judgewhite.fivelink( fivetable ) ){
				    	fivetable.displaygameover( line ,column );
					    cout<<"白棋五连，you lose"<<endl ;
					    return 0;
					}
			    	fivetable.display();
				}

				count ++ ;
			}

			cout<<"和棋"<<endl ;
			return 0;

		}


		/////////////////  电脑先手 //////////////////
		else
		{
			Ai black( 2 ) ;
			while( 225-count > 0 ){
				if( count%2 ){
					position = black.xiazi( fivetable ) ;
					line = position / 100 ;
					column = position % 100 ;
					fivetable.set( line, column, 2 ) ;
			    	if( judgeblack.longlink( fivetable ) ){
					    fivetable.displaygameover( line ,column );
					    cout<<"黑棋长连禁手，you win"<<endl ;
					    return 0;
					}
				    if( judgeblack.fivelink( fivetable ) ){
				    	fivetable.displaygameover( line ,column );
				    	cout<<"黑棋五连，you lose"<<endl ;
					    return 0;
					}
			    	if( judgeblack.huosan( fivetable ) > 1 ){
		                fivetable.displaygameover( line ,column );
				    	cout<<"黑棋三三禁手，you win"<<endl ;
					    return 0;
					}
			    	if( judgeblack.si( fivetable ) > 1 ){
				        fivetable.displaygameover( line ,column );
				    	cout<<"黑棋四四禁手，you win"<<endl ;
						return 0;
					}
			    	fivetable.display();
				}

		    	else{
					do{
						char pos[2];
						GetPos(pos, 'w');
						line = pos[0];
						column = pos[1];
					}while( !fivetable.set( line, column, 1) );
					if( judgewhite.fivelink( fivetable ) ){
				    	fivetable.displaygameover( line ,column );
					    cout<<"白棋五连，you win"<<endl ;
					    return 0;
					}
			    	fivetable.display();
				}

				count ++ ;
			}

			cout<<"和棋"<<endl ;
			return 0;

		}
	}

/////////////////////////////////////////////////////////////////////////////////////////

	
	return 0;
}


int main()
{
	char cycle() ;
	char flag = 'r' ;
	while( flag == 'r' ){
		cycle();
		cout << "\n按r键继续，按其他键退出\n" << endl;
		cin >> flag;
		cin.clear();
		cin.ignore(10, '\n');
	}
	return 0 ;

}







