#ifndef QUEEN_H
#define QUEEN_H

#include "Unit.h"
#include <string>

class Queen: public Unit{
public:
	Queen(int row, int col, bool isWhite);
	Queen();

};



#endif