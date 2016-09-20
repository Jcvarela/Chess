#ifndef KING_H
#define KING_H

#include "Unit.h"
#include <string>

class King: public Unit{
public:
	King(int row, int col, bool isWhite);
	King();

};



#endif