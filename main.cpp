#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "Board.h"
using namespace std;


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



int main() {
Board board;

while(true){
	string opponentMove;
	std::getline (std::cin,opponentMove);
    std::vector<std::string> tokens = split(opponentMove, ' '); //tokens is a vector conating input//for(auto& s: tokens)std::cout << s << endl;
    //Tokens can be-- P 1 2 | S 1 2 M 2 4 | RS 1 2 RE 4 16 X 3 4 | S 1 2 M 2 4 RS 1 2 RE 4 16 X 3 4
    int countTokens=tokens.size();
    int readTokens=0;
while(countTokens>0){

    if(tokens[0]=="P"){ //place a ring
        readTokens++;
        int hexagon = stoi(tokens[readTokens]);
        readTokens++;
        int position = stoi(tokens[readTokens]);
        board.setRing(0,hexagon,position);
        
    }
    else if(tokens[0]=="S"){
        if(tokens.size()==)
        int hexagon = stoi(tokens[1]);
        int position = stoi(tokens[2]);
        board.setRing(0,hexagon,position);
    }
    else if(tokens[0]=="RS"){ //remove row of markers and ring
        int hexagon = stoi(tokens[1]);
        int position = stoi(tokens[2]);
        board.setRing(0,hexagon,position);
    }    
    countTokens--;
}

    

    //OUR Turn... Move wisely! Best luck!
}

}

 
