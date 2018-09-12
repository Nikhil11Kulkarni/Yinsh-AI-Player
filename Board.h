

#ifndef BOARD_H
#define	BOARD_H

#include<iostream>
#include<fstream>
using namespace std;

class Point{
	int x;
	int y;
	public:
	int getx();
	int gety();
	void setx(int x1);
	void sety(int y1);
}

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

	Point twod_from_hex (Point p);
	
	Point hex_from_twod (Point p);

	/**
     * to set the position of a ring on the board.
     * 
     */
	/**
     * -1 :  empty , 0 : whitering , 1 :blackring , 2 : whitemarker , 3 : blackmarker  
     * 
     */


	void setRing(int ringcolor,int px, int py);// ringid , hexagon , position

	/**
     * to move the position of a ring on the board, and set the board accordingly.
     * 
     */
	void moveRing(int ringcolor, int from_x,int from_y, int to_x,int to_y);

	/**
     * to remove a ring from the board, and set the board accordingly.
     * 
     */
	void removeRing(int opponentID ,int from_x ,int from_y ,int  to_x ,int  to_y ,int ring_removeX ,int ring_removeY);
	// from_x , from_y to to_x to_y ==remove markers here of colour (opponentID+2).
	// remove ring from ring_removeX , ring_removeY
	/**
     * to calculate the evaluation function.
     * 
     */
	float evaluate();

	void getNeighbours(int px,int py, int ringcolor);



}



#endif	/* BOARD_H */


