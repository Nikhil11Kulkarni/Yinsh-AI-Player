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
void Point::set(int x1,int y1){
		this->x = x1; this->y = y1;
	}
string Point::getxystring(){
	string var="";
	var=var+to_string(this->x);
	var=var+" ";
	var=var+to_string(this->y);
	return var;
	}	

string Point::getHexagonPositionString(){
	Point p2;
	Point p1;
	p1.set(this->x , this->y);
	p2=hex_from_twod(p1);
	string var="";
	var=var+to_string(p2.getx());
	var=var+" ";
	var=var+to_string(p2.gety());
	return var;
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
	int h;
	if(px<=5 && py>=5)h=py-px;
	else if(py<=5&&py>=5) h=px-py;
	else h = max(abs(px-5),abs(py-5));   
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
	for(int i=0;i<4;i++)
	this->action[i]=-1;
	this->numberOfRings[0]=0;
	this->numberOfRings[1]=0;
    // refer to the coordinate system : a,b,c... are represented by the first dimension of the array.
	this->numberOfRings[0]=0;
	this->numberOfRings[0]=0;
	
    for(int i = 0;i<=10;i++){
    	for(int j =0;j<=10;j++){
    		boardArray[i][j] = -1;
    	}
    }

    for(int i = 0;i<=10;i++){
    	for(int j =0;j<=10;j++){
    		validArray[i][j] = false;
    		validBoardArray[i][j]=false;
    	}
    }



    for(int j =1; j<=4;j++){
    	validArray[0][j] = true;
	    validBoardArray[0][j]=true;
    }
    for(int j =0; j<=6;j++){
    	validArray[1][j] = true;
	    validBoardArray[1][j]=true;
    }
    for(int j =0; j<=7;j++){
    	validArray[2][j] = true;
	    validBoardArray[2][j]=true;
    }
    for(int j =0; j<=8;j++){
    	validArray[3][j] = true;
	    validBoardArray[3][j]=true;
    }
    for(int j =0; j<=9;j++){
    	validArray[4][j] = true;
	    validBoardArray[4][j]=true;
    }
    for(int j =1; j<=9;j++){
    	validArray[5][j] = true;
	    validBoardArray[5][j]=true;
    }
    for(int j =1; j<=10;j++){
    	validArray[6][j] = true;
 	    validBoardArray[6][j]=true;
    }
    for(int j =2; j<=10;j++){
    	validArray[7][j] = true;
  	    validBoardArray[7][j]=true;
    }
    for(int j =3; j<=10;j++){
    	validArray[8][j] = true;
	    validBoardArray[8][j]=true;
    }
    for(int j =4; j<=10;j++){
    	validArray[9][j] = true;
	    validBoardArray[9][j]=true; 
    }
    for(int j =6; j<=9;j++){
    	validArray[10][j] = true;
	    validBoardArray[10][j]=true;
    }
}


Board Board::clone(){
	Board newboard;
newboard.boardsize = this->boardsize;
newboard.numberOfRings[0] = this-> numberOfRings[0];
newboard.numberOfRings[1] = this-> numberOfRings[1];
newboard.myIDboard = this->myIDboard;
newboard.opponentIDboard=this->opponentIDboard;

	for(int i=0;i<this->myringPositions.size();i++){
		Point p1; p1.set(this->myringPositions[i].getx() , this->myringPositions[i].gety());
		newboard.myringPositions.push_back(p1);
	}
	
	for(int i=0;i<this->opponentringPositions.size();i++){
		Point p1; p1.set(this->opponentringPositions[i].getx() , this->opponentringPositions[i].gety());
		newboard.opponentringPositions.push_back(p1);
	}

	for(int i = 0;i<=10;i++){
    	for(int j =0;j<=10;j++){
    		newboard.boardArray[i][j] = this->boardArray[i][j] ;
    		newboard.validArray[i][j] = this->validArray[i][j] ;
    	}
    }
    return newboard;
}
// int boardsize = 11;
// int numberOfRings[2];
// int myIDboard,opponentIDboard;
// std::vector<Point> myringPositions, opponentringPositions;
// int boardArray [11] [11];
// bool validArray [11] [11];
// int action[4];



void Board::setmyRing(int ringcolor,int px, int py){
// if(ringcolor == opponentID){
// 	Point p1;
// 	p1.set(px,py);
// 	Point p2=twod_from_hex(p1);
// 	px=p2.getx();
// 	py=p2.gety();
//	cerr<<" px:"<<px<<" py:"<<py<<endl;
// 	}
	Point p1; p1.set( px, py);
	if(ringcolor==myIDboard)this->myringPositions.push_back(p1);
	if(ringcolor==opponentIDboard)this->opponentringPositions.push_back(p1);
	
	if(boardArray[px][py] == -1 && validArray[px][py] == true )  
		{	boardArray[px][py] = ringcolor;
			validArray[px][py] = false;       // CHECK THIS !!!!!!!
			this->numberOfRings[ringcolor] ++; 
		}

}


