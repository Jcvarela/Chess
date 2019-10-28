#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "Unit.h"

class Block{
	private:
		//A simple check to see if a unit is in the block
		bool hasUnit;
		//Unit in the block
		Unit *unit;
		// Contains the color value of the block (fill or NoFill)
		bool hasColor1;
		// Keeps track where the block is in the board
		int row, col;


		// Add new unit to this block
		Unit* makeUnit(Unit unit);
		// Add new unit by name
		Unit* makeUnit(std::string unit);
	public:
		//Constructor
		Block(int row, int col, bool hasCoolor1, Unit unit);
		Block(int row, int col, bool hasColor1);
		Block();
		//Destructor
		~Block();

		//Getters
		bool itIsColor1();
		bool ithasUnit();
		Unit* getUnit();

		//Setters
		void setUnit(Unit unit);
		void setUnit(std::string name);
		void setUnit();
		void setDefaultUnit();
		void setItHasUnit(bool hasUnit);
		void setPosition(int row,int col);
};

#endif
