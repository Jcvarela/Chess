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
	bool isOutBounds(int row, int col); 
	void changePosition(int row, int col);	

	//true -> its position got changed
	//false -> its position didnt get changed
	bool moveTo(std::string to); 
	bool attackTo(std::string to);

};

#endif


