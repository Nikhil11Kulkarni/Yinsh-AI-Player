#include <stdlib.h>

#include "Board.h"


Board::Board ( )
{	

    int boardArray [11] [11];
    bool validArray [11] [11];

    // refer to the coordinate system : a,b,c... are represented by the first dimension of the array.
    for(int i = 0;i<=10;i++){
    	for(int j =0;j<10;j++){
    		validArray[i][j] = false;
    	}
    }


    for(int j =2; j<=5;j++){
    	validArray[0][j] = true;
    }
    for(int j =1; j<=7;j++){
    	validArray[1][j] = true;
    }
    for(int j =1; j<=8;j++){
    	validArray[2][j] = true;
    }
    for(int j =1; j<=9;j++){
    	validArray[3][j] = true;
    }
    for(int j =1; j<=10;j++){
    	validArray[4][j] = true;
    }
    for(int j =2; j<=10;j++){
    	validArray[5][j] = true;
    }
    for(int j =2; j<=11;j++){
    	validArray[6][j] = true;
    }
    for(int j =3; j<=11;j++){
    	validArray[7][j] = true;
    }
    for(int j =4; j<=11;j++){
    	validArray[8][j] = true;
    }
    for(int j =5; j<=11;j++){
    	validArray[9][j] = true;
    }
    for(int j =7; j<=10;j++){
    	validArray[10][j] = true;
    }
 


}

Board::Board ( int sessionsInTrack )
{
    this->sessionsInTrack = sessionsInTrack;
    sessions = ( Session * ) malloc ( sizeof (Session ) * sessionsInTrack );
}



void Board::setRing(int ringcolor,int px, int py){

	if(boardArray[px][py] == -1 && validArray[px][py] == true )  
		{	boardArray[px][py] == ringcolor;
			validArray[px][py] == false;       // CHECK THIS !!!!!!!
		}

}


void Board::moveRing(int ringcolor, int from_x,int form-y, int to_x,int to_y){

	// 	ASSUMING THAT THE TO AND FROM COORDINATES ARE VALID.
	boardArray[from_x][from_y] == ringcolor +2;
	boardArray [to_x][to_y] == ringcolor;
	validArray[from_x][from_y] == false;
	validArray[to_x][to_y] == false;

	if(from_x == to_x){
		int miy = from_y,mxy  = to_y;
		if(from_y>to_y){miy = to_y; mxy = from_y}  
		for(int i = miy+1; i< mxy ;i++){
			if (boardArray[from_x][i] != -1 ) boardArray[from_x][i] = 5-boardArray[from_x][i]; // CHECK THIS IF CONDITION
		}
	}

	else if(from_y == to_y){
		int mix = from_x,mxx  = to_x;
		if(from_x>to_x){mix = to_x; mxx = from_x}  
		for(int i = mix+1; i< mxx ;i++){
			if (boardArray[i][from_y] != -1 ) boardArray[i][from_y] = 5-boardArray[i][from_y]; 
		}
	}

	else{
		if(from_x < to_x){
		int s = to_x - from_x ;
		for(int i = 1; i< s ;i++){
			if (boardArray[from_x+i][from_y+i] != -1 ) boardArray[from_x+i][from_y+i] = 5-boardArray[from_x+i][from_y+i]; 
		}
		}

		else{
		int s =from_x -  to_x ;
		for(int i = 1; i< s ;i++){
			if (boardArray[from_x-i][from_y-i] != -1 ) boardArray[from_x-i][from_y-i] = 5-boardArray[from_x-i][from_y-i]; 
		}
		}
	}

}





void Board::getNeighbours(int px,int py, int ringcolor){

	
}





