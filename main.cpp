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

        board.removeRing(opponentID , from_x ,from_y , to_x , to_y , ring_removeX , ring_removeY);
        
    	}    
}

}

int main() {

	int myID,opponentID;
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
if(board.mynumberOfRings==5)placingDone=

}


}

 
