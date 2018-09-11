#ifndef BOARD_H_
#define	BOARD_H_

#include<iostream>
#include<fstream>
using namespace std;

/// I HAVE CHANGED SOMEWHAT IN BOARD.H --ONLY SYNTACTICAL CHANGES (NO LOGICAL CHANGE)

class Board{

public:
	/**
     * Constructor : Creates the empty board with default size corresponding to 5 rings
     * 
     */
	Board();

	/**
     * Constructor : Creates the empty board with default size corresponding to 5 rings
     * 
     */

	Board( int boardsize);

	/**
     * to set the position of a ring on the board.
     * 
     */

	/**
     * -1 :  empty , 0 : whitering , 1 :blackring , 2 : whitemarker , 3 : blackmarker  
     * 
     */


	void setRing(int ringcolor,int px, int py);

	/**
     * to move the position of a ring on the board, and set the board accordingly.
     * 
     */
	void moveRing(int ringcolor, int from_x,int from_y, int to_x,int to_y);

	/**
     * to remove a ring from the board, and set the board accordingly.
     * 
     */
	void removeRing(int ringcolor,int px, int py);
	
	/**
     * to calculate the evaluation function.
     * 
     */
	float evaluate();

	void getNeighbours(int px,int py, int ringcolor);



};

#endif


