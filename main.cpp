#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "Board.h"
using namespace std;

//GLOBAL VARIABLES
Board board; 


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
	
	if(validArray[5][5]==false){  board.setRing(myID, 5, 5);
		p1.set(5,5); 
		p2 = board.hex_from_twod(p1); 
		initialmove=initialmove + p2.getxystring() ;
		return initialmove;
	}//centre
	for(int i=1;i<5;i++){
		if(validArray[5+i][j]==false){board.setRing(myID, 5+i, j);  
			p1.set(5+i,j); 
			p2 = board.hex_from_twod(p1); 
			initialmove=initialmove + p2.getxystring() ;
			return initialmove;}

		if(validArray[5-i][j]==false){board.setRing(myID, 5-i, j);
			p1.set(5+i,j); 
			p2 = board.hex_from_twod(p1); 
			initialmove=initialmove + p2.getxystring() ;
			return initialmove;}
	
		if(validArray[j][5+i]==false){board.setRing(myID, j,5+i);
			p1.set(5+i,j); 
			p2 = board.hex_from_twod(p1); 
			initialmove=initialmove + p2.getxystring() ;
			return initialmove;}

		if(validArray[j][5-i]==false){board.setRing(myID, j,5-i);
			p1.set(5+i,j); 
			p2 = board.hex_from_twod(p1); 
			initialmove=initialmove + p2.getxystring() ;
			return initialmove;}
	}
	cout<<"NONE OF THE SORROUNDING HAVE SPACE TO PUT A RING :CHECK!!!"
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
	int myCount=0;opponentCount=0;
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

int maxValue(Board currentBoard , int depth){
	if(depth==1){int ans=evaluation(currentBoard) ;return ans;} //TERMINAL TEST
	std::vector<Board> currentNeighbours = currentBoard.getNeighbours();
	int v=-1;
	depth++;
	for(int i=0;i<currentNeighbours.size();i++){
		v=max(v , minValue(currentNeighbours[i] , depth));
	}
	return v;

}

int minValue(Board currentBoard, int depth){

	if(depth==1){int ans=evaluation(currentBoard) ;return ans;} //TERMINAL TEST
	std::vector<Board> currentNeighbours = currentBoard.getNeighbours();
	int v=std::numeric_limits<int>::max();
	depth++;
	for(int i=0;i<currentNeighbours.size();i++){
		v=min(v , maxValue(currentNeighbours[i] , depth));
	}
	return v;
	
}

string minimaxDecision(Board currentBoard){
	int depth=0;
	int v=maxValue(currentBoard, depth);
	std::vector<Board> currentNeighbours = currentBoard.getNeighbours();
	for(int i=0;i<currentNeighbours.size();i++){
		if(evaluation(currentNeighbours[i])==v){ board=currentBoard ; return currentNeighbours.action;}//return action string here.
	}
}



int main() {

	int myID=1,opponentID=0;
	bool placingDone = false;
	//cin--for detecting who is playing first. by default -- opponent is playing first.
	//if first move is ours then do it here in 1 if loop // alloted values here---> myID,opponentID (0 ,1-by default)

while(true){
	string opponentMove;
	std::getline (std::cin,opponentMove);
	updateBoardOpponentMove( opponentID , opponentMove);
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
		board.removeRing(myID);
		mymove = minimaxDecision(board);
		board.removeRing(myID);
		cout<<mymove<<endl;	
	}

if(placingDone==true && (board.numberOfRings[myID]<=2 || board.numberOfRings[opponentID]<=2) ){
	int winner,unlucky;
	if(board.numberOfRings[myID]<=2){ winner=myID; unlucky=opponentID;}
	else{ winner=opponentID; unlucky=myID;} 

	cout<<"GAME OVER BROS: WIN:"<<winner<<" and LOSS:"<<unlucky<<endl;
	break;
}

}


}

 
