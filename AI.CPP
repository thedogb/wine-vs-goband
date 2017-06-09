#include "TABLE.H"
#include "JUDGE.H"
#include "AI.H"

Ai::Ai( int k )
{
	color = k ;
	if( k == 1 ) anticolor = 2 ;
	else anticolor = 1 ;
}

int Ai::xiazi( Table T )
{
	int i , j , besti , bestj , maxscore = 0 , sco ;
	if( T.data[7][7] == 0 ){
		cout<<"\t\t\t\t\t电脑落子： 7\t7"<<endl;
		return 707 ;
	}
	else{
		for( i = 0 ; i < 14 ; i++ ){
		    for( j = 0 ; j < 14 ; j++ ){
			    if( T.data[i][j] == 0 ){
				    sco = score( T , i , j ) ;
			        if( maxscore < sco ){
				        maxscore = sco ;
				        besti = i ;
				        bestj = j ;
					}
				}
			}
		}
		cout<<"score：\t\t\t\t\t电脑落子： "<<besti<<"\t"<<bestj<<endl ;
		cout<<maxscore ;
	    return 100*besti + bestj ;
	}
}

int Ai::score( Table T , int i , int j )
{
	int pcscore = 0 , humscore = 0 ;
	int F[2][5] = { { 0, 2, 8, 65, 160000 } , { 0, 10, 34, 750, 160000 } };
	int L[2][5] = { { 0, 1, 6, 45, 5000 } , { 0, 9, 29, 140, 5000 } };
	int num , i1 , j1 , i2 , j2 ;

    Table temp( T ) ;
	temp.set( i , j , 1 ) ;
	Judge tempblack( 1 ) ;

	////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////   电脑落子打分   ///////////////////////////////////

    /////横向打分//////

	num = 1 ;
	i1 = i2 = i ; j1 = j2 = j ;
	while( --j1 >= 0 && T.data[i][j1] == color ) num++ ;
	while( ++j2 <= 14 && T.data[i][j2] == color ) num++ ;

	if( color == 2 ){
		if( num >= 5 ) return F[1][4] ;       // 成五连
	}
	if( color == 1 ){
		if( num > 5 ) return 0 ;        // 成长连
		if( num == 5 ) return F[1][4] ;       // 成五连
	}
		
	if( num == 4 ){
		if( j1 >= 0 && j2 <= 14 && T.data[i][j1] == 0 && T.data[i][j2] == 0 ) pcscore += F[1][3] ;       //  活四
		else if( (j1 >= 0 && T.data[i][j1] == 0) || (j2 <= 14 && T.data[i][j2] == 0) ) pcscore += F[0][3] ;       //   冲四
	}
		
	if( num == 3 ){
		if( j1 >= 0 && j2 <= 14 && T.data[i][j1] == 0 && T.data[i][j2] == 0 ){
			if( (j1-1 >= 0 && T.data[i][j1-1] == color) || (j2+1 <= 14 && T.data[i][j2+1] == color) ){
				pcscore += F[0][3]-2 ;     //  跳四（冲四的一种特殊情况）
				if( (j1-1 >= 0 && T.data[i][j1-1] == color) && (j2+1 <= 14 && T.data[i][j2+1] == color) ) pcscore += F[0][3]-2 ;  //  双跳四
			}
			else{
				if( (j1-1 >= 0 && T.data[i][j1-1] == 0) || (j2+1 <= 14 && T.data[i][j2+1] == 0) ) pcscore += F[1][2] ;    //   活三
				else pcscore += F[0][2] ;    //  冲三
			}
		}
		else{
			if( j1 >= 0 && T.data[i][j1] == 0 ){
				if( j1-1 >= 0 && T.data[i][j1-1] == color ) pcscore += F[0][3]-2 ;     //  跳四
				if( j1-1 >= 0 && T.data[i][j1-1] == 0 ) pcscore += F[0][2] ;     //  冲三
			}
			if( j2 <= 14 && T.data[i][j2] == 0 ){
				if( j2+1 <= 14 && T.data[i][j2+1] == color ) pcscore += F[0][3]-2 ;     //  跳四					
				if( j2+1 <= 14 && T.data[i][j2+1] == 0 ) pcscore += F[0][2] ;     //  冲三
			}
		}
	}

	if( num == 2 ){
		if( j1 >= 0 && T.data[i][j1] == 0 ){
			if( j1-2 >= 0 && T.data[i][j1-1] == color && T.data[i][j1-2] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( j2 <= 14 && T.data[i][j2] == 0 ){
			if( j2+2 <= 14 && T.data[i][j2+1] == color && T.data[i][j2+2] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( j1 >= 0 && j2 <= 14 && T.data[i][j1] == 0 && T.data[i][j2] == 0 ){
			if( j1-2 >= 0 && T.data[i][j1-1] == color &&  T.data[i][j1-2] == 0 ) pcscore += F[1][2]-2 ;     //  活三
			if( j2+2 <= 14 && T.data[i][j2+1] == color &&  T.data[i][j2+2] == 0 ) pcscore += F[1][2]-2 ;     //  活三
			if( (j1-1 >= 0 && T.data[i][j1-1] == 0) || (j2+1 <= 14 && T.data[i][j2+1] == 0) ) pcscore += F[1][1] ;     //  活二
		}
	}

    if( num == 1 ){
		if( j1 >= 0 && T.data[i][j1] == 0 ){
			if( j1-3 >= 0 && T.data[i][j1-1] == color && T.data[i][j1-2] == color && T.data[i][j1-3] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( j2 <= 14 && T.data[i][j2] == 0 ){
			if( j2+3 <= 14 && T.data[i][j2+1] == color && T.data[i][j2+2] == color && T.data[i][j2+3] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( j1 >= 0 && j2 <= 14 && T.data[i][j1] == 0 && T.data[i][j2] == 0 ){
			if( j1-3 >= 0 && T.data[i][j1-1] == color && T.data[i][j1-2] == color && T.data[i][j1-3] == 0 ) pcscore += F[1][2]-2 ;     //  活三
			if( j2+3 <= 14 && T.data[i][j2+1] == color && T.data[i][j2+2] == color && T.data[i][j2+3] == 0 ) pcscore += F[1][2]-2 ;     //  活三
		}
	}


    //////纵向打分//////

	num = 1 ;
	i1 = i2 = i ; j1 = j2 = j ;
	while( --i1 >= 0 && T.data[i1][j1] == color ) num++ ;
	while( ++i2 <= 14 && T.data[i2][j2] == color ) num++ ;

	if( color == 2 ){
		if( num >= 5 ) return F[1][4] ;       // 成五连
	}
	if( color == 1 ){
		if( num > 5 ) return 0 ;        // 成长连
		if( num == 5 ) return F[1][4] ;       // 成五连
	}
		
	if( num == 4 ){
		if( i1 >= 0 && i2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ) pcscore += F[1][3] ;       //  活四
		else if( (i1 >= 0 && T.data[i1][j1] == 0) || (i2 <= 14 && T.data[i2][j2] == 0) ) pcscore += F[0][3] ;       //   冲四
	}
		
	if( num == 3 ){
		if( i1 >= 0 && i2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( (i1-1 >= 0 && T.data[i1-1][j1] == color) || (i2+1 <= 14 && T.data[i2+1][j2] == color) ){
				pcscore += F[0][3]-2 ;     //  跳四（冲四的一种特殊情况）
				if( (i1-1 >= 0 && T.data[i1-1][j1] == color) && (i2+1 <= 14 && T.data[i2+1][j2] == color) ) pcscore += F[0][3]-2 ;     //  双跳四
			}
			else{
				if( (i1-1 >= 0 && T.data[i1-1][j1] == 0) || (i2+1 <= 14 && T.data[i2+1][j2] == 0) ) pcscore += F[1][2] ;    //   活三
				else pcscore += F[0][2] ;    //  冲三
			}
		}
		else{
			if( i1 >= 0 && T.data[i1][j1] == 0 ){
				if( i1-1 >= 0 && T.data[i1-1][j1] == color ) pcscore += F[0][3]-2 ;     //  跳四
				if( i1-1 >= 0 && T.data[i1-1][j1] == 0 ) pcscore += F[0][2] ;     //  冲三
			}
			if( i2 <= 14 && T.data[i2][j2] == 0 ){
				if( i2+1 <= 14 && T.data[i2+1][j2] == color ) pcscore += F[0][3]-2 ;     //  跳四					
				if( i2+1 <= 14 && T.data[i2+1][j2] == 0 ) pcscore += F[0][2] ;     //  冲三
			}
		}
	}

	if( num == 2 ){
		if( i1 >= 0 && T.data[i1][j1] == 0 ){
			if( i1-2 >= 0 && T.data[i1-1][j1] == color && T.data[i1-2][j1] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( i2 <= 14 && T.data[i2][j2] == 0 ){
			if( i2+2 <= 14 && T.data[i2+1][j2] == color && T.data[i2+2][j2] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( i1 >= 0 && i2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( i1-2 >= 0 && T.data[i1-1][j1] == color &&  T.data[i1-2][j1] == 0 ) pcscore += F[1][2]-2 ;     //  活三
			if( i2+2 <= 14 && T.data[i2+1][j2] == color &&  T.data[i2+2][j2] == 0 ) pcscore += F[1][2]-2 ;     //  活三
			if( (i1-1 >= 0 && T.data[i1-1][j1] == 0) || (i2+1 <= 14 && T.data[i2+1][j2] == 0) ) pcscore += F[1][1] ;     //  活二
		}
	}

    if( num == 1 ){
		if( i1 >= 0 && T.data[i1][j1] == 0 ){
			if( i1-3 >= 0 && T.data[i1-1][j1] == color && T.data[i1-2][j1] == color && T.data[i1-3][j1] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( i2 <= 14 && T.data[i2][j2] == 0 ){
			if( i2+3 <= 14 && T.data[i2+1][j2] == color && T.data[i2+2][j2] == color && T.data[i2+3][j2] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( i1 >= 0 && i2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( i1-3 >= 0 && T.data[i1-1][j1] == color && T.data[i1-2][j1] == color && T.data[i1-3][j1] == 0 ) pcscore += F[1][2]-2 ;     //  活三
			if( i2+3 <= 14 && T.data[i2+1][j2] == color && T.data[i2+2][j2] == color && T.data[i2+3][j2] == 0 ) pcscore += F[1][2]-2 ;     //  活三
		}
	}


    //////"\"向打分//////

	num = 1 ;
	i1 = i2 = i ; j1 = j2 = j ;
	while( --i1 >= 0 && --j1 >= 0 && T.data[i1][j1] == color ) num++ ;
	while( ++i2 <= 14 && ++j2 <= 14 && T.data[i2][j2] == color ) num++ ;

	if( color == 2 ){
		if( num >= 5 ) return F[1][4] ;       // 成五连
	}
	if( color == 1 ){
		if( num > 5 ) return 0 ;        // 成长连
		if( num == 5 ) return F[1][4] ;       // 成五连
	}
		
	if( num == 4 ){
		if( i1 >= 0 && i2 <= 14 && j1 >=0 && j2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ) pcscore += F[1][3] ;       //  活四
		else if( (i1 >= 0 && j1 >= 0 && T.data[i1][j1] == 0) || (i2 <= 14 && j2 <= 14 && T.data[i2][j2] == 0) ) pcscore += F[0][3] ;       //   冲四
	}
		
	if( num == 3 ){
		if( i1 >= 0 && i2 <= 14 && j1 >=0 && j2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( (i1-1 >= 0 && j1-1 >= 0 && T.data[i1-1][j1-1] == color) || (i2+1 <= 14 && j2+1 <= 14 && T.data[i2+1][j2+1] == color) ){
				pcscore += F[0][3]-2 ;     //  跳四（冲四的一种特殊情况）
				if( (i1-1 >= 0 && j1-1 >= 0 && T.data[i1-1][j1-1] == color) && (i2+1 <= 14 && j2+1 <= 14 && T.data[i2+1][j2+1] == color) ) pcscore += F[0][3]-2 ;     //  双跳四
			}
			else{
				if( (i1-1 >= 0 && j1-1 >= 0 && T.data[i1-1][j1-1] == 0) || (i2+1 <= 14 && j2+1 <= 14 && T.data[i2+1][j2+1] == 0) ) pcscore += F[1][2] ;    //   活三
				else pcscore += F[0][2] ;    //  冲三
			}
		}
		else{
			if( i1 >= 0 && j1 >= 0 && T.data[i1][j1] == 0 ){
				if( i1-1 >= 0 && j1-1 >= 0 && T.data[i1-1][j1-1] == color ) pcscore += F[0][3]-2 ;     //  跳四
				if( i1-1 >= 0 && j1-1 >= 0 && T.data[i1-1][j1-1] == 0 ) pcscore += F[0][2] ;     //  冲三
			}
			if( i2 <= 14 && j2 <= 14 && T.data[i2][j2] == 0 ){
				if( i2+1 <= 14 && j2+1 <= 14 && T.data[i2+1][j2+1] == color ) pcscore += F[0][3]-2 ;     //  跳四					
				if( i2+1 <= 14 && j2+1 <= 14 && T.data[i2+1][j2+1] == 0 ) pcscore += F[0][2] ;     //  冲三
			}
		}
	}

	if( num == 2 ){
		if( i1 >= 0 && j1 >= 0 && T.data[i1][j1] == 0 ){
			if( i1-2 >= 0 && j1-2 >= 0 && T.data[i1-1][j1-1] == color && T.data[i1-2][j1-2] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( i2 <= 14 && j2 <= 14 && T.data[i2][j2] == 0 ){
			if( i2+2 <= 14 && j2+2 <= 14 && T.data[i2+1][j2+1] == color && T.data[i2+2][j2+2] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( i1 >= 0 && i2 <= 14 && j1 >=0 && j2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( i1-2 >= 0 && j1-2 >= 0 && T.data[i1-1][j1-1] == color &&  T.data[i1-2][j1-2] == 0 ) pcscore += F[1][2]-2 ;     //  活三
			if( i2+2 <= 14 && j2+2 <= 14 && T.data[i2+1][j2+1] == color &&  T.data[i2+2][j2+2] == 0 ) pcscore += F[1][2]-2 ;     //  活三
			if( (i1-1 >=0 && j1-1 >= 0 && T.data[i1-1][j1-1] == 0) || (i2+1 <= 14 && j2+1 <= 14 && T.data[i2+1][j2+1] == 0) ) pcscore += F[1][1] ;     //  活二
		}
	}

    if( num == 1 ){
		if( i1 >= 0 && j1 >= 0 && T.data[i1][j1] == 0 ){
			if( i1-3 >= 0 && j1-3 >= 0 && T.data[i1-1][j1-1] == color && T.data[i1-2][j1-2] == color && T.data[i1-3][j1-3] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( i2 <= 14 && j2 <= 14 && T.data[i2][j2] == 0 ){
			if( i2+3 <= 14 && j2+3 <= 14 && T.data[i2+1][j2+1] == color && T.data[i2+2][j2+2] == color && T.data[i2+3][j2+3] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( i1 >= 0 && i2 <= 14 && j1 >=0 && j2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( i1-3 >= 0 && j1-3 >= 0 && T.data[i1-1][j1-1] == color && T.data[i1-2][j1-2] == color && T.data[i1-3][j1-3] == 0 ) pcscore += F[1][2]-2 ;     //  活三
			if( i2+3 <= 14 && j2+3 <= 14 && T.data[i2+1][j2+1] == color && T.data[i2+2][j2+2] == color && T.data[i2+3][j2+3] == 0 ) pcscore += F[1][2]-2 ;     //  活三
		}
	}



    //////"/"向打分//////

	num = 1 ;
	i1 = i2 = i ; j1 = j2 = j ;
	while( --i1 >= 0 && ++j1 <= 14 && T.data[i1][j1] == color ) num++ ;
	while( ++i2 <= 14 && --j2 >= 0 && T.data[i2][j2] == color ) num++ ;

	if( color == 2 ){
		if( num >= 5 ) return F[1][4] ;       // 成五连
	}
	if( color == 1 ){
		if( num > 5 ) return 0 ;        // 成长连
		if( num == 5 ) return F[1][4] ;       // 成五连
	}
		
	if( num == 4 ){
		if( i1 >= 0 && i2 <= 14 && j1 <=14 && j2 >= 0 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ) pcscore += F[1][3] ;       //  活四
		else if( (i1 >= 0 && j1 <= 14 && T.data[i1][j1] == 0) || (i2 <= 14 && j2 >= 0 && T.data[i2][j2] == 0) ) pcscore += F[0][3] ;       //   冲四
	}
		
	if( num == 3 ){
		if( i1 >= 0 && i2 <= 14 && j1 <= 14 && j2 >= 0 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( (i1-1 >= 0 && j1+1 <= 14 && T.data[i1-1][j1+1] == color) || (i2+1 <= 14 && j2-1 >= 0 && T.data[i2+1][j2-1] == color) ){
				pcscore += F[0][3]-2 ;     //  跳四（冲四的一种特殊情况）
				if( (i1-1 >= 0 && j1+1 <= 14 && T.data[i1-1][j1+1] == color) && (i2+1 <= 14 && j2-1 >= 0 && T.data[i2+1][j2-1] == color) ) pcscore += F[0][3]-2 ;     //  双跳四
			}
			else{
				if( (i1-1 >= 0 && j1+1 <= 14 && T.data[i1-1][j1+1] == 0) || (i2+1 <= 14 && j2-1 >= 0 && T.data[i2+1][j2-1] == 0) ) pcscore += F[1][2] ;    //   活三
				else pcscore += F[0][2] ;    //  冲三
			}
		}
		else{
			if( i1 >= 0 && j1 <= 14 && T.data[i1][j1] == 0 ){
				if( i1-1 >= 0 && j1+1 <= 14 && T.data[i1-1][j1+1] == color ) pcscore += F[0][3]-2 ;     //  跳四
				if( i1-1 >= 0 && j1+1 <= 14 && T.data[i1-1][j1+1] == 0 ) pcscore += F[0][2] ;     //  冲三
			}
			if( i2 <= 14 && j2 >= 0 && T.data[i2][j2] == 0 ){
				if( i2+1 <= 14 && j2-1 >= 0 && T.data[i2+1][j2-1] == color ) pcscore += F[0][3]-2 ;     //  跳四					
				if( i2+1 <= 14 && j2-1 >= 0 && T.data[i2+1][j2-1] == 0 ) pcscore += F[0][2] ;     //  冲三
			}
		}
	}

	if( num == 2 ){
		if( i1 >= 0 && j1 <= 14 && T.data[i1][j1] == 0 ){
			if( i1-2 >= 0 && j1+2 <= 14 && T.data[i1-1][j1+1] == color && T.data[i1-2][j1+2] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( i2 <= 14 && j2 >= 0 && T.data[i2][j2] == 0 ){
			if( i2+2 <= 14 && j2-2 >= 0 && T.data[i2+1][j2-1] == color && T.data[i2+2][j2-2] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( i1 >= 0 && i2 <= 14 && j1 <=14 && j2 >= 0 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( i1-2 >= 0 && j1+2 <= 14 && T.data[i1-1][j1+1] == color &&  T.data[i1-2][j1+2] == 0 ) pcscore += F[1][2]-2 ;     //  活三
			if( i2+2 <= 14 && j2-2 >= 0 && T.data[i2+1][j2-1] == color &&  T.data[i2+2][j2-2] == 0 ) pcscore += F[1][2]-2 ;     //  活三
			if( (i1-1 >= 0 && j1+1 <= 14 && T.data[i1-1][j1+1] == 0) || (i2+1 <=14 && j2-1 >= 0 && T.data[i2+1][j2-1] == 0) ) pcscore += F[1][1] ;     //  活二
		}
	}

    if( num == 1 ){
		if( i1 >= 0 && j1 <= 14 && T.data[i1][j1] == 0 ){
			if( i1-3 >= 0 && j1+3 <= 14 && T.data[i1-1][j1+1] == color && T.data[i1-2][j1+2] == color && T.data[i1-3][j1+3] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( i2 <= 14 && j2 >= 0 && T.data[i2][j2] == 0 ){
			if( i2+3 <= 14 && j2-3 >= 0 && T.data[i2+1][j2-1] == color && T.data[i2+2][j2-2] == color && T.data[i2+3][j2-3] == color )  pcscore += F[0][3]-2 ;     //  跳四
		}
		if( i1 >= 0 && i2 <= 14 && j1 <=14 && j2 >= 0 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( i1-3 >= 0 && j1+3 <= 14 && T.data[i1-1][j1+1] == color && T.data[i1-2][j1+2] == color && T.data[i1-3][j1+3] == 0 ) pcscore += F[1][2]-2 ;     //  活三
			if( i2+3 <= 14 && j2-3 >= 0 && T.data[i2+1][j2-1] == color && T.data[i2+2][j2-2] == color && T.data[i2+3][j2-3] == 0 ) pcscore += F[1][2]-2 ;     //  活三
		}
	}


	if( pcscore > 125 ) pcscore += 500 ;      //   四四 修正
	else{
		if( pcscore > 94 ) pcscore += 80 ;      //   四三 修正
	}



	////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////   玩家落子打分   ///////////////////////////////////

    /////横向打分//////

	num = 1 ;
	i1 = i2 = i ; j1 = j2 = j ;
	while( --j1 >= 0 && T.data[i][j1] == anticolor ) num++ ;
	while( ++j2 <= 14 && T.data[i][j2] == anticolor ) num++ ;

	if( anticolor == 2 ){
		if( num >= 5 ) return L[1][4] ;       // 成五连
	}
	if( anticolor == 1 ){
		if( num > 5 ) humscore = 0 ;        // 成长连
		if( num == 5 ) return L[1][4] ;       // 成五连
	}
		
	if( num == 4 ){
		if( j1 >= 0 && j2 <= 14 && T.data[i][j1] == 0 && T.data[i][j2] == 0 ) humscore += L[1][3] ;       //  活四
		else if( (j1 >= 0 && T.data[i][j1] == 0) || (j2 <= 14 && T.data[i][j2] == 0) ) humscore += L[0][3] ;       //   冲四
	}
		
	if( num == 3 ){
		if( j1 >= 0 && j2 <= 14 && T.data[i][j1] == 0 && T.data[i][j2] == 0 ){
			if( (j1-1 >= 0 && T.data[i][j1-1] == anticolor) || (j2+1 <= 14 && T.data[i][j2+1] == anticolor) ){
				humscore += L[0][3] ;     //  跳四（冲四的一种特殊情况）
				if( (j1-1 >= 0 && T.data[i][j1-1] == anticolor) && (j2+1 <= 14 && T.data[i][j2+1] == anticolor) ) humscore += L[0][3] ;     //  双跳四
			}
			else{
				if( (j1-1 >= 0 && T.data[i][j1-1] == 0) || (j2+1 <= 14 && T.data[i][j2+1] == 0) ) humscore += L[1][2] ;    //   活三
				else humscore += L[0][2] ;    //  冲三
			}
		}
		else{
			if( j1 >= 0 && T.data[i][j1] == 0 ){
				if( j1-1 >= 0 && T.data[i][j1-1] == anticolor ) humscore += L[0][3] ;     //  跳四
				if( j1-1 >= 0 && T.data[i][j1-1] == 0 ) humscore += L[0][2] ;     //  冲三
			}
			if( j2 <= 14 && T.data[i][j2] == 0 ){
				if( j2+1 <= 14 && T.data[i][j2+1] == anticolor ) humscore += L[0][3] ;     //  跳四					
				if( j2+1 <= 14 && T.data[i][j2+1] == 0 ) humscore += L[0][2] ;     //  冲三
			}
		}
	}

	if( num == 2 ){
		if( j1 >= 0 && T.data[i][j1] == 0 ){
			if( j1-2 >= 0 && T.data[i][j1-1] == anticolor && T.data[i][j1-2] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( j2 <= 14 && T.data[i][j2] == 0 ){
			if( j2+2 <= 14 && T.data[i][j2+1] == anticolor && T.data[i][j2+2] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( j1 >= 0 && j2 <= 14 && T.data[i][j1] == 0 && T.data[i][j2] == 0 ){
			if( j1-2 >= 0 && T.data[i][j1-1] == anticolor &&  T.data[i][j1-2] == 0 ) humscore += L[1][2]-2 ;     //  活三
			if( j2+2 <= 14 && T.data[i][j2+1] == anticolor &&  T.data[i][j2+2] == 0 ) humscore += L[1][2]-2 ;     //  活三
			if( (j1-1 >= 0 && T.data[i][j1-1] == 0) || (j2+1 <= 14 && T.data[i][j2+1] == 0) ) humscore += L[1][1] ;     //  活二
		}
	}

    if( num == 1 ){
		if( j1 >= 0 && T.data[i][j1] == 0 ){
			if( j1-3 >= 0 && T.data[i][j1-1] == anticolor && T.data[i][j1-2] == anticolor && T.data[i][j1-3] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( j2 <= 14 && T.data[i][j2] == 0 ){
			if( j2+3 <= 14 && T.data[i][j2+1] == anticolor && T.data[i][j2+2] == anticolor && T.data[i][j2+3] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( j1 >= 0 && j2 <= 14 && T.data[i][j1] == 0 && T.data[i][j2] == 0 ){
			if( j1-3 >= 0 && T.data[i][j1-1] == anticolor && T.data[i][j1-2] == anticolor && T.data[i][j1-3] == 0 ) humscore += L[1][2]-2 ;     //  活三
			if( j2+3 <= 14 && T.data[i][j2+1] == anticolor && T.data[i][j2+2] == anticolor && T.data[i][j2+3] == 0 ) humscore += L[1][2]-2 ;     //  活三
		}
	}


    //////纵向打分//////

	num = 1 ;
	i1 = i2 = i ; j1 = j2 = j ;
	while( --i1 >= 0 && T.data[i1][j1] == anticolor ) num++ ;
	while( ++i2 <= 14 && T.data[i2][j2] == anticolor ) num++ ;

	if( anticolor == 2 ){
		if( num >= 5 ) return L[1][4] ;       // 成五连
	}
	if( anticolor == 1 ){
		if( num > 5 ) humscore = 0 ;        // 成长连
		if( num == 5 ) return L[1][4] ;       // 成五连
	}
		
	if( num == 4 ){
		if( i1 >= 0 && i2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ) humscore += L[1][3] ;       //  活四
		else if( (i1 >= 0 && T.data[i1][j1] == 0) || (i2 <= 14 && T.data[i2][j2] == 0) ) humscore += L[0][3] ;       //   冲四
	}
		
	if( num == 3 ){
		if( i1 >= 0 && i2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( (i1-1 >= 0 && T.data[i1-1][j1] == anticolor) || (i2+1 <= 14 && T.data[i2+1][j2] == anticolor) ){
				humscore += L[0][3] ;     //  跳四（冲四的一种特殊情况）
				if( (i1-1 >= 0 && T.data[i1-1][j1] == anticolor) && (i2+1 <= 14 && T.data[i2+1][j2] == anticolor) ) humscore += L[0][3] ;     //  双跳四
			}
			else{
				if( (i1-1 >= 0 && T.data[i1-1][j1] == 0) || (i2+1 <= 14 && T.data[i2+1][j2] == 0) ) humscore += L[1][2] ;    //   活三
				else humscore += L[0][2] ;    //  冲三
			}
		}
		else{
			if( i1 >= 0 && T.data[i1][j1] == 0 ){
				if( i1-1 >= 0 && T.data[i1-1][j1] == anticolor ) humscore += L[0][3] ;     //  跳四
				if( i1-1 >= 0 && T.data[i1-1][j1] == 0 ) humscore += L[0][2] ;     //  冲三
			}
			if( i2 <= 14 && T.data[i2][j2] == 0 ){
				if( i2+1 <= 14 && T.data[i2+1][j2] == anticolor ) humscore += L[0][3] ;     //  跳四					
				if( i2+1 <= 14 && T.data[i2+1][j2] == 0 ) humscore += L[0][2] ;     //  冲三
			}
		}
	}

	if( num == 2 ){
		if( i1 >= 0 && T.data[i1][j1] == 0 ){
			if( i1-2 >= 0 && T.data[i1-1][j1] == anticolor && T.data[i1-2][j1] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( i2 <= 14 && T.data[i2][j2] == 0 ){
			if( i2+2 <= 14 && T.data[i2+1][j2] == anticolor && T.data[i2+2][j2] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( i1 >= 0 && i2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( i1-2 >= 0 && T.data[i1-1][j1] == anticolor &&  T.data[i1-2][j1] == 0 ) humscore += L[1][2]-2 ;     //  活三
			if( i2+2 <= 14 && T.data[i2+1][j2] == anticolor &&  T.data[i2+2][j2] == 0 ) humscore += L[1][2]-2 ;     //  活三
			if( (i1-1 >= 0 && T.data[i1-1][j1] == 0) || (i2+1 <= 14 && T.data[i2+1][j2] == 0) ) humscore += L[1][1] ;     //  活二
		}
	}

    if( num == 1 ){
		if( i1 >= 0 && T.data[i1][j1] == 0 ){
			if( i1-3 >= 0 && T.data[i1-1][j1] == anticolor && T.data[i1-2][j1] == anticolor && T.data[i1-3][j1] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( i2 <= 14 && T.data[i2][j2] == 0 ){
			if( i2+3 <= 14 && T.data[i2+1][j2] == anticolor && T.data[i2+2][j2] == anticolor && T.data[i2+3][j2] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( i1 >= 0 && i2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( i1-3 >= 0 && T.data[i1-1][j1] == anticolor && T.data[i1-2][j1] == anticolor && T.data[i1-3][j1] == 0 ) humscore += L[1][2]-2 ;     //  活三
			if( i2+3 <= 14 && T.data[i2+1][j2] == anticolor && T.data[i2+2][j2] == anticolor && T.data[i2+3][j2] == 0 ) humscore += L[1][2]-2 ;     //  活三
		}
	}


    //////"\"向打分//////

	num = 1 ;
	i1 = i2 = i ; j1 = j2 = j ;
	while( --i1 >= 0 && --j1 >= 0 && T.data[i1][j1] == anticolor ) num++ ;
	while( ++i2 <= 14 && ++j2 <= 14 && T.data[i2][j2] == anticolor ) num++ ;

	if( anticolor == 2 ){
		if( num >= 5 ) return L[1][4] ;       // 成五连
	}
	if( anticolor == 1 ){
		if( num > 5 ) humscore = 0 ;        // 成长连
		if( num == 5 ) return L[1][4] ;       // 成五连
	}
		
	if( num == 4 ){
		if( i1 >= 0 && i2 <= 14 && j1 >=0 && j2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ) humscore += L[1][3] ;       //  活四
		else if( (i1 >= 0 && j1 >= 0 && T.data[i1][j1] == 0) || (i2 <= 14 && j2 <= 14 && T.data[i2][j2] == 0) ) humscore += L[0][3] ;       //   冲四
	}
		
	if( num == 3 ){
		if( i1 >= 0 && i2 <= 14 && j1 >=0 && j2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( (i1-1 >= 0 && j1-1 >= 0 && T.data[i1-1][j1-1] == anticolor) || (i2+1 <= 14 && j2+1 <= 14 && T.data[i2+1][j2+1] == anticolor) ){
				humscore += L[0][3] ;     //  跳四（冲四的一种特殊情况）
				if( (i1-1 >= 0 && j1-1 >= 0 && T.data[i1-1][j1-1] == anticolor) && (i2+1 <= 14 && j2+1 <= 14 && T.data[i2+1][j2+1] == anticolor) ) humscore += L[0][3] ;     //  双跳四
			}
			else{
				if( (i1-1 >= 0 && j1-1 >= 0 && T.data[i1-1][j1-1] == 0) || (i2+1 <= 14 && j2+1 <= 14 && T.data[i2+1][j2+1] == 0) ) humscore += L[1][2] ;    //   活三
				else humscore += L[0][2] ;    //  冲三
			}
		}
		else{
			if( i1 >= 0 && j1 >= 0 && T.data[i1][j1] == 0 ){
				if( i1-1 >= 0 && j1-1 >= 0 && T.data[i1-1][j1-1] == anticolor ) humscore += L[0][3] ;     //  跳四
				if( i1-1 >= 0 && j1-1 >= 0 && T.data[i1-1][j1-1] == 0 ) humscore += L[0][2] ;     //  冲三
			}
			if( i2 <= 14 && j2 <= 14 && T.data[i2][j2] == 0 ){
				if( i2+1 <= 14 && j2+1 <= 14 && T.data[i2+1][j2+1] == anticolor ) humscore += L[0][3] ;     //  跳四					
				if( i2+1 <= 14 && j2+1 <= 14 && T.data[i2+1][j2+1] == 0 ) humscore += L[0][2] ;     //  冲三
			}
		}
	}

	if( num == 2 ){
		if( i1 >= 0 && j1 >= 0 && T.data[i1][j1] == 0 ){
			if( i1-2 >= 0 && j1-2 >= 0 && T.data[i1-1][j1-1] == anticolor && T.data[i1-2][j1-2] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( i2 <= 14 && j2 <= 14 && T.data[i2][j2] == 0 ){
			if( i2+2 <= 14 && j2+2 <= 14 && T.data[i2+1][j2+1] == anticolor && T.data[i2+2][j2+2] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( i1 >= 0 && i2 <= 14 && j1 >=0 && j2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( i1-2 >= 0 && j1-2 >= 0 && T.data[i1-1][j1-1] == anticolor &&  T.data[i1-2][j1-2] == 0 ) humscore += L[1][2]-2 ;     //  活三
			if( i2+2 <= 14 && j2+2 <= 14 && T.data[i2+1][j2+1] == anticolor &&  T.data[i2+2][j2+2] == 0 ) humscore += L[1][2]-2 ;     //  活三
			if( (i1-1 >=0 && j1-1 >= 0 && T.data[i1-1][j1-1] == 0) || (i2+1 <= 14 && j2+1 <= 14 && T.data[i2+1][j2+1] == 0) ) humscore += L[1][1] ;     //  活二
		}
	}

    if( num == 1 ){
		if( i1 >= 0 && j1 >= 0 && T.data[i1][j1] == 0 ){
			if( i1-3 >= 0 && j1-3 >= 0 && T.data[i1-1][j1-1] == anticolor && T.data[i1-2][j1-2] == anticolor && T.data[i1-3][j1-3] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( i2 <= 14 && j2 <= 14 && T.data[i2][j2] == 0 ){
			if( i2+3 <= 14 && j2+3 <= 14 && T.data[i2+1][j2+1] == anticolor && T.data[i2+2][j2+2] == anticolor && T.data[i2+3][j2+3] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( i1 >= 0 && i2 <= 14 && j1 >=0 && j2 <= 14 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( i1-3 >= 0 && j1-3 >= 0 && T.data[i1-1][j1-1] == anticolor && T.data[i1-2][j1-2] == anticolor && T.data[i1-3][j1-3] == 0 ) humscore += L[1][2]-2 ;     //  活三
			if( i2+3 <= 14 && j2+3 <= 14 && T.data[i2+1][j2+1] == anticolor && T.data[i2+2][j2+2] == anticolor && T.data[i2+3][j2+3] == 0 ) humscore += L[1][2]-2 ;     //  活三
		}
	}



    //////"/"向打分//////

	num = 1 ;
	i1 = i2 = i ; j1 = j2 = j ;
	while( --i1 >= 0 && ++j1 <= 14 && T.data[i1][j1] == anticolor ) num++ ;
	while( ++i2 <= 14 && --j2 >= 0 && T.data[i2][j2] == anticolor ) num++ ;

	if( anticolor == 2 ){
		if( num >= 5 ) return L[1][4] ;       // 成五连
	}
	if( anticolor == 1 ){
		if( num > 5 ) humscore = 0 ;        // 成长连
		if( num == 5 ) return L[1][4] ;       // 成五连
	}
		
	if( num == 4 ){
		if( i1 >= 0 && i2 <= 14 && j1 <=14 && j2 >= 0 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ) humscore += L[1][3] ;       //  活四
		else if( (i1 >= 0 && j1 <= 14 && T.data[i1][j1] == 0) || (i2 <= 14 && j2 >= 0 && T.data[i2][j2] == 0) ) humscore += L[0][3] ;       //   冲四
	}
		
	if( num == 3 ){
		if( i1 >= 0 && i2 <= 14 && j1 <= 14 && j2 >= 0 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( (i1-1 >= 0 && j1+1 <= 14 && T.data[i1-1][j1+1] == anticolor) || (i2+1 <= 14 && j2-1 >= 0 && T.data[i2+1][j2-1] == anticolor) ){
				humscore += L[0][3] ;     //  跳四（冲四的一种特殊情况）
				if( (i1-1 >= 0 && j1+1 <= 14 && T.data[i1-1][j1+1] == anticolor) && (i2+1 <= 14 && j2-1 >= 0 && T.data[i2+1][j2-1] == anticolor) ) humscore += L[0][3] ;     //  双跳四
			}
			else{
				if( (i1-1 >= 0 && j1+1 <= 14 && T.data[i1-1][j1+1] == 0) || (i2+1 <= 14 && j2-1 >= 0 && T.data[i2+1][j2-1] == 0) ) humscore += L[1][2] ;    //   活三
				else humscore += L[0][2] ;    //  冲三
			}
		}
		else{
			if( i1 >= 0 && j1 <= 14 && T.data[i1][j1] == 0 ){
				if( i1-1 >= 0 && j1+1 <= 14 && T.data[i1-1][j1+1] == anticolor ) humscore += L[0][3] ;     //  跳四
				if( i1-1 >= 0 && j1+1 <= 14 && T.data[i1-1][j1+1] == 0 ) humscore += L[0][2] ;     //  冲三
			}
			if( i2 <= 14 && j2 >= 0 && T.data[i2][j2] == 0 ){
				if( i2+1 <= 14 && j2-1 >= 0 && T.data[i2+1][j2-1] == anticolor ) humscore += L[0][3] ;     //  跳四					
				if( i2+1 <= 14 && j2-1 >= 0 && T.data[i2+1][j2-1] == 0 ) humscore += L[0][2] ;     //  冲三
			}
		}
	}

	if( num == 2 ){
		if( i1 >= 0 && j1 <= 14 && T.data[i1][j1] == 0 ){
			if( i1-2 >= 0 && j1+2 <= 14 && T.data[i1-1][j1+1] == anticolor && T.data[i1-2][j1+2] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( i2 <= 14 && j2 >= 0 && T.data[i2][j2] == 0 ){
			if( i2+2 <= 14 && j2-2 >= 0 && T.data[i2+1][j2-1] == anticolor && T.data[i2+2][j2-2] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( i1 >= 0 && i2 <= 14 && j1 <=14 && j2 >= 0 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( i1-2 >= 0 && j1+2 <= 14 && T.data[i1-1][j1+1] == anticolor &&  T.data[i1-2][j1+2] == 0 ) humscore += L[1][2]-2 ;     //  活三
			if( i2+2 <= 14 && j2-2 >= 0 && T.data[i2+1][j2-1] == anticolor &&  T.data[i2+2][j2-2] == 0 ) humscore += L[1][2]-2 ;     //  活三
			if( (i1-1 >= 0 && j1+1 <= 14 && T.data[i1-1][j1+1] == 0) || (i2+1 <=14 && j2-1 >= 0 && T.data[i2+1][j2-1] == 0) ) humscore += L[1][1] ;     //  活二
		}
	}

    if( num == 1 ){
		if( i1 >= 0 && j1 <= 14 && T.data[i1][j1] == 0 ){
			if( i1-3 >= 0 && j1+3 <= 14 && T.data[i1-1][j1+1] == anticolor && T.data[i1-2][j1+2] == anticolor && T.data[i1-3][j1+3] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( i2 <= 14 && j2 >= 0 && T.data[i2][j2] == 0 ){
			if( i2+3 <= 14 && j2-3 >= 0 && T.data[i2+1][j2-1] == anticolor && T.data[i2+2][j2-2] == anticolor && T.data[i2+3][j2-3] == anticolor )  humscore += L[0][3] ;     //  跳四
		}
		if( i1 >= 0 && i2 <= 14 && j1 <=14 && j2 >= 0 && T.data[i1][j1] == 0 && T.data[i2][j2] == 0 ){
			if( i1-3 >= 0 && j1+3 <= 14 && T.data[i1-1][j1+1] == anticolor && T.data[i1-2][j1+2] == anticolor && T.data[i1-3][j1+3] == 0 ) humscore += L[1][2]-2 ;     //  活三
			if( i2+3 <= 14 && j2-3 >= 0 && T.data[i2+1][j2-1] == anticolor && T.data[i2+2][j2-2] == anticolor && T.data[i2+3][j2-3] == 0 ) humscore += L[1][2]-2 ;     //  活三
		}
	}

	if( humscore < 139 ){
		if( humscore > 89 ) humscore += 50 ;      //   四四 修正
		else{
			if( humscore > 73 ) humscore += 60 ;      //   四三 修正
		}
	}



////////////////////////////////     黑棋禁手判断     ////////////////////////////////

    if( color == 1 ){
		if( tempblack.longlink( temp ) ) pcscore = 0 ;
		if( tempblack.si( temp ) > 1 ) pcscore = 0 ;
		if( tempblack.huosan( temp ) > 1 ) pcscore = 0 ;
		return pcscore + humscore ;
	}
	else{
		if( tempblack.longlink( temp ) ) humscore = 0 ;
		if( tempblack.si( temp ) > 1 ) humscore = 0 ;
		if( tempblack.huosan( temp ) > 1 ) humscore = 0 ;
		return pcscore + humscore ;
	}


}