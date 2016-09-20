
#include <iostream>
#include <string>
#include "Board.h"
#include <vector>


// Stages
void start();
void wrongInput();
void play();

// methods for play state
void printMovement(std::vector<int> movement);
std::string printInfo(std::string &extra, bool skipFrom, bool kingBeenAttack,bool currentPlayerCanMove, std::string from);
bool checkFrom(int &frow, int &fcol, std::string &from, std::string &extra, bool currentPlayerCanMove);
bool checkTo(int &tcol, int &trow, std::string &to, std::string &extra, std::vector<int> movement, bool &skipFrom, std::string from);
bool contains(std::vector<int> movement, int row, int col);
bool validInput(std::string input, int *row, int *col);		//function from play()<< checks for input correctness and sets the column and row values for that piece
std::string choosePromotion();// peon gets promoted

const int startPage = -200050000;							// # main stage

int scene = startPage; //  what scene the player is, start, wronginput, play

static Board board;

int main(){

	while(scene != 2){
		
		switch(scene){
		case startPage:
			start();
			break;
		case 1:
			play();
			break;
		case 2:
			break;
		default:
			wrongInput();
			break;
		}
		system("cls"); //clear screen
	}
}


void start(){

	std::string title = "";
	title = "\t\t #### #### ####      #### #### ##       \n";
	title+= "\t\t ####      ####      #### #  # ####     \n";
	title+= "\t\t           ####      ####        ###    \n";
	title+= "\t\t #### #### ####      #### #  # ####     \n";
	title+= "\t\t #### #### ####      #### #### ##       \n";
	title+= "\t\t ####                ####               \n";
	title+= "\t\t ####      ####      ####               \n";
	title+= "\t\t #### #### ####      ####               \n";
	
	
	title += "\n\n\n\t\t\t\t";
	title += "Options:\n";
	title += "\t\t\t\t";
	title += "1->Start Game\n";
	title += "\t\t\t\t";
	title += "2->Exit\n";

	std::cout << title; 
	std::cin >> scene;

}


void wrongInput(){
	std::string title = "";
	title = "\t\t #### #### ####      #### #### ##       \n";
	title+= "\t\t ####      ####      #### #  # ####     \n";
	title+= "\t\t           ####      ####        ###    \n";
	title+= "\t\t #### #### ####      #### #  # ####     \n";
	title+= "\t\t #### #### ####      #### #### ##       \n";
	title+= "\t\t ####                ####               \n";
	title+= "\t\t ####      ####      ####               \n";
	title+= "\t\t #### #### ####      ####               \n";
	
	
	


	title += "\n\n\n\t\t";
	title += "Wrong Input, pick one of the option below\n";
	title += "\t\t\t\t";
	title += "1->Start Game\n";
	title += "\t\t\t\t";
	title += "2->Exit\n";

	std::cout << title;
	std::cin >>scene;

}


//play method
void play(){

	std::getline(std::cin, std::string()); //get rid of the first line
	board = Board();
	scene = startPage;

	std::string from = "", to = "";
	std::string extra = "";
	int frow,fcol;
	int trow,tcol;

	bool kingBeenAttack = false;
	bool currentPlayerCanMove = false;
	bool skipFrom = false;
	std::vector<int> movement;


	while (from.compare("-1") != 0 && to.compare("-1")){
		system("cls"); //clear screen
		
		kingBeenAttack = Board::isYourKingBeenAttack();
		currentPlayerCanMove = Board::checkIfPlayerHaveMovement();

		std::cout << printInfo(extra,skipFrom,kingBeenAttack,currentPlayerCanMove,from); // prints board and info




		if(!skipFrom){ // set the values from

			if (checkFrom(frow, fcol, from, extra, currentPlayerCanMove)){
				skipFrom = true;
				movement = board.block[frow][fcol].getUnit()->canMove();
			}
			else {
				continue;
			}

		}
		//extra
		printMovement(movement);

		if (checkTo(tcol, trow, to, extra, movement, skipFrom, from)){
			Board::addHistory(frow, fcol, trow, tcol);
			Board::moveTo(frow, fcol, trow, tcol);

			if (Board::block[trow][tcol].getUnit()->getName().at(1) == 'P' && (trow == 0 || trow == 7)){ //Peon got promoted
				 
				Board::setPromotion( (Board::playerOneTurn? "W":"B") + choosePromotion() );
			}


			skipFrom = false;
			board.playerOneTurn = !board.playerOneTurn;
		}
		else {
			continue;
		}
	}
}


//prints the information needed in the play state before getting input

std::string printInfo(std::string &extra, bool skipFrom, bool kingBeenAttack, bool currentPlayerCanMove, std::string from){
	std::string output = board.getBoard();

	output +=  "\t\t\t";
	output +=  (board.playerOneTurn ? "White Turn:\n" : "Black Turn:\n");
	output += "\t\t\t-1 Go to Main Menu\n";
	
	if (Board::history.size() != 0){ 	output += "\t\t\t-3 Go back\n"; 	}
	
	if (!currentPlayerCanMove){

		if (kingBeenAttack){
			output += "\n\t\t\tCHECK MATE\n";
			output += (Board::playerOneTurn ? "\t\t\tBLACK WON\n" : "\t\t\tWHITE WON\n");
		}
		else {
			output += "\n\t\t\tDRAW\n";
			output += (Board::playerOneTurn?"\t\t\tWHITE CANT MOVE":"\t\t\tBLACK CANT MOVE");
		}
	}
	else {

		output += "\t\t\t-5 to change from\n";

		if (kingBeenAttack){ output += "\n\n\t\t\t\tCHECK!!!\n"; }

		if (Board::history.size() != 0){
			output += "\n\t\t\t\tHistory\n";
			output += board.printHistory();
		}

		if (skipFrom){ output += "From -> " + from + "\n"; }

		if (extra.compare("") != 0){ output += "\n" + extra + "\n"; }

	}


	extra = "";
	return output;
}

