#include "TABLE.H"
#include "JUDGE.H"
#include "AI.H"
#include <fstream>
ofstream FileWriter;  //文件输出流

/////////////////////////////////////////////////////////////////////////////////////////

Table::Table(int input[15][15])           //构造函数
{
	for(int i = 0 ; i < 15 ; i++ ){
		for(int j = 0 ; j < 15 ; j++ ){
			data[i][j] = input[i][j] ;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void Table::display()
{
	int i = 0 , j = 0 ; 

	cout << "\t ";
	for (j = 0; j < 15; j++){
		printf(" %X", j);
	}
	cout << endl;

	if(data[0][0] == 0){
		cout<<"\t0┏" ;
	}
	else{
		if(data[0][0] == 1){
            cout<<"\t0●" ;
		}
		else cout<<"\t0○" ;
	}

	for( j = 1 ; j < 14 ; j++ ){
		if(data[i][j] == 0){
		    cout<<"┯" ;
		}
	    else{
		    if(data[i][j] == 1){
				cout<<"●" ;
			}
			else cout<<"○" ;
		}
	}

	if(data[0][14] == 0){
		cout<<"┓"<<endl ;
	}
	else{
		if(data[0][14] == 1){
			cout<<"●"<<endl ;
		}
		else cout<<"○"<<endl ;	
	}


	for(i = 1 ; i < 14 ; i++ ){
		if(data[i][0] == 0){
			printf("\t%X┠",i);
		}
	    else{
	        if(data[i][0] == 1){
				printf("\t%X●",i);
			}
			else printf("\t%X○",i);
		}
		for( j = 1 ; j < 14 ; j++ ){
		    if(data[i][j] == 0){
		        cout<<"┼" ;
			}
	        else{
		        if(data[i][j] == 1){
				    cout<<"●" ;
				}
		        else cout<<"○" ;
			}
		}
		if(data[i][14] == 0){
		    cout<<"┨"<<endl ;
		}
	    else{
		    if(data[i][14] == 1){
			    cout<<"●"<<endl ;
			}
		    else cout<<"○"<<endl ;
		}
	}


	if(data[i][0] == 0){
		cout<<"\tE┗" ;
	}
	else{
		if(data[i][0] == 1){
			cout<<"\tE●" ;
		}
		else cout<<"\tE○" ;
	}

	for( j = 1 ; j < 14 ; j++ ){
		if(data[i][j] == 0){
		    cout<<"┷" ;
		}
	    else{
		    if(data[i][j] == 1){
				cout<<"●" ;
			}
		    else cout<<"○" ;
		}
	}

	if(data[i][14] == 0){
		cout<<"┛"<<endl ;
	}
	else{
		if(data[i][14] == 1){
			cout<<"●"<<endl ;
		}
		else cout<<"○"<<endl ;
	}

	// 保存棋盘矩阵 15x15
	char ChessLogName[20] = "ChessLog.txt";
	FileWriter.open(ChessLogName);
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			FileWriter << data[i][j] << " ";
		}
		FileWriter << endl;
	}
	FileWriter.close();
}

/////////////////////////////////////////////////////////////////////////////////////////


bool Table::set(int a ,int b ,int color )
{
	if( data[a][b] == 0 && a >= 0 && a < 15 && b >= 0 && b < 15 ){
    	if( color == 1 ){
	    	data[a][b] = 1 ;
			return 1 ;
		}
    	if( color == 2 ){
	    	data[a][b] = 2 ;
			return 1 ;
		}
	}
	else{
		if( a > 14 || b > 14 || a < 0 || b < 0){
			cout << "请把棋子下在棋盘内" << endl;
		    return 0 ;
		}
		else{
			if (data[a][b] != 0)
			{
				cout << "此处已有棋子，请重新下子" << endl;
				return 0;
			}
		}
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////


void Table::displaygameover(int a , int b )
{
	int i = 0 , j = 0 ; 

	cout << "\t ";
	for (j = 0; j < 15; j++){
		printf(" %X", j);
	}
	cout << endl;

	if(data[0][0] == 0){
		cout<<"\t0┏" ;
	}
	else{
		if(data[0][0] == 1){
            if(a == 0 && b == 0 ) cout<<"\t0★" ;
			else cout<<"\t0●" ;
		}
		else{
			if(a == 0 && b == 0 ) cout<<"\t0☆" ; 
			else cout<<"\t0○" ;
		}
	}

	for( j = 1 ; j < 14 ; j++ ){
		if(data[i][j] == 0){
		    cout<<"┯" ;
		}
	    else{
		    if(data[i][j] == 1){
				if(i == a && j == b ) cout<<"★" ;
				else cout<<"●" ;
			}
			else{
				if(i == a && j == b ) cout<<"☆" ;
				else cout<<"○" ;
			}
		}
	}

	if(data[0][14] == 0){
		cout<<"┓"<<endl ;
	}
	else{
		if(data[0][14] == 1){
			if(a == 0 && b == 14 ) cout<<"★"<<endl ;
			else cout<<"●"<<endl ;
		}
		else{
			if(a == 0 && b == 14 ) cout<<"☆"<<endl ;
			else cout<<"○"<<endl ;	
		}
	}


	for(i = 1 ; i < 14 ; i++ ){
		if(data[i][0] == 0){
			printf("\t%X┠",i);
		}
	    else{
	        if(data[i][0] == 1){
				if(a == i && b == 0 ) printf("\t%X★",i);
				else printf("\t%X●",i);
			}
			else{
				if(a == i && b == 0 ) printf("\t%X☆",i);
				else printf("\t%X○",i);
			}
		}
		for( j = 1 ; j < 14 ; j++ ){
		    if(data[i][j] == 0){
		        cout<<"┼" ;
			}
	        else{
		        if(data[i][j] == 1){
				    if(i == a && j == b ) cout<<"★" ;
				    else cout<<"●" ;
				}
		        else{
				    if(i == a && j == b ) cout<<"☆" ;
				    else cout<<"○" ;
				}
			}
		}
		if(data[i][14] == 0){
		    cout<<"┨"<<endl ;
		}
	    else{
		    if(data[i][14] == 1){
			    if(a == i && b == 14 ) cout<<"★"<<endl ;
				else cout<<"●"<<endl ;
			}
			else{
				if(a == i && b == 14 ) cout<<"☆"<<endl ;
				else cout<<"○"<<endl ;
			}
		}
	}


	if(data[i][0] == 0){
		cout<<"\tE┗" ;
	}
	else{
		if(data[i][0] == 1){
			if(a == i && b == 0 ) cout<<"\tE★" ;
			else cout<<"\tE●" ;
		}
		else{
			if(a == i && b == 0 ) cout<<"\tE☆" ;
			else cout<<"\tE○" ;
		}
	}

	for( j = 1 ; j < 14 ; j++ ){
		if(data[i][j] == 0){
		    cout<<"┷" ;
		}
	    else{
		    if(data[i][j] == 1){
				if(i == a && j == b ) cout<<"★" ;
				else cout<<"●" ;
			}
		    else{
				if(i == a && j == b ) cout<<"☆" ;
				else cout<<"○" ;
			}
		}
	}

	if(data[i][14] == 0){
		cout<<"┛"<<endl ;
	}
	else{
		if(data[i][14] == 1){
			if(a == i && b == 14 ) cout<<"★"<<endl ;
			else cout<<"●"<<endl ;
		}
		else{
			if(a == i && b == 14 ) cout<<"☆"<<endl ;
			else cout<<"○"<<endl ;
		}
	}

	// 保存棋盘矩阵 15x15
	char ChessLogName[20] = "ChessLog.txt";
	FileWriter.open(ChessLogName);
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			FileWriter << data[i][j] << " ";
		}
		FileWriter << endl;
	}
	FileWriter.close();

}

/////////////////////////////////////////////////////////////////////////////////////////



