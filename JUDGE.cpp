#include "TABLE.H"
#include "JUDGE.H"
#include "AI.H"

/////////////////////////////////////////////////////////////////////////////////////////

Judge::Judge( int k )           //    构造函数
{
	color = k ;
	if( k == 1 ) anticolor = 2 ;
	else anticolor = 1 ;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool Judge::longlink( Table T )      // 判断长连
{
	int i, j ;
	for( i = 0 ; i < 15 ; i++ ){        //判断黑棋横向长连
		for( j = 0 ; j < 10 ; j++ ){
			if( T.data[i][j] == 2 && T.data[i][j+1] == 2 && T.data[i][j+2] == 2 && T.data[i][j+3] == 2 && T.data[i][j+4] == 2 && T.data[i][j+5] == 2){
				return 1 ;
			}
		}
	}

	for( i = 0 ; i < 10 ; i++ ){          //判断黑棋纵向长连
		for( j = 0 ; j < 15 ; j++ ){
			if( T.data[i][j] == 2 && T.data[i+1][j] == 2 && T.data[i+2][j] == 2 && T.data[i+3][j] == 2 && T.data[i+4][j] == 2 && T.data[i+5][j] == 2){
				return 1 ;
			}
		}
	}

	for( i = 0 ; i < 10 ; i++ ){              //判断黑棋“\”向长连
		for( j = 0 ; j < 10 ; j++ ){
			if( T.data[i][j] == 2 && T.data[i+1][j+1] == 2 && T.data[i+2][j+2] == 2 && T.data[i+3][j+3] == 2 && T.data[i+4][j+4] == 2 && T.data[i+5][j+5] == 2){
				return 1 ;
			}
		}
	}

	for( i = 0 ; i < 10 ; i++ ){              //判断黑棋“/”向长连
		for( j = 5 ; j < 15 ; j++ ){
			if( T.data[i][j] == 2 && T.data[i+1][j-1] == 2 && T.data[i+2][j-2] == 2 && T.data[i+3][j-3] == 2 && T.data[i+4][j-4] == 2 && T.data[i+5][j-5] == 2){
				return 1 ;
			}
		}
	}
	
	return 0 ;
}

/////////////////////////////////////////////////////////////////////////////////////////


int Judge::fivelink( Table T )            // 判断五连
{
	int i, j ;
	if( color == 1 ){            //判断横向五连
		for( i = 0 ; i < 15 ; i++ ){
			for( j = 0 ; j < 11 ; j++ ){
				if( T.data[i][j] == 1 && T.data[i][j+1] == 1 && T.data[i][j+2] == 1 && T.data[i][j+3] == 1 && T.data[i][j+4] == 1){
					return 1 ;
				}
			}
		}
	}
	else{
		for( i = 0 ; i < 15 ; i++ ){
			for( j = 0 ; j < 11 ; j++ ){
				if( T.data[i][j] == 2 && T.data[i][j+1] == 2 && T.data[i][j+2] == 2 && T.data[i][j+3] == 2 && T.data[i][j+4] == 2){
					return 2 ;
				}
			}
		}
	}

	if( color == 1 ){            //判断纵向五连
		for( i = 0 ; i < 11 ; i++ ){
			for( j = 0 ; j < 15 ; j++ ){
				if( T.data[i][j] == 1 && T.data[i+1][j] == 1 && T.data[i+2][j] == 1 && T.data[i+3][j] == 1 && T.data[i+4][j] == 1){
					return 1 ;
				}
			}
		}
	}
	else{
		for( i = 0 ; i < 11 ; i++ ){
			for( j = 0 ; j < 15 ; j++ ){
				if( T.data[i][j] == 2 && T.data[i+1][j] == 2 && T.data[i+2][j] == 2 && T.data[i+3][j] == 2 && T.data[i+4][j] == 2){
					return 2 ;
				}
			}
		}
	}

	if( color == 1 ){            //判断“\”向五连
		for( i = 0 ; i < 11 ; i++ ){
			for( j = 0 ; j < 11 ; j++ ){
				if( T.data[i][j] == 1 && T.data[i+1][j+1] == 1 && T.data[i+2][j+2] == 1 && T.data[i+3][j+3] == 1 && T.data[i+4][j+4] == 1){
					return 1 ;
				}
			}
		}
	}
	else{
		for( i = 0 ; i < 11 ; i++ ){
			for( j = 0 ; j < 11 ; j++ ){
				if( T.data[i][j] == 2 && T.data[i+1][j+1] == 2 && T.data[i+2][j+2] == 2 && T.data[i+3][j+3] == 2 && T.data[i+4][j+4] == 2){
					return 2 ;
				}
			}
		}
	}

	if( color == 1 ){            //判断“/”向五连
		for( i = 0 ; i < 11 ; i++ ){
			for( j = 4 ; j < 15 ; j++ ){
				if( T.data[i][j] == 1 && T.data[i+1][j-1] == 1 && T.data[i+2][j-2] == 1 && T.data[i+3][j-3] == 1 && T.data[i+4][j-4] == 1){
					return 1 ;
				}
			}
		}
	}
	else{
		for( i = 0 ; i < 11 ; i++ ){
			for( j = 4 ; j < 15 ; j++ ){
				if( T.data[i][j] == 2 && T.data[i+1][j-1] == 2 && T.data[i+2][j-2] == 2 && T.data[i+3][j-3] == 2 && T.data[i+4][j-4] == 2){
					return 2 ;
				}
			}
		}
	}
	return 0 ;
}

/////////////////////////////////////////////////////////////////////////////////////////


int Judge::si( Table T )            // 判断四（包括冲四、活四），并返回棋盘中“四”的个数
{
	int i , j , pi = 22 , pj = 22 , count = 0 ;
	for( i = 0 ; i < 15 ; i++ ){        //判断横向四
		for( j = 0 ; j < 11 ; j++ ){
			if((i != pi || j != pj+1 ) && T.data[i][j] != anticolor && T.data[i][j+1] != anticolor && T.data[i][j+2] != anticolor && T.data[i][j+3] != anticolor && T.data[i][j+4] != anticolor && ( T.data[i][j] + T.data[i][j+1] + T.data[i][j+2] + T.data[i][j+3] + T.data[i][j+4] ) == 4*color ){
				count ++ ;
				pi = i ; pj = j ;
			}
		}
	}

    pi = 22 ; pj = 22 ;
	for( i = 0 ; i < 11 ; i++ ){   //判断纵向四
		for( j = 0 ; j < 15 ; j++ ){
			if((i != pi+1 || j != pj ) && T.data[i][j] != anticolor && T.data[i+1][j] != anticolor && T.data[i+2][j] != anticolor && T.data[i+3][j] != anticolor && T.data[i+4][j] != anticolor && ( T.data[i][j] + T.data[i+1][j] + T.data[i+2][j] + T.data[i+3][j] + T.data[i+4][j] ) == 4*color ){
				count ++ ;
				pi = i ; pj = j ;
			}
		}
	}

    pi = 22 ; pj = 22 ;
	for( i = 0 ; i < 11 ; i++ ){    //判断“\”向四
		for( j = 0 ; j < 11 ; j++ ){
			if((i != pi+1 || j != pj+1 ) && T.data[i][j] != anticolor && T.data[i+1][j+1] != anticolor && T.data[i+2][j+2] != anticolor && T.data[i+3][j+3] != anticolor && T.data[i+4][j+4] != anticolor && ( T.data[i][j] + T.data[i+1][j+1] + T.data[i+2][j+2] + T.data[i+3][j+3] + T.data[i+4][j+4] ) == 4*color ){
				count ++ ;
				pi = i ; pj = j ;
			}
		}
	}

	pi = 22 ; pj = 22 ;
	for( i = 0 ; i < 11 ; i++ ){    //判断“/”向四
		for( j = 4 ; j < 15 ; j++ ){
			if((i != pi+1 || j != pj-1 ) && T.data[i][j] != anticolor && T.data[i+1][j-1] != anticolor && T.data[i+2][j-2] != anticolor && T.data[i+3][j-3] != anticolor && T.data[i+4][j-4] != anticolor && ( T.data[i][j] + T.data[i+1][j-1] + T.data[i+2][j-2] + T.data[i+3][j-3] + T.data[i+4][j-4] ) == 4*color ){
				count ++ ;
				pi = i ; pj = j ;
			}
		}
	}

	return count ;
}

/////////////////////////////////////////////////////////////////////////////////////////


int Judge::huosan( Table T )          //    判断“活三”，并返回棋盘中“活三”的个数
{
	int i, j , pi=22 , pj=22 , count = 0 ;
	for( i = 0 ; i < 15 ; i++ ){        //判断横向“活三”
		for( j = 0 ; j < 10 ; j++ ){
			if((i != pi || j != pj+1 ) && T.data[i][j] == 0 && T.data[i][j+1] != anticolor && T.data[i][j+2] != anticolor && T.data[i][j+3] != anticolor && T.data[i][j+4] != anticolor && T.data[i][j+5] == 0 && (T.data[i][j+1] + T.data[i][j+2] + T.data[i][j+3] + T.data[i][j+4]) == 3*color ){
				count ++ ;
				pi = i ; pj = j ;
			}
		}
	}
    
	pi = 22 ; pj = 22 ;
	for( i = 0 ; i < 10 ; i++ ){          //判断纵向“活三”
		for( j = 0 ; j < 15 ; j++ ){
			if((i != pi+1 || j != pj ) && T.data[i][j] == 0 && T.data[i+1][j] != anticolor && T.data[i+2][j] != anticolor && T.data[i+3][j] != anticolor && T.data[i+4][j] != anticolor && T.data[i+5][j] == 0 && (T.data[i+1][j] + T.data[i+2][j] + T.data[i+3][j] + T.data[i+4][j]) == 3*color ){
				count ++ ;
				pi = i ; pj = j ;
			}
		}
	}

    pi = 22 ; pj = 22 ;
	for( i = 0 ; i < 10 ; i++ ){              //判断“\”向“活三”
		for( j = 0 ; j < 10 ; j++ ){
			if((i != pi+1 || j != pj+1 ) && T.data[i][j] == 0 && T.data[i+1][j+1] != anticolor && T.data[i+2][j+2] != anticolor && T.data[i+3][j+3] != anticolor && T.data[i+4][j+4] != anticolor && T.data[i+5][j+5] == 0 && (T.data[i+1][j+1] + T.data[i+2][j+2] + T.data[i+3][j+3] + T.data[i+4][j+4]) == 3*color ){
				count ++ ;
				pi = i ; pj = j ;
			}
		}
	}

    pi = 22 ; pj = 22 ;
	for( i = 0 ; i < 10 ; i++ ){              //判断“/”向“活三”
		for( j = 5 ; j < 15 ; j++ ){
			if((i != pi+1 || j != pj-1 ) && T.data[i][j] == 0 && T.data[i+1][j-1] != anticolor && T.data[i+2][j-2] != anticolor && T.data[i+3][j-3] != anticolor && T.data[i+4][j-4] != anticolor && T.data[i+5][j-5] == 0 && (T.data[i+1][j-1] + T.data[i+2][j-2] + T.data[i+3][j-3] + T.data[i+4][j-4]) == 3*color ){
				count ++ ;
				pi = i ; pj = j ;
			}
		}
	}
	
	return count ;
}

/////////////////////////////////////////////////////////////////////////////////////////









