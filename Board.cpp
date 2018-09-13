#include <stdlib.h>

#include "Board.h"



// class Point{
// 	int x;
// 	int y;
// 	public:
// 	int getx(){
// 		return this.x;
// 	}
// 	int gety(){
// 		return this.x;	
// 	}
// 	void setx(int x1){
// 		this.x = x1;
// 	}
// 	void sety(int y1){
// 		this.y = y1;
// 	}

// }


int Point::getx(){
		return this->x;
	}
int Point::gety(){
		return this->y;	
	}
void Point::setx(int x1){
		this->x = x1;
	}
void Point::sety(int y1){
		this->y = y1;
	}




Point twod_from_hex (Point p){
		int h = p.getx();  // the hexagon number. center point is hexagon numbered 0.
		int c = p.gety();  // the point clockwise, first being 0.
		Point twod;
		if(c <= h){
			twod.setx(5+c);
			twod.sety(5+h);
		}
		else if(c<=2*h){
			twod.setx(5+h);
			twod.sety(5+2*h-c);
		}
		else if(c<=3*h){
			twod.setx(5+3*h-c);
			twod.sety(5-h+3*h-c);
		}
		else if(c<=4*h){
			twod.setx(5-(c-3*h));
			twod.sety(5-h);
		}
		else if(c<=5*h){
			twod.setx(5-h);
			twod.sety(5-h+c-4*h);
		}
		else{
			twod.setx(5-h+c-5*h);
			twod.sety(5+c-5*h);
		}

	// Point out;
	// out.setx(h);
	// out.sety(c);
	return twod;

}


Point hex_from_twod (Point p){
	int px = p.getx();
	int py = p.gety();
	int h = max(abs(px-5),abs(py-5));  
	int c;

	if(py == 5+h){
		c=px-5;	
	}
	else if(px == 5+h){
		c = 2*h - (py-5);
	}
	else if(py == 5-h){
		c = 3*h + 5-px; 
	}
	else if(px == 5-h ){
		c= 5*h - (5-py);
	}
	else if(px >= 5 && py <= 5){
		c= 3*h - (px-5);
	}
	else if(px <= 5 && py >= 5){
		c= 6*h - (5-px);
	}
	Point out;
	out.setx(h);
	out.sety(c);
	return out;
}



Board::Board ( )
{	

    // int boardArray [11] [11];
    // bool validArray [11] [11];

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

// Board::Board ( int sessionsInTrack )
// {
//     this->sessionsInTrack = sessionsInTrack;
//     sessions = ( Session * ) malloc ( sizeof (Session ) * sessionsInTrack );
// }



void Board::setRing(int ringcolor,int px, int py){

	if(boardArray[px][py] == -1 && validArray[px][py] == true )  
		{	boardArray[px][py] == ringcolor;
			validArray[px][py] == false;       // CHECK THIS !!!!!!!
		}

}


void Board::moveRing(int ringcolor, int from_x, int from_y, int to_x, int to_y){

	// 	ASSUMING THAT THE TO AND FROM COORDINATES ARE VALID.
	boardArray[from_x][from_y] == ringcolor +2;
	boardArray [to_x][to_y] == ringcolor;
	validArray[from_x][from_y] == false;
	validArray[to_x][to_y] == false;

	if(from_x == to_x){
		int miy = from_y,mxy  = to_y;
		if(from_y>to_y){miy = to_y; mxy = from_y;}  
		for(int i = miy+1; i< mxy ;i++){
			if (boardArray[from_x][i] != -1 ) boardArray[from_x][i] = 5-boardArray[from_x][i]; // CHECK THIS IF CONDITION
		}
	}

	else if(from_y == to_y){
		int mix = from_x,mxx  = to_x;
		if(from_x>to_x){mix = to_x; mxx = from_x;}  
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


Point Board::twod_from_hex (Point p){
		int h = p.getx();  // the hexagon number. center point is hexagon numbered 0.
		int c = p.gety();  // the point clockwise, first being 0.
		Point twod;
		if(c <= h){
			twod.setx(5+c);
			twod.sety(5+h);
		}
		else if(c<=2*h){
			twod.setx(5+h);
			twod.sety(5+2*h-c);
		}
		else if(c<=3*h){
			twod.setx(5+3*h-c);
			twod.sety(5-h+3*h-c);
		}
		else if(c<=4*h){
			twod.setx(5-(c-3*h));
			twod.sety(5-h);
		}
		else if(c<=5*h){
			twod.setx(5-h);
			twod.sety(5-h+c-4*h);
		}
		else{
			twod.setx(5-h+c-5*h);
			twod.sety(5+c-5*h);
		}

	// Point out;
	// out.setx(h);
	// out.sety(c);
	return twod;

}


Point Board::hex_from_twod (Point p){
	int px = p.getx();
	int py = p.gety();
	int h = max(abs(px-5),abs(py-5));  
	int c;

	if(py == 5+h){
		c=px-5;	
	}
	else if(px == 5+h){
		c = 2*h - (py-5);
	}
	else if(py == 5-h){
		c = 3*h + 5-px; 
	}
	else if(px == 5-h ){
		c= 5*h - (5-py);
	}
	else if(px >= 5 && py <= 5){
		c= 3*h - (px-5);
	}
	else if(px <= 5 && py >= 5){
		c= 6*h - (5-px);
	}
	Point out;
	out.setx(h);
	out.sety(c);
	return out;
}


void Board::getNeighbours(int px,int py, int ringcolor){

	
}





