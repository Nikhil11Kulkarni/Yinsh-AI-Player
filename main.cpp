#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "Board.h"
using namespace std;

// const int depot=0;
// const int startCustomer=1,endCustomer=1000;
// const int startCharging=1001,endCharging=1100;

int main() {
Board board;

while(true){
	string opponentMove;
	std::getline (std::cin,opponentMove);
    std::istringstream buf(opponentMove);
    std::istream_iterator<std::string> beg(buf), end;
    std::vector<std::string> tokens(beg, end); // done!
		    //cout<<tokens[0]<<"amaa";
		    //for(auto& s: tokens)std::cout << s << endl; //PRINTS INPUT
//tokens is a vector conating input
    if(tokens[0]=="P"){
    	int hexagon = stoi(tokens[1]);
    	int position = stoi(tokens[2]);
    	board.setRing(0,hexagon,position);
    }
    cout<<tokens[0]<<" ring set";

}

}


 

 
