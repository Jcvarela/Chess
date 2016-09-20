#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "Unit.h"

class Block{
private:

	bool hasUnit; //keeps track if theres a unit on this block
	Unit *unit;		//Unit in the block
	
	
	bool hasColor1; //-> true if color is white of block
					//   false if color is black  of block
	
	// keeps track of possition
	int row, col; 

public:

	//constroctor
	Block(int row, int col, bool hasCoolor1, Unit unit);	
	Block(int row, int col, bool hasColor1);			
	Block();
	//destroctor 
	~Block();

	//getters 
	bool itIsColor1(); 
	bool ithasUnit();
	Unit* getUnit();

	//setters 
	void setUnit(Unit unit);
	void setUnit(std::string name);      
	void setUnit();
	void setDefaultUnit();
	void setItHasUnit(bool hasUnit);
	void setPosition(int row,int col);
	
private:
	Unit* makeUnit(Unit unit);// locate memory for unit
	Unit* makeUnit(std::string unit);
};

#endif