//get the input values from 
//false if input is invalid 
//true  if input is valid
bool checkFrom(int &frow, int &fcol, std::string &from, std::string &extra, bool currentPlayerCanMove){



	std::cout << "From -> ";
	std::getline(std::cin, from); //gets the line

	if (from.compare("-1") == 0){
		return false;
	}

	if (from.compare("-3") == 0){ // go back option
		if (Board::history.size() == 0){
			extra = "Invalid Option\n";
		}
		else {
			Board::goback();
			Board::playerOneTurn = !Board::playerOneTurn;
		}
		return false;
	}

	if (!currentPlayerCanMove){ //if current player cannot move go with error
		extra = "Invalid Option\n";
		return false;
	}



	if (from.compare("-5") == 0){ // can't change from value
		extra = "Invalid Option\n";
		return false;
	}

	
	if (!validInput(from, &frow, &fcol)){
		extra = from + "is an invalid Input. Must be a number(1 - 7) and a character (a - h)\n";
		return false;
	}


	if (!board.block[frow][fcol].ithasUnit() || (board.block[frow][fcol].getUnit()->isItWhite() != board.playerOneTurn)){
		extra = "You don't have any units at "+ from+"\n";
		return false;
	}
	
	return true;
}


//get the input value to 
//false if input is invalid 
//true if input is valid
bool checkTo(int &tcol, int &trow, std::string &to, std::string &extra, std::vector<int> movement, bool &skipFrom, std::string from){
	std::cout << "To   -> ";
	std::getline(std::cin, to);

	if (to.compare("-1") == 0){ // go back to main menu
		return false;
	}

	if (to.compare("-5") == 0){ // change from output
		skipFrom = false;
		return false;
	}

	if (to.compare("-3") == 0){ 
		if (Board::history.size() == 0){ // cant go back
			extra = "Invalid Option\n";
		}
		else { // go back to last play
			skipFrom = false;
			Board::goback();
			Board::playerOneTurn = !Board::playerOneTurn;
		}
		return false;
	}

	if (!validInput(to, &trow, &tcol)){
		extra = to + "-> Invalid Input. Must be a number(1 - 7) and a character (a - h)\n";
		return false;
	}

	if (!contains(movement, trow, tcol)){
		extra = "Unit at " + from + " can't move to " + to +"\n";
		return false;
	}

	return true;

}


//check if position row and col are in vector of movment 
bool contains(std::vector<int> movement, int row, int col){

	for (unsigned int i = 0; i < movement.size(); i +=2){

		if (movement[i] == row && movement[i + 1] == col){
			return true;
		}

	}

	return false;
}


//invalid input if return false
//also sets the value of row and col if is true 
bool validInput(std::string input,int *row,int *col){

	if(input.length() != 2){
		return false;
	}

	*row = input.at(1) - '1';
	
	if(*row < 0 || *row > 7){

		*row = input.at(0) - '1';
		if(*row < 0 || *row > 7){
			return false;
		} 
		else {
			*col = input.at(1) - 'a';

			if(*col < 0 || *col > 7){
				*col = input.at(1) - 'A';

				if(*col < 0 || *col >7)
					return false;
				else return true;
			} 
			else return true;
		}
	} else {

		*col = input.at(0) - 'a';

			if(*col < 0 || *col > 7){
				*col = input.at(0) - 'A';

				if(*col < 0 || *col >7)
					return false;
				else return true;
			} 
			else return true;
	}

	return true;
}


//given an array of numbers { 5,2 7,1 ... } prints the position in forms of a letter an a number
//exp 0,0, -> A1 and 5,2 -> C6
void printMovement(std::vector<int> movement){
	
	std::string value = "";
	for (unsigned int i = 0; i < movement.size(); i += 2){
		switch (movement[i + 1]){
		case 0:
			std::cout << "A";
			break;
		case 1:
			std::cout << "B";
			break;
		case 2:
			std::cout << "C";
			break;
		case 3:
			std::cout << "D";
			break;
		case 4:
			std::cout << "E";
			break;
		case 5:
			std::cout << "F";
			break;
		case 6:
			std::cout << "G";
			break;
		default:
			std::cout << "H";
			break;
		}
		std::cout << movement[i] +1  << "  ";

	}
	std::cout << "\n";

}

std::string choosePromotion(){

	std::string input = "";
	bool check = true;

	while (check){

		if (input.compare("") != 0){
			std::cout << "\n Wrong input\n";
		}

		std::cout << "\n\tPick Promotion:";
		std::cout << "\n\tQ for Queen";
		std::cout << "\n\tR for Rook ";
		std::cout << "\n\tB for Bishop ";
		std::cout << "\n\tN for Knight ";

		std::getline(std::cin, input);

		if (input.compare("Q") == 0){ check = false; }
		else if (input.compare("R") == 0) { check = false; }
		else if (input.compare("B") == 0) { check = false; }
		else if (input.compare("N") == 0) { check = false; }

		std::cout << "\n\n";
	}

	return input;
}