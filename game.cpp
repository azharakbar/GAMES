#include <iostream>
#include <windows.h>
#include <ctime>
#include <stdlib.h>

using namespace std ;

struct c
{
	int data ;
	int mine ;

	c()
	{
		data = -1 ;
		mine = -1 ;
	}
};

c cell[50][50] ;

void printGrid ( int size , int type = 0 ) 
{
	int i = 0 , j = 0 ;

	if ( type == 0 )
		for ( i = 0; i < size; ++i)
		{
			for ( j = 0; j < size ; ++j)
				{
					if ( cell[i][j].data >= 0 )
						cout << " " << cell[i][j].data << " " ;
					else
						cout << " X " ;
				}	
				cout << endl ;
		}

	else
		for ( i = 0; i < size; ++i)
		{
			for ( j = 0; j < size ; ++j)
				{
					if ( cell[i][j].data >= 0 )
						cout << " " << cell[i][j].data << " " ;
					else if ( cell[i][j].mine == 1 )
						cout << " M " ;
					else
						cout << " X " ;
				}	
				cout << endl ;
		}		
}

int calcData ( int cellX , int cellY , int size )
{
	int mineFound = 0 ;

	if ( cellX-1 >= 0 && cellY-1 >= 0 )
	{
		if ( cell[cellX-1][cellY-1].mine == 1 )
			++mineFound ;
	}

	if ( cellX-1 >= 0  )
	{
		if ( cell[cellX-1][cellY].mine == 1 )
			++mineFound ;
	}	

	if ( cellY-1 >= 0 )
	{
		if ( cell[cellX][cellY-1].mine == 1 )
			++mineFound ;
	}	

	if ( cellX+1 < size && cellY+1 < size )
	{
		if ( cell[cellX+1][cellY+1].mine == 1 )
			++mineFound ;
	}	

	if ( cellX+1 < size  )
	{
		if ( cell[cellX+1][cellY].mine == 1 )
			++mineFound ;
	}	

	if ( cellY+1 < size )
	{
		if ( cell[cellX][cellY+1].mine == 1 )
			++mineFound ;
	}		

	if ( cellX+1 < size && cellY-1 >= 0 )
	{
		if ( cell[cellX+1][cellY-1].mine == 1 )
			++mineFound ;
	}		

	if ( cellX-1 >= 0 && cellY+1 < size )
	{
		if ( cell[cellX-1][cellY+1].mine == 1 )
			++mineFound ;
	}		

	return mineFound ;

}

int main(int argc, char const *argv[])
{
	int size = 0 , mines = 0 ;

	do
	{	
		system ( "cls" ) ;
		cout << endl << " ----- MINESWEEPER ----- " << endl << endl ; 
		cout << " >> Enter The Size Of Grid : " ;
		cin  >> size ;

		cout << " >> Enter The No. Of Mines : " ;
		cin >> mines ;
	} while ( size < 5 && mines >= size*size ) ;

	

	srand(time(NULL));
	int x = 0 ; 
	int y = 0 ;
	int installed = 0 ;

	while ( installed < mines )
	{
		x = ( rand() % size ) ;
		y = ( rand() % size ) ;
		if ( !installed )
			cell[x][y].mine = 1 ;
		else
		{
			if ( cell[x][y].mine != 1 )
				cell[x][y].mine = 1 ;
			else
				continue ;
		}
		//cout << x << " " << y  << endl ;
		++installed ;
	}

	int opened = 0 ;
	int availed = ( size*size ) - mines ;
	int cellno = 0 ;
	int i = 0 , j = 0 ;

	while ( opened < availed )
	{
		system ( "cls" ) ;

		cout << endl << endl ;
		printGrid ( size ) ;
		cout << endl << endl ;
		cout << " Enter any 'X' marked cell to open : " ; 
		cin  >> cellno ;
		--cellno ;

		int cellX = 0 , cellY = 0 ;

		x = -1 ;

		for ( i = 0; i < size; ++i)
		{
			for ( j = 0; j < size ; ++j)
				{
					++x ;
					if ( x == cellno )
						break ;
				}	
			if ( x == cellno )
				break ;				
		}

		cellX = i ;
		cellY = j ;

		if ( cell[cellX][cellY].mine == 1 )
		{
			printGrid ( size , 1 ) ;
			cout << endl << endl << " *** FAILED *** " << endl ;
			return 0 ;
		}
		else
			cell[cellX][cellY].data = calcData ( cellX , cellY , size ) ;

		++opened ;
	}

	cout << " *-*-*-*-*-*-* YOU WON *-*-*-*-*-*-*-* " << endl ;

	return 0;
}