#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>

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
	static bool isOutBounds(int row, int col); // check if unit goes out of bound 
	void changePosition(int row, int col);

	virtual std::vector<int> canMove(); // return an array with the  location of all posible position for unit


	//true -> its position got change
	//false -> its position didnt got change
	bool moveTo(std::string to); 
	bool attackTo(std::string to);

};

#endif


