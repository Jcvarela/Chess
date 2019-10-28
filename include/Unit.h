#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>

class Unit{
	protected:
		std::string name;
		//Keep track of the unit position
		int row, col;
		bool isWhite;

	public:
		//row col for every two entries
		const static int move[], attack[];

		Unit(int row, int col, bool isWhite);
		Unit();

		//Getters
		int getRow();
		int getCol();
		bool isItWhite();
		std::string getName();

		//Setters
		void setIsItWhite(bool isWhite);
		virtual void changePosition(int row, int col);
		//Check if the unit goes out of bound
		static bool isOutBounds(int row, int col);
		//Return an array with the possible location the unit can move
		virtual std::vector<int> canMove();
};

#endif
