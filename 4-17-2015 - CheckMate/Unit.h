#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>

class Unit{

protected:
	std::string name; //unit name 
	int row, col; //keep track of unit position
	
	bool isWhite;  // -> true if unit is white
				   //    false if unit is black
		
public:
	//row col for every two entries 
	const static int move[], attack[];

	//constant
	Unit(int row, int col, bool isWhite);
	Unit();
	
	//getters 
	int getRow();
	int getCol();
	bool isItWhite();
	std::string getName();

	//setters 
	void setIsItWhite(bool isWhite);


	//check
	static bool isOutBounds(int row, int col); // check if unit goes out of bound 

	//virtual functions
	virtual void changePosition(int row, int col); //setters for row and col
	virtual std::vector<int> canMove(); // return an array with the  location of all posible position for unit
	



};

#endif


