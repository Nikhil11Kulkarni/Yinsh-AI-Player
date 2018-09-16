#define __USE_MINGW_ANSI_STDIO 0
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "Board.h"
using namespace std;

//GLOBAL VARIABLES
Board board; 
Board ansboard; 
int myID,opponentID;


//GLOBAL FUNCTIONS
template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

string setInitialRing(){
	string initialmove="P ";
	int j=5;
	Point p1,p2;
	
	if(board.validArray[5][5]==true){  board.setmyRing(myID, 5, 5);	cout<<" px:"<<5<<" py:"<<5<<endl;
		p1.set(5,5); 
		p2 = board.hex_from_twod(p1); 
		initialmove=initialmove + p2.getxystring() ;
		return initialmove;
	}//centre
	for(int i=1;i<5;i++){
		if(board.validArray[5+i][j]==true){board.setmyRing(myID, 5+i, j); 	cout<<" px:"<< 5+i <<" py:"<<j<<endl; 
			p1.set(5+i,j); 
			p2 = board.hex_from_twod(p1); 
			initialmove=initialmove + p2.getxystring() ;
			return initialmove;}

		if(board.validArray[5-i][j]==true){board.setmyRing(myID, 5-i, j);	cout<<" px:"<< 5-i<<" py:"<< j<<endl;
			p1.set(5-i,j); 
			p2 = board.hex_from_twod(p1); 
			initialmove=initialmove + p2.getxystring() ;
			return initialmove;}
	
		if(board.validArray[j][5+i]==true){board.setmyRing(myID, j,5+i);	cout<<" px:"<<j<<" py:"<<5+i<<endl;
			p1.set(j,5+i); 
			p2 = board.hex_from_twod(p1); 
			initialmove=initialmove + p2.getxystring() ;
			return initialmove;}

		if(board.validArray[j][5-i]==true){board.setmyRing(myID, j,5-i);	cout<<" px:"<<j<<" py:"<<5-i<<endl;
			p1.set(j,5-i); 
			p2 = board.hex_from_twod(p1); 
			initialmove=initialmove + p2.getxystring() ;
			return initialmove;}
	}

	cout<<"NONE OF THE SORROUNDING HAVE SPACE TO PUT A RING :CHECK!!!";
	return initialmove;

}


