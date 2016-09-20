#ifndef BOARD_H
#define BOARD_H


#include "Unit.h"
#include "Block.h"
#include <vector>
#include <string>

class Board{
	const static int row;
	const static int col;

	

public:
	Block **block;
	bool playerOneTurn;

	Board();

	std::string getBoard();
	
	bool moveTo(int frow,int fcol, int trow,int  tcol);
};

#endif