#define __USE_MINGW_ANSI_STDIO 0
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include<time.h>
#include <limits>
#include <bits/stdc++.h>
#include <ctime>
#include "Board.h"
using namespace std;

//GLOBAL VARIABLES
Board board; 
Board ansboard; 
int myID,opponentID , depthLimiting;
double timeAllowed;
int initialStepsWithLessDepth=0;


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
	
	if(board.validArray[5][5]==true){  board.setmyRing(myID, 5, 5);	//cout<<" px:"<<5<<" py:"<<5<<endl;
		p1.set(5,5); 
		p2 = board.hex_from_twod(p1); 
		initialmove=initialmove + p2.getxystring() ;
		return initialmove;
	}//centre
	for(int i=1;i<5;i++){
		if(board.validArray[5+i][j]==true){board.setmyRing(myID, 5+i, j); 	//cout<<" px:"<< 5+i <<" py:"<<j<<endl; 
			p1.set(5+i,j); 
			p2 = board.hex_from_twod(p1); 
			initialmove=initialmove + p2.getxystring() ;
			return initialmove;}

		if(board.validArray[5-i][j]==true){board.setmyRing(myID, 5-i, j);	//cout<<" px:"<< 5-i<<" py:"<< j<<endl;
			p1.set(5-i,j); 
			p2 = board.hex_from_twod(p1); 
			initialmove=initialmove + p2.getxystring() ;
			return initialmove;}
	
		if(board.validArray[j][5+i]==true){board.setmyRing(myID, j,5+i);	//cout<<" px:"<<j<<" py:"<<5+i<<endl;
			p1.set(j,5+i); 
			p2 = board.hex_from_twod(p1); 
			initialmove=initialmove + p2.getxystring() ;
			return initialmove;}

		if(board.validArray[j][5-i]==true){board.setmyRing(myID, j,5-i);	//cout<<" px:"<<j<<" py:"<<5-i<<endl;
			p1.set(j,5-i); 
			p2 = board.hex_from_twod(p1); 
			initialmove=initialmove + p2.getxystring() ;
			return initialmove;}
	}

	//cout<<"NONE OF THE SORROUNDING HAVE SPACE TO PUT A RING :CHECK!!!";
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
	for(int i=0;i<6;i++){ myarr[i]=0; opponentarr[i]=0; 
		if(i==5){weights[i]=100;} 
		else{weights[i]=i*2;}
	}
	int currentTurn= myID;
	for(int i = 0; i<11;i++){
		for(int j= 0; j<11;j++){			
					if(board.boardArray[i][j]==(myID+2) && currentTurn==myID){
						myCount++;
					}
					if(board.boardArray[i][j]==(myID+2) && currentTurn==opponentID){
						opponentarr[opponentCount]=opponentarr[opponentCount] + 1;
						opponentCount=0;
						currentTurn=myID;
						myCount++;
					}
					if(board.boardArray[i][j]==(opponentID+2) && currentTurn==myID){
						myarr[myCount]=myarr[myCount] + 1;
						myCount=0;
						currentTurn=opponentID;
						opponentCount++;
					}
					if(board.boardArray[i][j]==(opponentID+2) && currentTurn==opponentID){
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
myCount=0; opponentCount=0;

		for(int j = 0; j<11;j++){
			for(int i= 0; i<11;i++){			
					if(board.boardArray[i][j]==(myID+2) && currentTurn==myID){
						myCount++;
					}
					if(board.boardArray[i][j]==(myID+2) && currentTurn==opponentID){
						opponentarr[opponentCount]=opponentarr[opponentCount] + 1;
						opponentCount=0;
						currentTurn=myID;
						myCount++;
					}
					if(board.boardArray[i][j]==(opponentID+2) && currentTurn==myID){
						myarr[myCount]=myarr[myCount] + 1;
						myCount=0;
						currentTurn=opponentID;
						opponentCount++;
					}
					if(board.boardArray[i][j]==(opponentID+2) && currentTurn==opponentID){
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

	myCount=0; opponentCount=0;

	for(int k = 4; k>=1;k--){
		for (int i = 0; i<11-k ;i++){
					if(board.boardArray[k+i][i]==(myID+2) && currentTurn==myID){
						myCount++;
					}
					if(board.boardArray[k+i][i]==(myID+2) && currentTurn==opponentID){
						opponentarr[opponentCount]=opponentarr[opponentCount] + 1;
						opponentCount=0;
						currentTurn=myID;
						myCount++;
					}
					if(board.boardArray[k+i][i]==(opponentID+2) && currentTurn==myID){
						myarr[myCount]=myarr[myCount] + 1;
						myCount=0;
						currentTurn=opponentID;
						opponentCount++;
					}
					if(board.boardArray[k+i][i]==(opponentID+2) && currentTurn==opponentID){
						opponentCount++;
					}
					if(board.boardArray[k+i][i]!=opponentID && board.boardArray[k+i][i]!=myID){
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
	// for line going to up-right in the middle. has to be written
	myCount=0; opponentCount=0;

	for (int i=1;i<=9;i++){
					if(board.boardArray[i][i]==(myID+2) && currentTurn==myID){
						myCount++;
					}
					if(board.boardArray[i][i]==(myID+2) && currentTurn==opponentID){
						opponentarr[opponentCount]=opponentarr[opponentCount] + 1;
						opponentCount=0;
						currentTurn=myID;
						myCount++;
					}
					if(board.boardArray[i][i]==(opponentID+2) && currentTurn==myID){
						myarr[myCount]=myarr[myCount] + 1;
						myCount=0;
						currentTurn=opponentID;
						opponentCount++;
					}
					if(board.boardArray[i][i]==(opponentID+2) && currentTurn==opponentID){
						opponentCount++;
					}
					if(board.boardArray[i][i]!=opponentID && board.boardArray[i][i]!=myID){
						if(currentTurn==myID)myarr[myCount]=myarr[myCount] + 1;
						if(currentTurn==opponentID)opponentarr[opponentCount]=opponentarr[opponentCount] + 1;
						myCount=0;
						opponentCount=0;
						currentTurn=myID;
					}
	}
	
	myCount=0; opponentCount=0;

	for(int k = 4; k>=1;k--){
		for (int i = 0; i<11-k ;i++){
		
					if(board.boardArray[i][k+i]==(myID+2) && currentTurn==myID){
						myCount++;
					}
					if(board.boardArray[i][k+i]==(myID+2) && currentTurn==opponentID){
						opponentarr[opponentCount]=opponentarr[opponentCount] + 1;
						opponentCount=0;
						currentTurn=myID;
						myCount++;
					}
					if(board.boardArray[i][k+i]==(opponentID+2) && currentTurn==myID){
						myarr[myCount]=myarr[myCount] + 1;
						myCount=0;
						currentTurn=opponentID;
						opponentCount++;
					}
					if(board.boardArray[i][k+i]==(opponentID+2) && currentTurn==opponentID){
						opponentCount++;
					}
					if(board.boardArray[i][k+i]!=opponentID && board.boardArray[i][k+i]!=myID){
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
	for(int i=0;i<6;i++){ sumEvaluation=sumEvaluation + weights[i]*(myarr[i]- opponentarr[i]) ; } 
	sumEvaluation = sumEvaluation + (board.numberOfRings[board.opponentIDboard] - board.numberOfRings[board.myIDboard])*1000; 
return sumEvaluation;
}


bool checkfive(Board b){

	int ringcolor = myID;
	bool ans=false;
	int mcolor = ringcolor+2;
	for(int j = 0; j<11;j++){
		for(int i= 0; i<=6;i++ ){
			if(b.boardArray[j][i] == mcolor && b.boardArray[j][i+1] == mcolor && b.boardArray[j][i+2] == mcolor && b.boardArray[j][i+3] == mcolor  
				&& b.boardArray[j][i+4] == mcolor){
				// do something-- make all pos of markers empty and valid-true; remove one ring and update things in the board-- RS 1 2 RE 4 16 X 3 4

				ans =true;

			}
		}
	}

	for(int j = 0; j<11;j++){
		for(int i= 0; i<=6;i++ ){
			if(b.boardArray[i][j] == mcolor && b.boardArray[i+1][j] == mcolor && b.boardArray[i+2][j] == mcolor && b.boardArray[i+3][j] == mcolor  
				&& b.boardArray[i+4][j] == mcolor){
				// do something.
				ans=true;
			
			}
		}
	}

	for(int k = 4; k>=1;k--){
		for (int i = 0; i<7-k ;i++){
			if(b.boardArray[k+i][i] == mcolor && b.boardArray[k+i+1][i+1] == mcolor && b.boardArray[k+i+2][i+2] == mcolor && b.boardArray[k+i+3][i+3] == mcolor  
				&& b.boardArray[k+i+4][i+4] == mcolor){
				
				ans =true;
			}
		}  
	}	


	// for line going to up-right in the middle. has to be written
	for (int i=1;i<=5;i++){
		if(b.boardArray[i][i] == mcolor && b.boardArray[i+1][i+1] == mcolor && b.boardArray[i+2][i+2] == mcolor && b.boardArray[i+3][i+3] == mcolor  
				&& b.boardArray[i+4][i+4] == mcolor){
				// do something.
				ans = true;

			}
	}



	for(int k = 4; k>=1;k--){
		for (int i = 0; i<7-k ;i++){
			if(b.boardArray[i][k+i] == mcolor && b.boardArray[i+1][k+i+1] == mcolor && b.boardArray[i+2][k+i+2] == mcolor && b.boardArray[i+3][k+i+3] == mcolor  
				&& b.boardArray[i+4][k+i+4] == mcolor){
				// do something.
				ans = true;
			
			}
		}  
	}

return ans;
}

int maxValue(Board currentBoard , int depth,int alpha, int beta);
int minValue(Board currentBoard, int depth,int alpha, int beta);

int minValue(Board currentBoard, int depth,int alpha, int beta){

	if(depth==depthLimiting){int ans=evaluation(currentBoard) ;return ans;} //TERMINAL TEST
	std::vector<Board> currentNeighbours = currentBoard.getSuccessors(opponentID);
	int v=std::numeric_limits<int>::max();
	depth++;
	for(int i=0;i<currentNeighbours.size();i++){
		int maxofneighbour = maxValue(currentNeighbours[i],depth,alpha,beta);
		beta = min(beta,maxofneighbour);
		if(alpha>= beta) return maxofneighbour;
		v=min(v , maxofneighbour);
	}
	return v;
	
}

int maxValue(Board currentBoard , int depth, int alpha, int beta){

	if(depth==depthLimiting){int ans=evaluation(currentBoard) ;return ans;} //TERMINAL TEST
	std::vector<Board> currentNeighbours = currentBoard.getSuccessors(myID);
	int v=std::numeric_limits<int>::min();
	depth++;
	for(int i=0;i<currentNeighbours.size();i++){
		int minofneighbour= minValue(currentNeighbours[i],depth,alpha,beta);
		alpha = max(alpha,minofneighbour);
		if(alpha>=beta) return minofneighbour;
		if(depth==1){
			bool t = checkfive(currentNeighbours[i]);
			//cerr<<"five truth is"<<t<<endl;
			if(t){ansboard = currentNeighbours[i];return minValue(currentNeighbours[i],depth,alpha,beta);}
		}
		if(depth==1 && minofneighbour > v){ansboard = currentNeighbours[i];}
		v= max(v,  minofneighbour);
	}
	return v;

}

string minimaxDecision(Board currentBoard){
	int alpha =  std::numeric_limits<int>::min();
	int beta = std::numeric_limits<int>::max();
	int depth=0;
	if(timeAllowed < 10 || initialStepsWithLessDepth <= 3) depthLimiting=1;
	else if(timeAllowed > 10) depthLimiting=4;
	
	string ans1="";
		//cout<<"minimaxDecision:start"<<endl;
	int v=maxValue(currentBoard, depth, alpha, beta);
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
// cout<<"\n\nansboard:\n";
// ansboard.printBoard();

cerr<<"my--from_x:"<<ansboard.action[0]<<" from_y:"<<ansboard.action[1]<<" to_x:"<<ansboard.action[2]<<" to_y:"<<ansboard.action[3]<<endl;

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
			if(ansboard.actionRemoveString != ""){ans=ans+" "+ansboard.actionRemoveString ;}	
		return ans;

}

std::istream& skip_till_endl(std::istream& in)
{
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return in;
}


int main() {

	bool placingDone = false;
	double totaltime;
	//cin--for detecting who is playing first. by default -- opponent is playing first.
	//if first move is ours then do it here in 1 if loop // alloted values here---> myID,opponentID (0 ,1-by default)
		int playernum,boardsizeHexagon;
		cin>>playernum;
			myID=playernum - 1; // as it is either 0 OR 1
			opponentID = (3 -playernum) -1;//planum=1--myid=0--oppid=1   planum=2--myid=1--oppid=0
			board.setID(myID,opponentID);
		cin>>boardsizeHexagon; //NOT USED UNTIL NOW
		cin>>timeAllowed>>skip_till_endl;//PUT TIME 

if(myID==0){
string mo1= setInitialRing(); //function sets the board and gives the initial move.
cout<<mo1<<endl;
}

while(true){

	string opponentMove;
	std::getline (std::cin,opponentMove);
	double timestart= clock();

	updateBoardOpponentMove( opponentID , opponentMove);

if(board.numberOfRings[myID]==5){placingDone=true;} //cout<<"placingDone."<<endl;
string mymove="";

	if(placingDone==false){

		mymove= setInitialRing(); //function sets the board and gives the initial move.
		cout<<mymove<<endl;
	}
	else{
		initialStepsWithLessDepth++;
		string strRemove1 = "", strRemove2 = "";
		strRemove1= board.removeRing(myID);

		if(board.numberOfRings[myID]<=2){
			//mymove = strRemove1 +" "+ mymove;
			cout<<strRemove1<<"\n";	
		}
		else{
			mymove = minimaxDecision(board);
			strRemove2= board.removeRing(myID);
			
		if(strRemove1!=""){mymove = strRemove1 +" "+ mymove;}
		if(strRemove2!=""){mymove = mymove+" " +strRemove2 ;}

			if(board.numberOfRings[myID]<=2) { cout<<mymove<<"\n";	cerr<<"with /n"<<endl;} //AS GAME ENDS --- NO EXTRA PRINT
			else{cout<<mymove<<"\n";}//	cerr<<"GAME OVER BRODAAA---please do it: no:"<<board.numberOfRings[myID]<<endl;
		}	

	}
	bool gameendDone=false;
if(placingDone==true && (board.numberOfRings[myID]<=2 || board.numberOfRings[opponentID]<=2) ){
	int winner,unlucky;
	cerr<<"GAME OVER BRODAAA"<<endl;
	gameendDone=true;	
	if(board.numberOfRings[myID]<=2){ winner=myID; unlucky=opponentID;}
	else{ winner=opponentID; unlucky=myID;} 
//while(true){	cerr<<"GAME OVER BROS: WIN:"<<winner<<" and LOSS:"<<unlucky<<endl;}

	//break;
}


	double timeend= clock();
	double timeelapsed=(timestart - timeend)/(CLOCKS_PER_SEC);

timeAllowed=timeAllowed - timeelapsed;
if(gameendDone==true)break;

}


}

//PLEASE DONOT DELETE THIS COMMANDS
 
//OUR Turn... Move wisely! Best luck!

//First 5 moves must place a ring.
//Thereafter search for "Removable Rows"--if T then remove them and remove a ring for every row.
//else move a ring and 
//Remove as many Removable Rows as possible.
//At specific points check for win-lose-draw condition of the board. and exit the loop accordingly & print score + results.


// cout<<"b1"<<endl;
// cout<<"b3:------"<<mymove<<endl;
// cout<<"b4"<<endl;
//cout<<"b5"<<endl;

//cout<<"opponentMove:"<<opponentMove<<endl;
//board.printBoard();
// cout<<"myring:"<<board.numberOfRings[myID]<<endl;
// cout<<"opponentring:"<<board.numberOfRings[opponentID]<<endl;
		//cout<<"1 -- myring:"<<board.numberOfRings[myID]<<" opponentring:"<<board.numberOfRings[opponentID]<<endl;
		//cout<<"2 -- myring:"<<board.numberOfRings[myID]<<" opponentring:"<<board.numberOfRings[opponentID]<<endl;	
		//cout<<"-- myring:"<<board.numberOfRings[myID]<<" opponentring:"<<board.numberOfRings[opponentID]<<endl;

