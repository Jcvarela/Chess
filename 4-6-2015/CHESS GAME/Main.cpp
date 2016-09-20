#include <iostream>
#include <string>
#include "Board.h"

void start();
void play();
void wrongInput();
bool validInput(std::string input, int *row, int *col);

const int startPage = -200050000;
int scene = startPage;

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
	std::cin >>scene;
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

void play(){
	Board board = Board();
	scene = startPage;

	int *move = NULL;

	std::string from = "", to = "";
	std::string extra = "";

	int frow,fcol;
	int trow,tcol;

	bool skipFrom = false;
	

	while (from.compare("-1") != 0 && to.compare("-1")){
		system("cls");
		

		std::cout << board.getBoard();

		std::cout << "\t\t\t";
		std::cout << (board.playerOneTurn?"First Player Turn:\n":"Second Player Turn:\n");
		std::cout << "\t\t\t-1 Go to Main Menu\n";
		if(skipFrom)
			std::cout << "\t\t\t-5 to change from\n"; 

		if(extra.compare("") != 0)
			std::cout << extra;

		extra = "";

		if(skipFrom){
			skipFrom = !skipFrom;
		}
		else {
			std::cin >> from;

			if(from.compare("-1") == 0)
				break;

			if(!validInput(from,&frow,&fcol)){
				extra = from + "-> Invalid Input. Must be a number(1 - 7) and a character (a - h)\n";
				continue;
			}
			 
			if(!board.block[frow][fcol].ithasUnit() && (board.block[frow][fcol].getUnit().isItWhite() == board.playerOneTurn)){
				extra = "There are no units in that block\n";
				continue;
			}

			skipFrom = true;
		}
		

		std::cin >> to;
		if(to.compare("-1") == 0)
			break;
		if(!validInput(to,&trow,&tcol)){
			extra = to + "-> Invalid Input. Must be a number(1 - 7) and a character (a - h)\n";
			continue;
		}

		board.moveTo(frow,fcol,trow,tcol);

		skipFrom = false;
		board.playerOneTurn = !board.playerOneTurn;
	}
	
}


//invalid input if return false and get row and col
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