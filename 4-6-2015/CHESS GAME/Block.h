#ifndef BLOCK_H
#define BLOCK_H

#include "Unit.h"
#include <string>

class Block{
private:
	Unit unit;
	
	bool hasUnit;

	//boc color
	bool hasColor1; // true for color white, false for color black 

public:

	Block(bool hasCoolor1, Unit unit);
	Block(bool hasColor1, int unit);
	Block();

	bool itIsColor1();
	bool ithasUnit();

	Unit getUnit();
	void setUnit(Unit unit);
	void setUnit(int unit);

};



#endif