#ifndef UNIT_H
#define UNIT_H

#include <string>

class Unit{

protected:
	std::string name;
	int row, col;
	bool isWhite;
		
public:
	//row col for every two entries 
	const static int move[], attack[];

	Unit(int row, int col, bool isWhite);
	Unit();

	int getRow();
	int getCol();
	std::string getName();
	bool isItWhite();
	

	//true -> its position got change
	//false -> its position didnt got change
	bool moveTo(std::string to); 
	bool attackTo(std::string to);

};

#endif