void Board::setRing(int ringcolor,int px, int py){

	Point p1;
	p1.set(px,py);
	Point p2=twod_from_hex(p1);
	px=p2.getx();
	py=p2.gety();
	cerr<<"opponent- px:"<<px<<" py:"<<py<<endl;

	Point ptoadd; ptoadd.set( px, py);
	if(ringcolor==myIDboard)this->myringPositions.push_back(ptoadd);
	if(ringcolor==opponentIDboard)this->opponentringPositions.push_back(ptoadd);

	if(boardArray[px][py] == -1 && validArray[px][py] == true )  
		{	boardArray[px][py] = ringcolor;
			validArray[px][py] = false;       // CHECK THIS !!!!!!!
			this->numberOfRings[ringcolor] ++; 
		}

}

void Board::updateRingPosition(int ringcolor ,int from_x, int from_y, int to_x, int to_y ){
	Point ptoadd; ptoadd.set( to_x, to_y);
	if(ringcolor==myIDboard){ 
		for(int i=0;i<this->myringPositions.size();i++){
			if(this->myringPositions[i].getx() == from_x && this->myringPositions[i].gety() == from_y){
				this->myringPositions.erase(this->myringPositions.begin()+i );break; }
		}
		this->myringPositions.push_back(ptoadd);
	}
	
	if(ringcolor==opponentIDboard){
		for(int i=0;i<this->opponentringPositions.size();i++){
			if(this->opponentringPositions[i].getx() == from_x && this->opponentringPositions[i].gety() == from_y){
				this->opponentringPositions.erase(this->opponentringPositions.begin()+i );break; }
		}
		this->opponentringPositions.push_back(ptoadd);
	}


}