void updateBoardOpponentMove(int opponentID , string opponentMove){
    std::vector<std::string> tokens = split(opponentMove, ' '); //tokens is a vector conating input//for(auto& s: tokens)std::cout << s << endl;
    //Tokens can be-- P 1 2 | S 1 2 M 2 4 | RS 1 2 RE 4 16 X 3 4 | S 1 2 M 2 4 RS 1 2 RE 4 16 X 3 4

    int readTokens=0;
while(readTokens < tokens.size()){

    if(tokens[readTokens]=="P"){ //place a ring
        readTokens++;
        int hexagon = stoi(tokens[readTokens]);
        readTokens++;
        int position = stoi(tokens[readTokens]);
        readTokens++;
        
        board.setRing(opponentID , hexagon , position);    
    }
    else if(tokens[readTokens]=="S"){
        readTokens++;
        int from_x = stoi(tokens[readTokens]);
        readTokens++;
        int from_y = stoi(tokens[readTokens]);
        readTokens=readTokens+2; // AS  (S 1 2 M 2 4)
        int to_x = stoi(tokens[readTokens]);
        readTokens++;
        int to_y = stoi(tokens[readTokens]);
        readTokens++;

        board.moveRing(opponentID, from_x , from_y, to_x , to_y);
    }
    else if(tokens[readTokens]=="RS"){ //remove row of markers and ring - 0 1 2 4 5 7 8
        readTokens++;
        int from_x = stoi(tokens[readTokens]);
        readTokens++;
        int from_y = stoi(tokens[readTokens]);
        readTokens=readTokens+2; // AS  (S 1 2 M 2 4)
        int to_x = stoi(tokens[readTokens]);
        readTokens++;
        int to_y = stoi(tokens[readTokens]);
        readTokens=readTokens+2;
        int ring_removeX = stoi(tokens[readTokens]);
        readTokens++;
        int ring_removeY = stoi(tokens[readTokens]);
        readTokens++;

        board.removeRingOpponent(opponentID , from_x ,from_y , to_x , to_y , ring_removeX , ring_removeY);
        
    	}    
}

}
int evaluation(Board board){
	int myarr[6],opponentarr[6],weights[6];
	int myCount=0,opponentCount=0;
	for(int i=0;i<6;i++){ myarr[i]=0; opponentarr[i]=0; weights[i]=i*2; }
	int currentTurn= myID;
	for(int i = 0; i<11;i++){
		for(int j= 0; j<11;j++){
			if(board.boardArray[i][j]==myID && currentTurn==myID){
				myCount++;
			}
			if(board.boardArray[i][j]==myID && currentTurn==opponentID){
				opponentarr[opponentCount]=opponentarr[opponentCount] + 1;
				opponentCount=0;
				currentTurn=myID;
				myCount++;
			}
			if(board.boardArray[i][j]==opponentID && currentTurn==myID){
				myarr[myCount]=myarr[myCount] + 1;
				myCount=0;
				currentTurn=opponentID;
				opponentCount++;
			}
			if(board.boardArray[i][j]==opponentID && currentTurn==opponentID){
				opponentCount++;
			}
			if(board.boardArray[i][j]!=opponentID && board.boardArray[i][j]!=myID){
				if(currentTurn==myID)myarr[myCount]=myarr[myCount] + 1;
				if(currentTurn==opponentID)opponentarr[opponentCount]=opponentarr[opponentCount] + 1;
				myCount=0;
				opponentCount=0;
				currentTurn=myID;
			}
		}
		if(currentTurn==myID)myarr[myCount]=myarr[myCount] + 1;
		if(currentTurn==opponentID)opponentarr[opponentCount]=opponentarr[opponentCount] + 1;
		myCount=0;
		opponentCount=0;
		currentTurn=myID;
	}
int sumEvaluation=0;
	for(int i=0;i<6;i++){ sumEvaluation=sumEvaluation + weights[i]*(myarr[i] - opponentarr[i]) ; }
return sumEvaluation;
}

int maxValue(Board currentBoard , int depth);
int minValue(Board currentBoard, int depth);

int minValue(Board currentBoard, int depth){

	if(depth==1){int ans=evaluation(currentBoard) ;return ans;} //TERMINAL TEST
	std::vector<Board> currentNeighbours = currentBoard.getSuccessors(opponentID);
	int v=std::numeric_limits<int>::max();
	depth++;
	for(int i=0;i<currentNeighbours.size();i++){
		v=min(v , maxValue(currentNeighbours[i] , depth));
	}
	return v;
	
}

int maxValue(Board currentBoard , int depth){
		//cout<<"maxValue:start"<<endl;
	if(depth==1){int ans=evaluation(currentBoard) ;return ans;} //TERMINAL TEST
	cout<<"\n\ncurrentBoard:\n"<<endl;
	currentBoard.printBoard();
	std::vector<Board> currentNeighbours = currentBoard.getSuccessors(myID);
	int v=std::numeric_limits<int>::min();
	depth++;
	for(int i=0;i<currentNeighbours.size();i++){
		int minofneighbour= minValue(currentNeighbours[i],depth);
		cout<<"\n\ncurrentNeighbours[i]:\n"<<endl;
		currentNeighbours[i].printBoard();
		if(depth==1 && minofneighbour > v){ansboard = currentNeighbours[i];}
		v= max(v,  minofneighbour);
	}
	return v;

}

