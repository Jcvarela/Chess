#ifndef KING_H
#define KING_H

#include "Unit.h"
#include <string>
#include <vector>

class King: public Unit{


public:
	//constructor 
	King(int row, int col, bool isWhite);
	King();

	//oberide methods
	std::vector <int> canMove();


};



#endif