void Board::moveRing(int ringcolor, int from_x, int from_y, int to_x, int to_y){

	// 	ASSUMING THAT THE TO AND FROM COORDINATES ARE VALID.
	Point p1,p2;
	p1.set(from_x,from_y);
	p2.set(to_x,to_y);
	Point p1changed=twod_from_hex(p1);
	Point p2changed=twod_from_hex(p2);
	
	from_x = p1changed.getx(); 
	from_y = p1changed.gety();
	to_x = p2changed.getx(); 
	to_y = p2changed.gety();
	
	cerr<<"opp-from_x:"<<from_x<<" from_y:"<<from_y<<" to_x:"<<to_x<<" to_y:"<<to_y<<endl;

	this->updateRingPosition(ringcolor ,from_x,  from_y, to_x, to_y );

	boardArray[from_x][from_y] = ringcolor +2;
	boardArray [to_x][to_y] = ringcolor;
	validArray[from_x][from_y] = false;
	validArray[to_x][to_y] = false;

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



void Board::moveMyRing(int ringcolor, int from_x, int from_y, int to_x, int to_y){

	// 	ASSUMING THAT THE TO AND FROM COORDINATES ARE VALID.

		
	this->updateRingPosition(ringcolor ,from_x,  from_y, to_x, to_y ); //ASSUMING from_x from_y to_x to_y are all in TWOD form.

	boardArray[from_x][from_y] = ringcolor +2;
	boardArray [to_x][to_y] = ringcolor;
	validArray[from_x][from_y] = false;
	validArray[to_x][to_y] = false;

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

void Board::setID( int id1,int id2){
	this->myIDboard=id1;
	this->opponentIDboard=id2;
}


Point Board::hex_from_twod (Point p){
	int px = p.getx();
	int py = p.gety();
	int h;
	if(px<=5 && py>=5)h=py-px;
	else if(py<=5&&py>=5) h=px-py;
	else h = max(abs(px-5),abs(py-5));   
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

void Board::setAction(int from_x,int from_y, int to_x,int to_y){
	this->action[0]=from_x;this->action[1]=from_y;this->action[2]=to_x;this->action[3]=to_y;
}


vector<Board> Board::getNeighbours1(int px,int py, int ringcolor){
	// cout<<"in neighbours1"<<endl;
	vector <Board> neighbours;
// in direction 0
	bool dir0=true;
	int flag =0;int i=1;
	while(py+i<=10 && validBoardArray[px][py+i]==true && dir0==true ){
		// cout<<"in direction 0 "<<endl;
		if(flag==0){
			if(boardArray[px][py+i]==-1 && validBoardArray[px][py+i]==true){//space
				Board b = this->clone();
			  	b.moveMyRing(ringcolor,px,py,px,py+i);
			    b.setAction(px,py,px,py+i);
			    neighbours.push_back(b);
				i++;
			}
			else if(validBoardArray[px][py+i]==false){dir0=false ;break;}//invalid
			else if((boardArray[px][py+i]==0 || boardArray[px][py+i]==1)&&validBoardArray[px][py+i]==true){dir0=false;break;}//rings
			else if((boardArray[px][py+i]==2 || boardArray[px][py+i]==3)&& validBoardArray[px][py+i]==true){flag=1; i++;}//markers
		}
		else if(flag==1){
			if(boardArray[px][py+i]==-1 && validBoardArray[px][py+i]==true){//space
				Board b = this->clone();
			  	b.moveMyRing(ringcolor,px,py,px,py+i);
			    b.setAction(px,py,px,py+i);
			    neighbours.push_back(b);			
			    dir0=false ;
				break;
			}
			else if(validBoardArray[px][py+i]==false){dir0=false ;break;}//invalid
			else if((boardArray[px][py+i]==0 || boardArray[px][py+i]==1)&&validBoardArray[px][py+i]==true){dir0=false ;break;}//rings
			else if((boardArray[px][py+i]==2 || boardArray[px][py+i]==3)&& validBoardArray[px][py+i]==true){flag=1; i++;}//markers
		}

	}
// in direction 1
	flag =0; i=1;
	bool dir1=true;
	while(px+i<=10 && py+i<=10 && validBoardArray[px+i][py+i]==true && dir1==true){
		// cout<<"in direction 1 "<<endl;
		if(flag==0){
			if(boardArray[px+i][py+i]==-1 && validBoardArray[px+i][py+i]==true){//space
				// cout<<"in IF -1 FLAG 0 i:"<<i<<" px+i:"<<px+i<<" py+i:"<<py+i<<endl;
				Board b = this->clone();
			  	b.moveMyRing(ringcolor,px,py,px+i,py+i);
			    b.setAction(px,py,px+i,py+i);
			    neighbours.push_back(b);
				i++;
			}
			else if(validBoardArray[px+i][py+i]==false){dir1=false ; break;}//invalid
			else if((boardArray[px+i][py+i]==0 || boardArray[px+i][py+i]==1)&&validBoardArray[px+i][py+i]==true){dir1=false ;break;}//rings
			else if((boardArray[px+i][py+i]==2 || boardArray[px+i][py+i]==3)&& validBoardArray[px+i][py+i]==true){flag=1; i++;}//markers
		}
		else if(flag==1){
			if(boardArray[px+i][py+i]==-1 && validBoardArray[px+i][py+i]==true){//space
				//cout<<"in IF -1 FLAG 1 "<<endl;
				Board b = this->clone();
			  	b.moveMyRing(ringcolor,px,py,px+i,py+i);
			    b.setAction(px,py,px+i,py+i);
			    neighbours.push_back(b);			
				dir1=false ;break;
			}
			else if(validBoardArray[px+i][py+i]==false){dir1=false ;break;}//invalid cout<<"in IF VALID FLAG 1 "<<endl;
			else if((boardArray[px+i][py+i]==0 || boardArray[px+i][py+i]==1)&&validBoardArray[px+i][py+i]==true){dir1=false ;break;}//rings
			else if((boardArray[px+i][py+i]==2 || boardArray[px+i][py+i]==3)&& validBoardArray[px+i][py+i]==true){flag=1; i++;}//markers
		}

	}
// in dirrection 2
	bool dir2=true;
	flag =0;i=1;
	while(px+i<=10 && validBoardArray[px+i][py]==true && dir2==true){
		// cout<<"in direction 2 "<<endl;
		if(flag==0){
			if(boardArray[px+i][py]==-1 && validBoardArray[px+i][py]==true){//space
				Board b = this->clone();
			  	b.moveMyRing(ringcolor,px,py,px+i,py);
			    b.setAction(px,py,px+i,py);
			    neighbours.push_back(b);
				i++;
			}
			else if(validBoardArray[px+i][py]==false){dir2=false;break;}//invalid
			else if((boardArray[px+i][py]==0 || boardArray[px+i][py]==1)&&validBoardArray[px+i][py]==true){dir2=false;break;}//rings
			else if((boardArray[px+i][py]==2 || boardArray[px+i][py]==3)&&validBoardArray[px+i][py]==true){flag=1; i++;}//markers
		}
		else if(flag==1){
			if(boardArray[px+i][py]==-1 && validBoardArray[px+i][py]==true){//space
				Board b = this->clone();
			  	b.moveMyRing(ringcolor,px,py,px+i,py);
			    b.setAction(px,py,px+i,py);
			    neighbours.push_back(b);	
			    dir2=false;		
				break;
			}
			else if(validBoardArray[px+i][py]==false){dir2=false;break;}//invalid
			else if((boardArray[px+i][py]==0 || boardArray[px+i][py]==1)&&validBoardArray[px+i][py]==true){dir2=false;break;}//rings
			else if((boardArray[px+i][py]==2 || boardArray[px+i][py]==3)&&validBoardArray[px+i][py]==true){flag=1; i++;}//markers
		}

	}
// in direction 3
	flag =0; i=1;
	bool dir3=true;
	while(py-i>=0 && validBoardArray[px][py-i]==true && dir3==true){
		// cout<<"in direction 3 "<<endl;
		if(flag==0){
			if(boardArray[px][py-i]==-1 && validBoardArray[px][py-i]==true){//space
				Board b = this->clone();
			  	b.moveMyRing(ringcolor,px,py,px,py-i);
			    b.setAction(px,py,px,py-i);
			    neighbours.push_back(b);
				i++;
			}
			else if(validBoardArray[px][py-i]==false){dir3=false;break;}//invalid
			else if((boardArray[px][py-i]==0 || boardArray[px][py-i]==1)&&validBoardArray[px][py-i]==true){dir3=false;break;}//rings
			else if((boardArray[px][py-i]==2 || boardArray[px][py-i]==3)&&validBoardArray[px][py-i]==true){flag=1; i++;}//markers
		}
		else if(flag==1){
			if(boardArray[px][py-i]==-1 && validBoardArray[px][py-i]==true){//space
				Board b = this->clone();
			  	b.moveMyRing(ringcolor,px,py,px,py-i);
			    b.setAction(px,py,px,py-i);
			    neighbours.push_back(b);			
			    dir3=false;
				break;
			}
			else if(validBoardArray[px][py-i]==false){dir3=false;break;}//invalid
			else if((boardArray[px][py-i]==0 || boardArray[px][py-i]==1)&&validBoardArray[px][py-i]==true){dir3=false;break;}//rings
			else if((boardArray[px][py-i]==2 || boardArray[px][py-i]==3)&&validBoardArray[px][py-i]==true){flag=1; i++;}//markers
		}

	}
// in direction 4
	bool dir4=true;
	flag =0;i=1;
	while(px-i>=0 && py-i>=0 && validBoardArray[px-i][py-i]==true && dir4==true){
		// cout<<"in direction 4 "<<endl;
		if(flag==0){
			if(boardArray[px-i][py-i]==-1 && validBoardArray[px-i][py-i]==true){//space
				Board b = this->clone();
			  	b.moveMyRing(ringcolor,px,py,px-i,py-i);
			    b.setAction(px,py,px-i,py-i);
			    neighbours.push_back(b);
				i++;
			}
			else if(validBoardArray[px-i][py-i]==false){dir4=false;break;}//invalid
			else if((boardArray[px-i][py-i]==0 || boardArray[px-i][py-i]==1)&&validBoardArray[px-i][py-i]==true){dir4=false;break;}//rings
			else if((boardArray[px-i][py-i]==2 || boardArray[px-i][py-i]==3)&&validBoardArray[px-i][py-i]==true){flag=1; i++;}//markers
		}
		else if(flag==1){
			if(boardArray[px-i][py-i]==-1 && validBoardArray[px-i][py-i]==true){//space
				Board b = this->clone();
			  	b.moveMyRing(ringcolor,px,py,px-i,py-i);
			    b.setAction(px,py,px-i,py-i);
			    neighbours.push_back(b);			
			    dir4=false;
				break;
			}
			else if(validBoardArray[px-i][py-i]==false){dir4=false;break;}//invalid
			else if((boardArray[px-i][py-i]==0 || boardArray[px-i][py-i]==1)&&validBoardArray[px-i][py-i]==true){dir4=false;break;}//rings
			else if((boardArray[px-i][py-i]==2 || boardArray[px-i][py-i]==3)&&validBoardArray[px-i][py-i]==true){flag=1; i++;}//markers
		}

	}
// in direction 5
	bool dir5=true;
	flag =0;i=1;
	while(px-i>=0 && validBoardArray[px-i][py]==true && dir5==true){
		// cout<<"in direction 5 "<<endl;
		if(flag==0){
			if(boardArray[px-i][py]==-1 && validBoardArray[px-i][py]==true){//space
				Board b = this->clone();
			  	b.moveMyRing(ringcolor,px,py,px-i,py);
			    b.setAction(px,py,px-i,py);
			    neighbours.push_back(b);
				i++;
			}
			else if(validBoardArray[px-i][py]==false){dir5=false;break;}//invalid
			else if((boardArray[px-i][py]==0 || boardArray[px-i][py]==1)&&validBoardArray[px-i][py]==true){dir5=false;break;}//rings
			else if((boardArray[px-i][py]==2 || boardArray[px-i][py]==3)&&validBoardArray[px-i][py]==true){flag=1; i++;}//markers
		}
		else if(flag==1){
			if(boardArray[px-i][py]==-1 && validBoardArray[px-i][py]==true){//space
				Board b = this->clone();
			  	b.moveMyRing(ringcolor,px,py,px-i,py);
			    b.setAction(px,py,px-i,py);
			    neighbours.push_back(b);			
			    dir5=false;
				break;
			}
			else if(validBoardArray[px-i][py]==false){dir5=false;break;}//invalid
			else if((boardArray[px-i][py]==0 || boardArray[px-i][py]==1)&&validBoardArray[px-i][py]==true){dir5=false;break;}//rings
			else if((boardArray[px-i][py]==2 || boardArray[px-i][py]==3)&&validBoardArray[px-i][py]==true){flag=1; i++;}//markers
		}

	} 

	return neighbours;


}




// ------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------

vector<Board> Board::getNeighbours(int px,int py, int ringcolor){
	// HAVE TO ADD THE CASE IN WHICH THERE IS -1 IN A DIRECTION SO ALL THE -1 IN THAT LINE
	// CORRESPOND TO NEIGHBOURS. 


	// Point p1;
	// p1.set(px,py);
	// Point p2=twod_from_hex(p1);
	// px=p2.getx();
	// py=p2.gety();

	vector <Board> neighbours;

// in direction 0
	int i=1;int flag =0;
	while(py+i<=10 && (boardArray[px][py+i] == 2 || boardArray[px][py+i] == 3 ) && validBoardArray[px][py+i]==true){
		i++;
		if(boardArray[px][py+i]==-1 && validBoardArray[px][py+i]==true){break;flag=3;}
		if(boardArray[px][py+i]==0||boardArray[px][py+i]==1) {break;flag=1;}
	}

	if(boardArray[px][py+1]==0||boardArray[px][py+1]==1)flag =1;
	if(i==1 && flag ==0){   //if there is no immediate ring and the adjecent is empty
		  int k=1;
		  while(py+k<=10 && boardArray[px][py+k] == -1 && validArray[px][py+k]== true){
		  	Board b = this->clone();
		  	b.moveMyRing(ringcolor,px,py,px,py+k);
		    b.setAction(px,py,px,py+k);
		    neighbours.push_back(b);
		    k++;
		    // cout<<"in while 0\n";
		  }
	}
	else if(flag==3){      //if the position is after the markers.
			Board p0 = this->clone(); 
			p0.moveMyRing(ringcolor,px,py,px,py+i);
			p0.setAction(px,py,px,py+i);
			// cout<<"in neighbour function : "<<"px,py,i is "<<px<<","<<py<<","<<i<<endl;
			// cout<<"printing board in neighbour function"<<endl;
			// p0.printBoard();
			neighbours.push_back(p0);
	}


// in direction 1
	i=1;flag =0;
	while(py+i<=10 && px+i<=10 && (boardArray[px+i][py+i] == 2 || boardArray[px+i][py+i] == 3 ) && validBoardArray[px+i][py+i]==true){
		i++;
		if(boardArray[px+i][py+i]==-1 && validBoardArray[px+i][py+i]==true){break;flag=3;}
		if(boardArray[px+i][py+i]==0||boardArray[px+i][py+i]==1) flag=1;
	}
	if(boardArray[px+1][py+1]==0||boardArray[px+1][py+1]==1)flag =1;

	if(i==1 && flag ==0){   //if there is no immediate ring and the adjecent is empty
		  int k=1;
		  while(py+k<=10 && px+k<=10 && boardArray[px+k][py+k] == -1 && validArray[px+k][py+k] == true){
		  	Board b = this->clone();
		  	b.moveMyRing(ringcolor,px,py,px+k,py+k);
		    b.setAction(px,py,px+k,py+k);
		    neighbours.push_back(b);
		    k++;
		  }
	}

	else if(flag==3){ 
				Board p1 = this->clone(); 
				p1.moveMyRing(ringcolor,px,py,px+i,py+i);
				p1.setAction(px,py,px+i,py+i);
				neighbours.push_back(p1);
	}


// in direction 2
	i=1;flag =0;
	while(px+i<=10 && (boardArray[px+i][py] == 2 || boardArray[px+i][py] == 3 )&& validBoardArray[px+i][py]==true){
		i++;
		if(boardArray[px+i][py]==-1 && validBoardArray[px+i][py]==true){break;flag=3;}
		if(boardArray[px+i][py]==0||boardArray[px+i][py]==1) flag=1;
	}
	if(boardArray[px+1][py]==0||boardArray[px+1][py]==1)flag =1;

	if(i==1 && flag ==0){   //if there is no immediate ring and the adjecent is empty
		  int k=1;
		  while(px+k<=10 && boardArray[px+k][py] == -1 && validArray[px+k][py] == true ){
		  	Board b = this->clone();
		  	b.moveMyRing(ringcolor,px,py,px+k,py);
		    b.setAction(px,py,px+k,py);
		    neighbours.push_back(b);
		    k++;
		  }
	}

	else if(flag==3) {
				Board p2 = this->clone(); 
				p2.moveMyRing(ringcolor,px,py,px+i,py);
			    p2.setAction(px,py,px+i,py);
				neighbours.push_back(p2);
	}
	

// in direction 3
	i=1;flag =0;
	while(py-i<=0 && (boardArray[px][py-i] == 2 || boardArray[px][py-i] == 3 )&& validBoardArray[px][py-i]==true){
		i++;
		if(boardArray[px][py-i]==-1 && validBoardArray[px][py-i]==true){break;flag=3;}
		if(boardArray[px][py-i]==0||boardArray[px][py-i]==1) flag=1;
	}
	if(boardArray[px][py-1]==0||boardArray[px][py-1]==1)flag =1;

	if(i==1 && flag ==0){   //if there is no immediate ring and the adjecent is empty
		  int k=1;
		  while(py-k>=0 && boardArray[px][py-k] == -1 && validArray[px][py-k] == true){
		  	Board b = this->clone();
		  	b.moveMyRing(ringcolor,px,py,px,py-k);
		    b.setAction(px,py,px,py-k);
		    neighbours.push_back(b);
		  	k++;		    
		  }
	}

	else if(flag==3){ 
		 		Board p3 = this->clone(); 
		        p3.moveMyRing(ringcolor,px,py,px,py-i);
				p3.setAction(px,py,px,py-i);
				neighbours.push_back(p3);
	}
		

// in direction 4
	i=1;flag =0;
	while(py-i>=0 && px-i>=0 && (boardArray[px-i][py-i] == 2 || boardArray[px-i][py-i] == 3 )&& validBoardArray[px-i][py-i]==true){
		i++;
		if(boardArray[px-i][py-i]==-1 && validBoardArray[px-i][py-i]==true){break;flag=3;}
		if(boardArray[px-i][py-i]==0||boardArray[px-i][py-i]==1) flag=1;
	}
	if(boardArray[px-1][py-1]==0||boardArray[px-1][py-1]==1)flag =1;

	if(i==1 && flag ==0){   //if there is no immediate ring and the adjecent is empty
		  int k=1;
		  while(py-k>=0 && px-k>=0 && boardArray[px-k][py-k] == -1 && validArray[px-k][py-k] == true ){
		  	Board b = this->clone();
		  	b.moveMyRing(ringcolor,px,py,px-k,py-k);
		    b.setAction(px,py,px-k,py-k);
		    neighbours.push_back(b);
		  	k++;
		  }
	}	

	else if(flag==3) {
				 Board p4 = this->clone(); 
		         p4.moveMyRing(ringcolor,px,py,px-i,py-i);
				 p4.setAction(px,py,px-i,py-i);
				 neighbours.push_back(p4);
	}
		

// in direction 5
	i=1;flag =0;
	while(px-i>=0 && (boardArray[px-i][py] == 2 || boardArray[px-i][py] == 3)&& validBoardArray[px-i][py]==true){
		i++;
		if(boardArray[px-i][py]==-1 && validBoardArray[px-i][py]==true){break;flag=3;}
		if(boardArray[px-i][py]==0||boardArray[px-i][py]==1) flag=1;
	}
	if(boardArray[px-1][py]==0||boardArray[px-1][py]==1)flag =1;

	if(i==1 && flag ==0){   //if there is no immediate ring and the adjecent is empty
		  int k=1;
		  while(px-k>=0 && boardArray[px-k][py] == -1 && validArray[px-k][py] == true ){
		  	Board b = this->clone();
		  	b.moveMyRing(ringcolor,px,py,px-k,py);
		    b.setAction(px,py,px-k,py);
		    neighbours.push_back(b);
		  	k++;
		  }
	}	

	else if(flag==3){ 
				Board p5 = this->clone(); 
				p5.moveMyRing(ringcolor,px,py,px-i,py);
				p5.setAction(px,py,px-i,py);
				neighbours.push_back(p5);
	}
		

return neighbours; 
	
}

// int boardsize = 11;
// int numberOfRings[2];
// int myIDboard,opponentIDboard;
// std::vector<Point> myringPositions, opponentringPositions;
// int boardArray [11] [11];
// bool validArray [11] [11];
// int action[4];

string Board::removeRing(int opponentID ){
	string removedMarkersRings ="";
	int ringcolor = opponentID;

	int mcolor = ringcolor+2;
	for(int j = 0; j<11;j++){
		for(int i= 0; i<=6;i++ ){
			if(boardArray[j][i] == mcolor && boardArray[j][i+1] == mcolor && boardArray[j][i+2] == mcolor && boardArray[j][i+3] == mcolor  
				&& boardArray[j][i+4] == mcolor){
				// do something-- make all pos of markers empty and valid-true; remove one ring and update things in the board-- RS 1 2 RE 4 16 X 3 4

				validArray[j][i]=true;validArray[j][i+1]=true;validArray[j][i+2]=true;
				validArray[j][i+3]=true;validArray[j][i+4]=true;
				boardArray[j][i]=-1;boardArray[j][i+1]=-1;boardArray[j][i+2]=-1;
				boardArray[j][i+3]=-1;boardArray[j][i+4]=-1;
				numberOfRings[opponentID]--;
				int ringXpos1,ringXpos2;
				if(ringcolor==myIDboard){ringXpos1=myringPositions[0].getx(); ringXpos2=myringPositions[0].gety();
										 myringPositions.erase(myringPositions.begin());}
				if(ringcolor==opponentIDboard){ringXpos1=opponentringPositions[0].getx(); ringXpos2=opponentringPositions[0].gety();
										opponentringPositions.erase(opponentringPositions.begin());}
			Point pstart,pend,ringX;
			pstart.set(j, i); pend.set(j ,i+4); ringX.set(ringXpos1, ringXpos2); 

			removedMarkersRings = removedMarkersRings + "RS "+ pstart.getHexagonPositionString()+" " ;
			removedMarkersRings = removedMarkersRings + "RE " + pend.getHexagonPositionString()+" ";
			removedMarkersRings = removedMarkersRings + "X "+ringX.getHexagonPositionString();

			}
		}
	}

	for(int j = 0; j<11;j++){
		for(int i= 0; i<=6;i++ ){
			if(boardArray[i][j] == mcolor && boardArray[i+1][j] == mcolor && boardArray[i+2][j] == mcolor && boardArray[i+3][j] == mcolor  
				&& boardArray[i+4][j] == mcolor){
				// do something.
				validArray[i][j]=true;validArray[i+1][j]=true;validArray[i+2][j]=true;
				validArray[i+3][j]=true;validArray[i+4][j]=true;
				boardArray[i][j]=-1;boardArray[i+1][j]=-1;boardArray[i+2][j]=-1;
				boardArray[i+3][j]=-1;boardArray[i+4][j]=-1;
				numberOfRings[opponentID]--;
				int ringXpos1,ringXpos2;
				if(ringcolor==myIDboard){ringXpos1=myringPositions[0].getx(); ringXpos2=myringPositions[0].gety();
										 myringPositions.erase(myringPositions.begin());}
				if(ringcolor==opponentIDboard){ringXpos1=opponentringPositions[0].getx(); ringXpos2=opponentringPositions[0].gety();
										opponentringPositions.erase(opponentringPositions.begin());}
			Point pstart,pend,ringX;
			pstart.set( i,j); pend.set(i+4 ,j); ringX.set(ringXpos1, ringXpos2); 

			removedMarkersRings = removedMarkersRings + "RS "+ pstart.getHexagonPositionString()+" " ;
			removedMarkersRings = removedMarkersRings + "RE " + pend.getHexagonPositionString()+" ";
			removedMarkersRings = removedMarkersRings + "X "+ringX.getHexagonPositionString();

			
			}
		}
	}

	for(int k = 4; k>=1;k--){
		for (int i = 0; i<7-k ;i++){
			if(boardArray[k+i][i] == mcolor && boardArray[k+i+1][i+1] == mcolor && boardArray[k+i+2][i+2] == mcolor && boardArray[k+i+3][i+3] == mcolor  
				&& boardArray[k+i+4][i+4] == mcolor){
				// do something.
				validArray[k+i][i]=true;validArray[k+i+1][i+1]=true;validArray[k+i+2][i+2]=true;
				validArray[k+i+3][i+3]=true;validArray[k+i+4][i+4]=true;
				boardArray[k+i][i]=-1;boardArray[k+i+1][i+1]=-1;boardArray[k+i+2][i+2]=-1;
				boardArray[k+i+3][i+3]=-1;boardArray[k+i+4][i+4]=-1;
				numberOfRings[opponentID]--;
				int ringXpos1,ringXpos2;
				if(ringcolor==myIDboard){ringXpos1=myringPositions[0].getx(); ringXpos2=myringPositions[0].gety();
										 myringPositions.erase(myringPositions.begin());}
				if(ringcolor==opponentIDboard){ringXpos1=opponentringPositions[0].getx(); ringXpos2=opponentringPositions[0].gety();
										opponentringPositions.erase(opponentringPositions.begin());}
			Point pstart,pend,ringX;
			pstart.set(k+i, i); pend.set(k+i+4 ,i+4); ringX.set(ringXpos1, ringXpos2); 

			removedMarkersRings = removedMarkersRings + "RS "+ pstart.getHexagonPositionString()+" " ;
			removedMarkersRings = removedMarkersRings + "RE " + pend.getHexagonPositionString()+" ";
			removedMarkersRings = removedMarkersRings + "X "+ringX.getHexagonPositionString();

			}
		}  
	}	


	// for line going to up-right in the middle. has to be written
	for (int i=1;i<=5;i++){
		if(boardArray[i][i] == mcolor && boardArray[i+1][i+1] == mcolor && boardArray[i+2][i+2] == mcolor && boardArray[i+3][i+3] == mcolor  
				&& boardArray[i+4][i+4] == mcolor){
				// do something.
				validArray[i][i]=true;validArray[i+1][i+1]=true;validArray[i+2][i+2]=true;
				validArray[i+3][i+3]=true;validArray[i+4][i+4]=true;
				boardArray[i][i]=-1;boardArray[i+1][i+1]=-1;boardArray[i+2][i+2]=-1;
				boardArray[i+3][i+3]=-1;boardArray[i+4][i+4]=-1;
				numberOfRings[opponentID]--;
				int ringXpos1,ringXpos2;
				if(ringcolor==myIDboard){ringXpos1=myringPositions[0].getx(); ringXpos2=myringPositions[0].gety();
										 myringPositions.erase(myringPositions.begin());}
				if(ringcolor==opponentIDboard){ringXpos1=opponentringPositions[0].getx(); ringXpos2=opponentringPositions[0].gety();
										opponentringPositions.erase(opponentringPositions.begin());}
			Point pstart,pend,ringX;
			pstart.set(i, i); pend.set(i+4 ,i+4); ringX.set(ringXpos1, ringXpos2); 

			removedMarkersRings = removedMarkersRings + "RS "+ pstart.getHexagonPositionString()+" " ;
			removedMarkersRings = removedMarkersRings + "RE " + pend.getHexagonPositionString()+" ";
			removedMarkersRings = removedMarkersRings + "X "+ringX.getHexagonPositionString();

			}
	}



	for(int k = 4; k>=1;k--){
		for (int i = 0; i<7-k ;i++){
			if(boardArray[i][k+i] == mcolor && boardArray[i+1][k+i+1] == mcolor && boardArray[i+2][k+i+2] == mcolor && boardArray[i+3][k+i+3] == mcolor  
				&& boardArray[i+4][k+i+4] == mcolor){
				// do something.
				validArray[i][k+i]=true;validArray[i+1][k+i+1]=true;validArray[i+2][k+i+2]=true;
				validArray[i+3][k+i+3]=true;validArray[i+4][k+i+4]=true;
				boardArray[i][k+i]=-1;boardArray[i+1][k+i+1]=-1;boardArray[i+2][k+i+2]=-1;
				boardArray[i+3][k+i+3]=-1;boardArray[i+4][k+i+4]=-1;
				numberOfRings[opponentID]--;
				int ringXpos1,ringXpos2;
				if(ringcolor==myIDboard){ringXpos1=myringPositions[0].getx(); ringXpos2=myringPositions[0].gety();
										 myringPositions.erase(myringPositions.begin());}
				if(ringcolor==opponentIDboard){ringXpos1=opponentringPositions[0].getx(); ringXpos2=opponentringPositions[0].gety();
										opponentringPositions.erase(opponentringPositions.begin());}
			Point pstart,pend,ringX;
			pstart.set(i, k+i); pend.set(i+4 ,k+i+4); ringX.set(ringXpos1, ringXpos2); 

			removedMarkersRings = removedMarkersRings + "RS "+ pstart.getHexagonPositionString()+" " ;
			removedMarkersRings = removedMarkersRings + "RE " + pend.getHexagonPositionString()+" ";
			removedMarkersRings = removedMarkersRings + "X "+ringX.getHexagonPositionString();

			
			}
		}  
	}

return removedMarkersRings;
}

// given the string of turn of the opponent remove his markers from the board. 
void Board::removeRingOpponent(int opponentID ,int from_x ,int from_y , int to_x ,int  to_y ,int ring_removeX ,int ring_removeY){
	Point p1,p2,p3;
	p1.set(from_x,from_y);
	p2.set(to_x,to_y);
	p3.set(ring_removeX,ring_removeY);
	Point p1changed=twod_from_hex(p1);
	Point p2changed=twod_from_hex(p2);
	Point p3changed=twod_from_hex(p3);
		
	from_x = p1changed.getx(); 
	from_y = p1changed.gety();
	to_x = p2changed.getx(); 
	to_y = p2changed.gety();
	ring_removeX = p3changed.getx(); 
	ring_removeY = p3changed.gety();


	int ringcolor = opponentID;
	this->numberOfRings[ringcolor] --;
	boardArray[ring_removeX][ring_removeY] = -1;
	validArray[ring_removeX][ring_removeY] = true;

	if(from_x == to_x){
		int miy = from_y,mxy  = to_y;
		if(from_y>to_y){miy = to_y; mxy = from_y;}  
		for(int i = miy+1; i< mxy ;i++){
			if (boardArray[from_x][i] != -1 ) {boardArray[from_x][i] = -1; validArray[from_x][i]= true;}// CHECK THIS IF CONDITION
		}
	}

	else if(from_y == to_y){
		int mix = from_x,mxx  = to_x;
		if(from_x>to_x){mix = to_x; mxx = from_x;}  
		for(int i = mix+1; i< mxx ;i++){
			if (boardArray[i][from_y] != -1 ) {boardArray[i][from_y] = -1;boardArray[i][from_y]=true;} 
		}
	}

	else{
		if(from_x < to_x){
		int s = to_x - from_x ;
		for(int i = 1; i< s ;i++){
			if (boardArray[from_x+i][from_y+i] != -1 ) {boardArray[from_x+i][from_y+i] = -1; boardArray[from_x+i][from_y+i] = true;} 
		}
		}

		else{
		int s =from_x -  to_x ;
		for(int i = 1; i< s ;i++){
			if (boardArray[from_x-i][from_y-i] != -1 ) {boardArray[from_x-i][from_y-i] = -1; boardArray[from_x-i][from_y-i] = true;} 
		}
		}
	}
}



// do something like storing a board and evaluationg the racursing on actions in minimax. 
vector<Board> Board::getSuccessors(int ringcolor){
	vector<Board> succ;
	// ringcolor == 
	for(int i =0;i<=10;i++){
		for(int j =0;j<=10;j++){
			if(boardArray[i][j] == ringcolor){
				//cout<<"looking for neighbours of "<<i<<","<<j<<endl;
				vector<Board> n = this->getNeighbours1(i,j,ringcolor);
				succ.insert(succ.end(),n.begin(),n.end());
			}
		}
	}
	return succ;
}


void Board::printBoard(){
	int c;
    for(int i = 0;i<=10;i++){
	for(int j = 0;j<=10;j++){
		c = boardArray[j][i];
		if(boardArray[j][i]==-1) c = 5;
		if(c==5)cout<<"*"<<" ";
		else{cout<<c<<" ";}
	}
	cout<<"                ";
	for(int j =0;j<=10;j++){
		cout<<validArray[j][i]<<" ";
	}

	cout<<endl;
	}
}

// this is old one