string minimaxDecision(Board currentBoard){
	int depth=0;
	string ans1="";
		//cout<<"minimaxDecision:start"<<endl;
	int v=maxValue(currentBoard, depth);
// 	std::vector<Board> currentNeighbours = currentBoard.getSuccessors(myID);
// 	cout<<"minimaxDecision:got v:size"<<currentNeighbours.size()<<endl;
// 	for(int i=0;i<currentNeighbours.size();i++){
// 		cout<<i<<":11minimaxDecision:got v:"<<v<<endl;
// 		if(evaluation(currentNeighbours[i])==v){
// 		cout<<"yippie"<<endl; 
// 		}
// 		//return action string here.
// 	}
//	return ans1;
cout<<"\n\nansboard:\n";
// ansboard.printBoard();
board=ansboard ; 
Point p1,p2;
	p1.set(ansboard.action[0],ansboard.action[1]);
	p2.set(ansboard.action[2],ansboard.action[3]);
	Point p1changed=hex_from_twod(p1);
	Point p2changed=hex_from_twod(p2);
	
	int from_x = p1changed.getx(); 
	int from_y = p1changed.gety();
	int to_x = p2changed.getx(); 
	int to_y = p2changed.gety();
	

		string ans="";
		ans=ans+"S ";
		ans=ans+ to_string(from_x)+" "+to_string(from_y)+" ";//"S x y "
		ans=ans+"M " + to_string(to_x)+" "+to_string(to_y);//"S x y M x y";
		
		return ans;

}



int main() {

	bool placingDone = false;
	//cin--for detecting who is playing first. by default -- opponent is playing first.
	//if first move is ours then do it here in 1 if loop // alloted values here---> myID,opponentID (0 ,1-by default)
		int playernum,boardsizeHexagon;
		cin>>playernum;
			myID=playernum - 1; // as it is either 0 OR 1
			opponentID = (3 -playernum) -1;//planum=1--myid=0--oppid=1   planum=2--myid=1--oppid=0
			board.setID(myID,opponentID);
		cin>>boardsizeHexagon; //NOT USED UNTIL NOW
		cin>>;//PUT TIME 

if(myID==0){
string mo1= setInitialRing(); //function sets the board and gives the initial move.
cout<<mo1<<endl;
}

while(true){
	string opponentMove;
	std::getline (std::cin,opponentMove);
	updateBoardOpponentMove( opponentID , opponentMove);
	board.printBoard();
    //OUR Turn... Move wisely! Best luck!

//First 5 moves must place a ring.
//Thereafter search for "Removable Rows"--if T then remove them and remove a ring for every row.
//else move a ring and 
//Remove as many Removable Rows as possible.
//At specific points check for win-lose-draw condition of the board. and exit the loop accordingly & print score + results.
if(board.numberOfRings[myID]==5)placingDone=true;
string mymove;

	if(placingDone==false){
		mymove= setInitialRing(); //function sets the board and gives the initial move.
		cout<<mymove<<endl;
	}

	else{
		string strRemove1 = "",strRemove2 = "";

		cout<<"b1"<<endl;
		strRemove1= board.removeRing(myID);
		cout<<"b2"<<endl;
		mymove = minimaxDecision(board);
		cout<<"b3:------"<<mymove<<endl;		
		strRemove2= board.removeRing(myID);
		cout<<"b4"<<endl;
	if(strRemove1!=""){mymove = strRemove1 +" "+ mymove;}
	if(strRemove2!=""){	mymove=mymove+" " +strRemove2 ;}

		cout<<mymove<<endl;	
	}
	cout<<"b5"<<endl;

if(placingDone==true && (board.numberOfRings[myID]<=2 || board.numberOfRings[opponentID]<=2) ){
	int winner,unlucky;
	cout<<"b6"<<endl;	
	if(board.numberOfRings[myID]<=2){ winner=myID; unlucky=opponentID;}
	else{ winner=opponentID; unlucky=myID;} 

	cout<<"GAME OVER BROS: WIN:"<<winner<<" and LOSS:"<<unlucky<<endl;
	break;
}

}


}

 
