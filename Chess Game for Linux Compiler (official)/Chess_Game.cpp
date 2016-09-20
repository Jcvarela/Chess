
#include <vector>
#include <string>
#include <sstream>
#include <iostream>


//------------------CLASSES-----------------------------------------------------------------------------


// All units in the extends from this clas Pawn, Bishop, Knight, Rook, Queena and King
class Unit{ 

protected:
	
	// keeps track of the unit name with two characters
	// name[0] will be the color of the unit "W" for white and "B" for black
	// name[1] will keep track of the unit: "P" for Pawn, "B" for Bishp, "N" for Knight, "R" for Rook, "Q" for queen and "K" for king
	std::string name;  
	int row, col; //keep track of positpion of unit in board
	
	bool isWhite;  // -> true if unit is white
				   //    false if unit is black
		
public:

	//constroctors
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
	//true if it goes out of bound
	//elsewise
	static bool isOutBounds(int row, int col); 

	//virtual functions
	virtual void changePosition(int row, int col); //setters for row and col
	virtual std::vector<int> canMove(); // return an array with the  location of all posible position for unit
};

class Pawn: public Unit{

public:
	Pawn(int row, int col, bool isWhite);
	Pawn();
	
	//overide function
	std::vector<int> canMove();

};

class Bishop: public Unit{
public:
	Bishop(int row, int col, bool isWhite);
	Bishop();
	
	//overide function
	std::vector<int> canMove();
	
};

class Knight: public Unit{
public:
	Knight(int row, int col, bool isWhite);
	Knight();
	
	//overide function
	std::vector<int> canMove();
};

class King: public Unit{


public:
	King(int row, int col, bool isWhite);
	King();

	//overide function
	std::vector <int> canMove();
};


// Keeps track of a specific block of the board
class Block{ 
private:
	
	//true if block has unit
	// false if it dosen't
	bool hasUnit; 
	
	//keeps track of the unit if it has one
	Unit *unit;	
	
	//true if color is white
	//false if color is black
	bool hasColor1; 
	
	// keeps track of position of the block
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


//All methods in the board are static
class Board{

public:
	
	//board contains 64 blocks
	static Block **block;

	//true if its whites turn
 	//false if its black turn
	static bool playerOneTurn;
	
	//keeps track of the position of the kings
	static int wKing[], bKing[]; // {row,col, how many time it move}
	
	//keeps track of rooks position and how many time they move
	static int white_left_rook[], white_right_rook[];
	static int black_left_rook[], black_right_rook[];


	
	//option, rowF, colF, rowT, colT , name 
	//option 1 -> move												-> size = 7
	//option 2 -> eat, add extra name of who got eaten				-> size = 9
	//option 3 -> Castling											-> size = 7
	//option 4 -> Promotion, extra name								-> size = 9								
	//option 5 -> En passant, add extra name and its position		-> size = 11
	
	//exp 10203WK -> 1 means: Unit move from (0,2) to (0,3) and it was the white king 
	static std::vector<std::string> history; 
	
	
	
	//constructor
	Board();
	
				

	//move unit from (frow,fcol) to (trow,tcol) 
	static bool moveTo(int frow,int fcol, int trow,int  tcol);

	//check if unit at (row2,col2) can attack (row,col)
	static bool piecesWhat(int row, int col, int row2, int col2);
	
	//check if position at (m,n) is been attack by enemy units
	static bool beingAttacked(int row, int col);

	//true your king is udner attack
	//false false your king is not under attack
	static bool isYourKingBeenAttack();

	// true if your king has move
	// false if your king hasen't move
	static bool yourKingMove();
	
	// true if rook at specific position move
	// false otherwise
	static bool rook_at_pos_move(int row,int col);
	
	// check if a unit can move to position with out king been in check
	// return true if you can move 
	// return false if king is under attack or u cant move there 
	static bool checkIfUnitCanMove(int row, int col);
	
	//return true if player at this turn can make at least one movement
	//return false if player at this turn cant make anymovements meaning tie or checkmate
	static bool checkIfPlayerHaveMovement();
	
	
	
	

	//retrunsthe the last 5 movement maid in the game
	static std::string printHistory();

	// add to history
	static void addHistory(int frow, int fcol, int trow, int  tcol);
	
	//goes back
	// true -> if it can go back 
	// false -> history is empty
	static  bool goback();

	//peopn gets promoted && and add to history
	static void setPromotion(std::string name);

	//set the board to it's default value
	static void InitializeBoard();




	//returns a string with the entire board ready to print
	std::string getBoard();		
};



class Rook: public Unit{
public:
	Rook(int row, int col, bool isWhite);
	Rook();
	
	//overide methods
	std::vector<int> canMove();
	
	//return true if block has an enemy unit
	bool hasEnemy(Block *b); 

};

class Queen: public Unit{
public:
	Queen(int row, int col, bool isWhite);
	Queen();
	
	//overide methods
	std::vector<int> canMove();
	
	//return true if block has an enemy unit
	bool hasEnemy(Block *b);
};


//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//--------------------------------------setting Unit class methods---------------------------------------------

//constroctors
 Unit::Unit(int row, int col, bool isWhite){
	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;
	 this->name = (isWhite)?std::string("W"):std::string("B");
	 this->name += std::string("U");
 }
 Unit::Unit(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = std::string("WU");
 }

 //getters
 int Unit::getRow(){ return this->row; }
 int Unit::getCol(){ return this->col; }
 bool Unit::isItWhite(){return this->isWhite; }
 std::string Unit::getName(){  return this->name;}


 //setters 
 void Unit::changePosition(int row, int col){
	 this->row = row;
	 this->col = col;
 }
 void Unit::setIsItWhite(bool isWhite){	 this->isWhite = isWhite;}
 


 // return true if is out of bound
 //			false if is in bound
 bool Unit::isOutBounds(int row, int col){ return !(row >= 0 && row <= 7 && col >= 0 && col <= 7); }

 //default canMove function return all values 
 std::vector<int> Unit::canMove(){

	 std::vector<int> movement; // {row, col}

	 for (int i = 0; i < 8; i ++){
		 for (int j = 0; j < 8;j ++){
			 movement.push_back(i);
			 movement.push_back(j);
		 }
	 }
	 return movement;
 }



//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//--------------------------------------setting Pawn class methods---------------------------------------------


 Pawn::Pawn(int row, int col, bool isWhite){
	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;
	 this->name = (isWhite)?"W":"B";
	 this->name += "P";
 }

 Pawn::Pawn(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WP";
 }

 
 //This function returns a vector with all posible movements of this specific pawn
 std::vector<int> Pawn::canMove(){

	 // every two elements will be compose of row and col so peon has 4 movments 
	 //{-1,0, -2,0, -1,-1, -1,1}
	 std::vector<int> movement;  // return this value            
	 
	 //Block is a static array in the Board class
	 //doing this will alow you to get all the information from the board
	 Block** board = Board::block; 

	 board[row][col].setItHasUnit(false);//remove from board to check movements

	 int mult = (this->isWhite ? 1 : -1); 



	 //Checks if pawn can move to the block in front of it (one space)
	 if (!this->isOutBounds(row + (-1)*mult, col) && !board[row + (-1)*mult][col].ithasUnit()){

		 if (Board::checkIfUnitCanMove(row + (-1)*mult, col)){
			 movement.push_back(row + (-1)*mult);
			 movement.push_back(col);
		 }
	 }

	 //Checks if pawn can move to the block in front of it (two spaces)
	 if (( (isWhite && row == 6)  ||  (!isWhite && row == 1)  ) && !board[row + (-2)*mult][col].ithasUnit() && !board[row + (-1)*mult][col].ithasUnit()){
		 

		 if (Board::checkIfUnitCanMove(row + (-2)*mult, col)){
			 movement.push_back(row + (-2)*mult);
			 movement.push_back(col);
		 }


	 }
	 //Checks if pawn can move/attack to the diagonal (right block)
	 if (!this->isOutBounds(row + (-1)*mult, col + 1) && board[row + (-1)*mult][col + 1].ithasUnit() && (this->isWhite != board[row + (-1)*mult][col + 1].getUnit()->isItWhite())){
		

		 if (Board::checkIfUnitCanMove(row + (-1)*mult, col + 1)){
			 movement.push_back(row + (-1)*mult);
			 movement.push_back(col + 1);
		 }
	 }
	 //Checks if pawn can move/attack to the diagonal (left block)
	 if (!this->isOutBounds(row + (-1)*mult, col - 1) && board[row + (-1)*mult][col - 1].ithasUnit() && (this->isWhite != board[row + (-1)*mult][col - 1].getUnit()->isItWhite())){
		

		 if (Board::checkIfUnitCanMove(row + (-1)*mult, col - 1)){
			 movement.push_back(row + (-1)*mult);
			 movement.push_back(col - 1);
		 }
	 }
	 


	 //check peon al paso
	 if (Board::history.size() > 0){
		 std::string before = Board::history[Board::history.size() - 1];

		 int frow = before.at(3) - '0';
		 int trow = before.at(1) - '0';
		 int tcol = before.at(2) - '0';


		 if (before.substr(6, 1).compare("P") == 0 && ((frow - trow) == 2 || (frow - trow) == -2)){ // last movement was a peon and its stared with double jump

			 if ((tcol - col == 1 || tcol - col == -1) && row == frow){ // if the difference between columes is 1 and they are at the same row then pawn can do En passant


				 if (Board::checkIfUnitCanMove(row + (-1)*mult, tcol)){
					 movement.push_back(row + (-1)*mult);
					 movement.push_back(tcol);
				 }


			 }
		 }

	 }
	 board[row][col].setItHasUnit(true); //put unit back in the baord
	 return movement;
 }
 

 
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------
//--------------------------------------setting Bishop class methods---------------------------------------------

Bishop::Bishop(int row, int col, bool isWhite){
	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;
	 this->name = (isWhite)?"W":"B";
	 this->name += "B";
 }

 Bishop::Bishop(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WB";
 }
 
 std::vector<int> Bishop::canMove(){
	 std::vector<int> movement;
	 Block** board = Board::block;
	 
	 board[row][col].setItHasUnit(false);//remove from board to check movements

	 for (int i = 0; i < 4; i++)
	 {
		 
		 for (int j = 1; j < 8; j++){
			 int k = 0;
			 int p = 0;
			 switch (i){
			 case 0:
				 k = row - j ;
				 p = col + j ;
				 break;
			 case 1:
				 k = row + j;
				 p = col + j ;
				 break;
			 case 2:
				 k = row - j;
				 p = col - j;
				 break;
			 default:
				 k = row + j;
				 p = col - j;
				 break;

			 }
				if (this->isOutBounds(k, p)){
					break;
				}
				else{ 
					if (board[k][p].ithasUnit() ){
						
						if (Board::checkIfUnitCanMove(k,p)){
							movement.push_back(k);
							movement.push_back(p);
						}
						break;
					}
					else if (Board::checkIfUnitCanMove(k, p)){
						movement.push_back(k);
						movement.push_back(p);
					}
				}
		 }
		

	 }

	 board[row][col].setItHasUnit(true); //put unit back in the baord
	 return movement;
 }



//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//--------------------------------------setting Knight class methods---------------------------------------------

 
 Knight::Knight(int row, int col, bool isWhite){
	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;
	 this->name = (isWhite)?"W":"B";
	 this->name += "N";
 }

 Knight::Knight(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WN";
 }

 
std::vector<int> Knight::canMove(){
 	
	std::vector<int>movement;
	Block** board = Board::block;
	
	board[row][col].setItHasUnit(false);//remove from board to check movements

	int potentialMovement[]={-1,2, -2,1, 1,2, 2,1, 2,-1, 1,-2, -1,-2, -2,-1};
 	for (int i = 0; i <16; i+=2)
 	{

		int k = row + potentialMovement[i];
		int p = col + potentialMovement[i + 1];

 		if (!this->isOutBounds(k,p)){//checks if it goes out of bounds
			//then checks if there is a unit on the square and checks what color that unit is

			if (Board::checkIfUnitCanMove(k,p)){
				movement.push_back(k);
				movement.push_back(p);
			}
		}
	}

	board[row][col].setItHasUnit(true); //put unit back in the baord

	return movement;
 }
 


//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//--------------------------------------setting Rook class methods---------------------------------------------

Rook::Rook(int row, int col, bool isWhite){

	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;
	 this->name = (isWhite)?"W":"B";
	 this->name += "R";
 }

 Rook::Rook(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WR";
 }

 std::vector<int> Rook::canMove(){
	 bool continuesUp, continuesDown, continuesRight, continuesLeft;
	 continuesUp = continuesDown = continuesRight = continuesLeft = true;

	 std::vector<int> movement;				//This vector contains an even number of values, pairing values for every posible move the Rook can move
	 
	 Block** board = Board::block;		//We are creating a 2d array of Block pointers, to asign the static value of our board (WE are getting the value of [Block** block] in class Board and asigning it to our board) 

	 board[row][col].setItHasUnit(false);//remove from board to check movements

	 for(int i=1; i<=7; i++){			//This loop will go (UP TO) 7 places up, down, left and right checking for posible moves for our Rook

		 if (continuesDown && !this->isOutBounds(row, col + i) && (hasEnemy(&board[row][col + i]) || !board[row][col + i].ithasUnit())){  //We check for columns down the board
			 if (hasEnemy(&board[row][col + i]))			/*_________________________________________ */
				 continuesDown = false;						/*|NOTE:								   |*/
			 if (Board::checkIfUnitCanMove(row, col + i)){	/*|If we find a unit either friend or enemy|*/
				 movement.push_back(row);					/*|we set the continue Boolean to false    |*/
				 movement.push_back(col + i);				/*|since we can't check past any unit      |*/
			 }												/*|________________________________________|*/

		 }
		 else continuesDown = false;

		 if (continuesUp && !this->isOutBounds(row, col - i) && (hasEnemy(&board[row][col-i]) || !board[row][col-i].ithasUnit())){  //We check for columns up the board
			 if(hasEnemy(&board[row][col-i]))		
				 continuesUp = false;

			 if (Board::checkIfUnitCanMove(row, col - i)){
				 movement.push_back(row);
				 movement.push_back(col - i);
			 }
		 }													
		 else continuesUp=false;


		 if (continuesRight && !this->isOutBounds(row + i, col) && (hasEnemy(&board[row+i][col]) || !board[row+i][col].ithasUnit())){  //We check for columns to the right of board
			 if(hasEnemy(&board[row+i][col]))			
				 continuesRight=false;					
			

			 if (Board::checkIfUnitCanMove(row + i, col )){
				 movement.push_back(row + i);
				 movement.push_back(col);
			 }
				
		 }												
		 else continuesRight=false;


		 if (continuesLeft && !this->isOutBounds(row - i, col) && (hasEnemy(&board[row-i][col]) || !board[row-i][col].ithasUnit())){  //We check for columns to the left of the board
			 if(hasEnemy(&board[row-i][col]))			
				 continuesLeft=false;					
			
			 if (Board::checkIfUnitCanMove(row - i,col)){
				 movement.push_back(row -i);
				 movement.push_back(col);
			 }
				
		 }												
		 else continuesLeft=false;


	 }


	 board[row][col].setItHasUnit(true); //put unit back in the baord
	 return movement;


 }


 //This function checks if a block has an enemy unit
 bool Rook::hasEnemy(Block *b){

	 if(!b->ithasUnit())		//If no unit is found in the block return false
		 return false;
	 else if(this->isWhite==(b->getUnit()->isItWhite()))	//If the unit found is the same color return false
		 return false;
	 else							//If the unit found is enemy return true
		 return true;

 }





//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//--------------------------------------setting Queen class methods---------------------------------------------



Queen::Queen(int row, int col, bool isWhite){
	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;
	 this->name = (isWhite)?"W":"B";
	 this->name += "Q";
 }

 Queen::Queen(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WQ";
 }

 std::vector<int> Queen::canMove(){
	 bool continues = true;
	 int A[16] = {1,1,  1,0,  1,-1,  0,-1,  -1,-1,  -1,0,  -1,1,  0,1};

	 std::vector<int> movement;				//This vector contains an even number of values, pairing values for every posible move the Rook can move

	 Block** board = Board::block;		//We are creating a 2d array of Block pointers, to asign the static value of our board (WE are getting the value of [Block** block] in class Board and asigning it to our board) 

	 board[row][col].setItHasUnit(false);//remove from board to check movements

	 for (int i = 0; i < 16; i += 2){
		 for (int j = 1; j <= 7; j++){

			 int m = A[i] * j + row;
			 int n = A[i + 1] * j + col;

			 if (continues && !this->isOutBounds(m, n) && (hasEnemy(&board[m][n]) || !board[m][n].ithasUnit())){

				 if (hasEnemy(&board[m][n]))			
					 continues = false;
				 if (Board::checkIfUnitCanMove(m, n)){
					 movement.push_back(m);
					 movement.push_back(n);
				 
				 }

			 }
			 else continues = false;
		 }
		 continues = true;
	 }

	 board[row][col].setItHasUnit(true); //put unit back in the baord
	 return movement;
 }

 //This function checks if a block has an enemy unit
 bool Queen::hasEnemy(Block *b){

	 if (!b->ithasUnit())		//If no unit is found in the block return false
		 return false;
	 else if (this->isWhite == (b->getUnit()->isItWhite()))	//If the unit found is the same color return false
		 return false;
	 else							//If the unit found is enemy return true
		 return true;

 }



//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//--------------------------------------setting King class methods---------------------------------------------


//constructor 
 King::King(int row, int col, bool isWhite){
	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;
	 this->name = (isWhite)?"W":"B";
	 this->name += "K";
 }
 King::King(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WK";
 }


 std::vector <int> King::canMove(){
	 int arrays[16]= { -1,-1,   -1, 0,   -1, 1,   0, 1,   1,1,   1, 0,   1, -1,   0, -1 };
	 
	 Board b = Board();
	 Block** board = b.block;
	 
	 std::vector <int> movement;
	 
	 board[row][col].setItHasUnit(false);//remove from board to check movements

	 //checks all 8 possible mvoement
	 for (int i = 0; i < 16; i+=2){
		 int m = row + arrays[i];
		 int n = col + arrays[i + 1];

		 if (!this->isOutBounds(m, n)	 &&		!Board::beingAttacked(m, n)		 &&		(!board[m][n].ithasUnit()	 ||		this->isWhite != board[m][n].getUnit()->isItWhite())){
			 movement.push_back(m);
			 movement.push_back(n);
		 }
	}

	 int rowloc = (isWhite ? 7 : 0);


	//check if it can casteling
	 if (!Board::yourKingMove() && !Board::beingAttacked(row,col)){ // check if king hasent move and king is not been attack
		
		 if (!Board::rook_at_pos_move(rowloc, 0)){ //rook hase't move
			 //check if the 3 blocks at the left are empty and are not under attack... 3rd blokc has to be empty
			 if (!board[rowloc][col - 1].ithasUnit() && !Board::beingAttacked(rowloc, col - 1) && !board[rowloc][col - 2].ithasUnit() && !Board::beingAttacked(rowloc, col - 2) && !board[rowloc][col - 3].ithasUnit()){
				 movement.push_back(rowloc);
				 movement.push_back(col - 2);
			 }
		 }

		 if (!Board::rook_at_pos_move(rowloc, 7)){ //rook hase't move
			 //check if the 2 blocks at the right are empty and are not under attack
			 if (!board[rowloc][col + 1].ithasUnit() && !Board::beingAttacked(rowloc, col + 1) && !board[rowloc][col + 2].ithasUnit() && !Board::beingAttacked(rowloc, col  + 2)){
				 movement.push_back(rowloc);
				 movement.push_back(col + 2);
			 }
		 }

	 }


	board[row][col].setItHasUnit(true); //put unit back in the baord
	return movement;
 }





//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//--------------------------------------setting Block class methods---------------------------------------------

//constroctor
Block::Block(int row, int col, bool hasColor1, Unit unit){
	this->row = row;
	this->col = col;
	this->hasColor1 = hasColor1;
	this->unit = makeUnit(unit);
	this->hasUnit = true;
}
Block::Block(int row, int col, bool hasColor1){
	this->row = row;
	this->col = col;
	this->hasColor1 = hasColor1;
	this->hasUnit = false;
	this->unit = makeUnit(Unit(0,0,true)); //default unit
}
Block::Block(){
	this->hasColor1 = true;
	this->hasUnit = false;
	this->row = 0;
	this->col = 0;
	this->unit = makeUnit(Unit(0,0,true));
}

//destroctor
Block::~Block(){
	delete this->unit;
	this->unit = NULL;
}



//getters 

bool Block::itIsColor1(){ return this->hasColor1; }
bool Block::ithasUnit(){ return this->hasUnit; }
Unit* Block::getUnit(){	return this->unit; }



//setters
void Block::setUnit(Unit unit){ setUnit(unit.getName()); }

void Block::setUnit(std::string name){
	this->hasUnit = true;
	delete this->unit;
	this->unit = makeUnit(name);
}

void Block::setUnit(){ 
	this->hasUnit = false;
	delete this->unit;
	this->unit = makeUnit(Unit(0, 0, true));
}

void Block::setDefaultUnit(){
	this->hasUnit = false;
	this->unit = makeUnit(Unit(0,0,true));
}

void Block::setItHasUnit(bool hasUnit){

	this->hasUnit = hasUnit;
}

void Block::setPosition(int row, int col){
	this->row = row;
	this->col = col;
}


//private methods 

Unit* Block::makeUnit(Unit unit){
	return makeUnit(unit.getName());
}
Unit* Block::makeUnit(std::string unit){
	Unit *ans = NULL;

	if (unit.substr(1, 1).compare("P") == 0){
		ans = new Pawn(row, col, unit.at(0) == 'W');
	}
	else if (unit.substr(1, 1).compare("R") == 0){
		ans = new Rook(row, col, unit.at(0) == 'W');
	}
	else if (unit.substr(1, 1).compare("B") == 0){
		ans = new Bishop(row, col, unit.at(0) == 'W');
	}
	else if (unit.substr(1, 1).compare("N") == 0){
		ans = new Knight(row, col, unit.at(0) == 'W');
	}
	else if (unit.substr(1, 1).compare("Q") == 0){
		ans = new Queen(row, col, unit.at(0) == 'W');
	}
	else if (unit.substr(1, 1).compare("K") == 0){
		ans = new King(row, col, unit.at(0) == 'W');
	}
	else {
		ans = new Unit(row, col, unit.at(0) == 'W');
	}

	return ans;
}




//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//--------------------------------------setting Board class methods---------------------------------------------

bool Board::playerOneTurn = true;
Block** Board::block = new Block*[8];

//keeps track of king position and last one of how many time it move
int Board::wKing[] = { 7, 4,0 }; 
int Board::white_left_rook[] = { 0, 0, 0 };
int Board::white_right_rook[] = { 0, 0, 0 };

int Board::bKing[] = { 0, 4,0 }; 
int Board::black_left_rook[] = { 0, 0, 0 };
int Board::black_right_rook[] = { 0, 0, 0 };

std::vector<std::string> Board::history;

//constroctor
Board::Board(){
}


void Board::InitializeBoard(){
	
	Block **b = new Block*[8];

	bool isColor1 = true;
	for(int i = 0; i < 8; i++){
		
		b[i] = new Block[8];

		for(int j = 0; j < 8; j++){
			b[i][j] = Block(i,j,isColor1);
			b[i][j].setDefaultUnit();
			isColor1 = !isColor1;

		}

		isColor1 = !isColor1;
	}


	//black
	b[1][0].setUnit(Pawn(1,0,false));
	b[1][1].setUnit(Pawn(1,1,false));
	b[1][2].setUnit(Pawn(1,2,false));
	b[1][3].setUnit(Pawn(1,3,false));
	b[1][4].setUnit(Pawn(1,4,false));
	b[1][5].setUnit(Pawn(1,5,false));
	b[1][6].setUnit(Pawn(1,6,false));
	b[1][7].setUnit(Pawn(1,7,false));

	b[0][0].setUnit(Rook(0,0,false));
	black_left_rook[0] = 0;
	black_left_rook[1] = 0;
	black_left_rook[2] = 0;
	b[0][1].setUnit(Knight(0,1,false));
	b[0][2].setUnit(Bishop(0,2,false));
	b[0][3].setUnit(Queen(0,3,false));
	b[0][5].setUnit(Bishop(0,5,false));
	b[0][6].setUnit(Knight(0,6,false));
	b[0][7].setUnit(Rook(0,7,false));
	black_right_rook[0] = 0;
	black_right_rook[1] = 7;
	black_right_rook[2] = 0;



	//white
	b[6][0].setUnit(Pawn(1,0,true));
	b[6][1].setUnit(Pawn(6,1,true));
	b[6][2].setUnit(Pawn(6,2,true));
	b[6][3].setUnit(Pawn(6,3,true));
	b[6][4].setUnit(Pawn(6,4,true));
	b[6][5].setUnit(Pawn(6,5,true));
	b[6][6].setUnit(Pawn(6,6,true));
	b[6][7].setUnit(Pawn(6,7,true));

	b[7][0].setUnit(Rook(7,0,true));
	white_left_rook[0] = 7;
	white_left_rook[1] = 0;
	white_left_rook[2] = 0;
	b[7][1].setUnit(Knight(7,1,true));
	b[7][2].setUnit(Bishop(7,2,true));
	b[7][3].setUnit(Queen(7,3,true));
	b[7][5].setUnit(Bishop(7,5,true));
	b[7][6].setUnit(Knight(7,6,true));
	b[7][7].setUnit(Rook(7,7,true));
	white_right_rook[0] = 7;
	white_right_rook[1] = 7;
	white_right_rook[2] = 0;

	b[0][4].setUnit(King(0, 4, false)); //0,4
	bKing[0] = 0; //row
	bKing[1] = 4; // col
	bKing[2] = 0; // how many time has move

	b[7][4].setUnit(King(7, 4, true)); // 7,4
	wKing[0] = 7; //row
	wKing[1] = 4;// col
	wKing[2] = 0;// how many has move




	delete block;
	block =  b;

	playerOneTurn = true;
}



bool Board::moveTo(int frow,int fcol, int trow,int  tcol){

	//keep track of the position of the king if it change
	if (block[frow][fcol].getUnit()->getName().at(1) == 'K'){
		
		int value = fcol - tcol;

		if (block[frow][fcol].getUnit()->getName().at(0) == 'W'){
			wKing[0] = trow;
			wKing[1] = tcol;
			wKing[2]++;


			if (value == 2){ //castling to the left
				moveTo(7,0,7,3);
			}
			else if (value == -2){ //castling to the right
				moveTo(7,7,7,5);
			}
		}
		else {
			bKing[0] = trow;
			bKing[1] = tcol;
			bKing[2]++;


			if (value == 2){ //castling to the left
				moveTo(0, 0, 0, 3);
			}
			else if (value == -2){ //castling to the right
				moveTo(0, 7, 0, 5);
			}
		}


	}



	//keeps track of the position of the rook if it change
	if (block[frow][fcol].getUnit()->getName().at(1) == 'R'){
		
		if (frow == white_left_rook[0] && fcol == white_left_rook[1]){
			white_left_rook[0] = trow;
			white_left_rook[1] = tcol;
			white_left_rook[2]++;
		}
		else if (frow == white_right_rook[0] && fcol == white_right_rook[1]){
			white_right_rook[0] = trow;
			white_right_rook[1] = tcol;
			white_right_rook[2]++;
		}
		else if (frow == black_left_rook[0] && fcol == black_left_rook[1]){
			black_left_rook[0] = trow;
			black_left_rook[1] = tcol;
			black_left_rook[2]++;
		}
		else if (frow == black_right_rook[0] && fcol == black_right_rook[1]){
			black_right_rook[0] = trow;
			black_right_rook[1] = tcol;
			black_right_rook[2]++;
		}
	}



	block[trow][tcol].setUnit(*block[frow][fcol].getUnit()); //chenges the board
	block[trow][tcol].getUnit()->changePosition(trow,tcol); // changes the position of units
	block[frow][fcol].setUnit(); //delete unit
	
	return true;
}
  

//check if block at postion row, col is been attack by enemy untis
 bool Board::beingAttacked(int row, int col){
	 int arrays[16] = { -1, -1,	  -1, 0,   -1, 1,   0, 1,   1, 1,   1, 0,   1, -1,   0, -1 };
	 Block** board = block;

	 bool check = false;


	 int potentialMovement[] = { -1, 2, -2, 1, 1, 2, 2, 1, 2, -1, 1, -2, -1, -2, -2, -1 };

	 for (int i = 0; i < 16; i += 2){ //check if horse can attack that block
		 int k = row + potentialMovement[i];
		 int p = col + potentialMovement[i + 1];
		 if ((k >= 0 && k <= 7 &&  p >= 0 && p <= 7)){ // if is not out of bound

			 if (board[k][p].ithasUnit() && board[k][p].getUnit()->getName().at(1) == 'N' && board[k][p].getUnit()->isItWhite() != playerOneTurn){
				 return true;
			 }
		 }
	 }



	 //this is going to to check the positions where a block can be attacked, spcifically by a turret, pawn, queen, bishop
	 for (int i = 0; i < 16; i+=2){		
		 for (int j = 1; j < 8; j++){
			 int k = arrays[i] * j + row;
			 int p = arrays[i + 1] * j + col;

				if (!Unit::isOutBounds(k, p)){
					 
					if (board[k][p].ithasUnit()){

						if (board[k][p].getUnit()->isItWhite() != playerOneTurn){
							check = piecesWhat(row, col, k, p);
							if (check){
								return check;
							}
						} 
						
						break;
						
					} 
					else {
						continue;
					}

				}
				else { //is out of bound 
					break;
				}
		 }
	 }
	 return check;
}	

 //checks which element is attacking and returns if there is an element that can attack the block
 bool Board::piecesWhat(int row, int col, int row2, int col2){

	 std::string name = block[row2][col2].getUnit()->getName();
	 bool check = false;
	 int m;
	 int n;
	 int mult;

	 switch (name.at(1)){

	 case 'B':

		 if (row2 != row && col2 != col){
			 check = true;
		 }

		 break;
	 case 'R':

		 if (row2 == row || col2 == col){
			 check = true;
		 }
		 break;

	 case 'P':
		 //find a way check for both pawns
		 mult = (block[row2][col2].getUnit()->isItWhite()? -1 : 1); 

		 if ( (row - row2)*mult  == 1 && ( col + 1 == col2  || col - 1 == col2) ){
			 check = true;
		 }

		 break;

	 case 'K':
		 m = row - row2;
		 n = col - col2;

		 if ((m == 1 || m == -1 || m == 0) && (n == 1 || n == -1 || n == 0)){
			 check = true;
		 }

		 break;
	 case 'Q':
		 check = true;
		 break;

	 default:
		 check = false;
		 break;
	 }

	 return check;
 }


 std::string Board::printHistory(){
	 std::string value = "";
	 std::string extra, positionFrom ="", positionTo = "";
	 std::string position_extra = "";


	 //print 5 last plays
	 for (unsigned int i = 1; i <= history.size()  &&   i <= 5; i++){
		 std::ostringstream num;
		 num << i;
		 value += "\t\t\t" + num.str() + ": ";
		 
		 extra = history[history.size() - i];
		 


		 switch(extra.at(0)){
		 case '1': //it move
			 
			 positionFrom = (char)('A' + (extra.at(2) - '0'));
			 positionFrom += (char)('1' + (extra.at(1) - '0'));
			 positionTo = (char)('A' + (extra.at(4) - '0'));
			 positionTo += (char)('1' + (extra.at(3) - '0'));

			 value += "Move " + extra.substr(5,2) +" from " + positionFrom + " to " + positionTo;
			 break;
			 
		 case '2': //it attack

			 positionFrom = (char)('A' + (extra.at(2) - '0'));
			 positionFrom += (char)('1' + (extra.at(1) - '0'));
			 positionTo = (char)('A' + (extra.at(4) - '0'));
			 positionTo += (char)('1' + (extra.at(3) - '0'));

			 value += "Attack " + extra.substr(7, 2) + " at " + positionTo + " from " + positionFrom + " with "+ extra.substr(5,2);
			 break;
			 
		 case '3': //Castling

			 value += "Castling " + extra.substr(5, 2) + " to " + ((extra.at(4) > extra.at(2)) ? "right": "left");
			 break;
		 case '4':
			 positionFrom = (char)('A' + (extra.at(2) - '0'));
			 positionFrom += (char)('1' + (extra.at(1) - '0'));

			 value += "Promote " + extra.substr(5, 2) + " at " + positionFrom + " to " + extra.substr(7, 2);
			break;


		 case '5':
			 positionFrom = (char)('A' + (extra.at(2) - '0'));
			 positionFrom += (char)('1' + (extra.at(1) - '0'));
			 positionTo = (char)('A' + (extra.at(4) - '0'));
			 positionTo += (char)('1' + (extra.at(3) - '0'));

			 position_extra = (char)('A' + (extra.at(9) - '0'));
			 position_extra += (char)('1' + (extra.at(10) - '0'));

			 value += "En passant: Attack " + extra.substr(7, 2) + " at " + position_extra + " by " + extra.substr(5,2) + " from " + positionFrom + " to " + positionTo;
			 break;
		 default:
			 value += extra;
			 break;
		 }//end switch
		value += "\n";
	 }//end for loop

	 return value;
 }



 void Board::addHistory(int frow, int fcol, int trow, int  tcol){
	 std::string h = "";
	 std::ostringstream num;
	 


	 if (block[trow][tcol].ithasUnit()){
		 h = "2"; // means its eating 
	 }
	 else {

		 int value = tcol - fcol;

		 //if unit at from is a king and the distance move is two then is castling
		 if (block[frow][fcol].getUnit()->getName().at(1) == 'K' && (value == 2 || value == -2)){
			 h = "3"; //its castling
		 }
		 else if (block[frow][fcol].getUnit()->getName().at(1) == 'P' && (value != 0)){ //En passant
			 h = "5";
		 }
		 else {
			 h = "1"; //means its moving
		 }

	}
	 
	 if (h.compare("5") == 0){

		 num << frow << fcol << trow << tcol << block[frow][fcol].getUnit()->getName() + block[frow][tcol].getUnit()->getName() << frow << tcol;
		 h += num.str();
		 block[frow][tcol].setItHasUnit(false);

	 }
	 else {
		
		 num << frow << fcol << trow << tcol;
		 h += num.str() + block[frow][fcol].getUnit()->getName();

		 if (block[trow][tcol].ithasUnit()){
			 h += block[trow][tcol].getUnit()->getName();
		 }
	 }


	 history.push_back(h);
 }



 bool Board::goback(){
	
	 if (history.size() == 0){
		 return false;
	 }
	 else{
		 int frow, fcol, trow, tcol;

		 std::string extra = history[history.size() - 1];
		 history.pop_back();

		 switch (extra.at(0)){
		 case '1': //MOVING

			 frow = extra.at(3) - '0';
			 fcol = extra.at(4) - '0';
			 trow = extra.at(1) - '0';
			 tcol = extra.at(2) - '0';
		 
			 moveTo(frow, fcol, trow, tcol);

			 if (block[trow][tcol].getUnit()->getName().at(1) == 'K'){
				
				 if (block[trow][tcol].getUnit()->getName().at(0) == 'W'){  wKing[2] -= 2;	 }
				 else { bKing[2] -= 2; }
				 
			 }
			 else if (block[trow][tcol].getUnit()->getName().at(1) == 'R'){
				
				 if (block[trow][tcol].getUnit()->getName().at(0) == 'W'){
					 if (trow == white_left_rook[0] && tcol == white_left_rook[1]){ white_left_rook[2] -= 2; }
					 else { white_right_rook[2] -= 2; }
				 }
				 else {

					 if (trow == black_left_rook[0] && tcol == black_left_rook[1]){ black_left_rook[2] -= 2; }
					 else { black_right_rook[2] -= 2; };
				 }
			 }

			 break;
			 
		 case '2': //EATING

			 frow = extra.at(3) - '0';
			 fcol = extra.at(4) - '0';
			 trow = extra.at(1) - '0';
			 tcol = extra.at(2) - '0';

			 moveTo(frow, fcol, trow, tcol);
			 block[frow][fcol].setUnit( extra.substr(7, 2) );



			 if (block[trow][tcol].getUnit()->getName().at(1) == 'K'){

				 if (block[trow][tcol].getUnit()->getName().at(0) == 'W'){ wKing[2] -= 2; }
				 else { bKing[2] -= 2; }

			 }
			 else if (block[trow][tcol].getUnit()->getName().at(1) == 'R'){

				 if (block[trow][tcol].getUnit()->getName().at(0) == 'W'){
					 if (trow == white_left_rook[0] && tcol == white_left_rook[1]){ white_left_rook[2] -= 2; }
					 else { white_right_rook[2] -= 2; }
				 }
				 else {

					 if (trow == black_left_rook[0] && tcol == black_left_rook[1]){ black_left_rook[2] -= 2; }
					 else { black_right_rook[2] -= 2; };
				 }
			 }


			 break;

		 case '3': //CASTLING

			 frow = extra.at(3) - '0';
			 fcol = extra.at(4) - '0';
			 trow = extra.at(1) - '0';
			 tcol = extra.at(2) - '0';

			 if (fcol > tcol){ //right
				 moveTo(trow, tcol + 1, trow, 7); //move rook first
				 
				 moveTo(frow, fcol, frow, fcol - 1); //move king 
				 moveTo(frow, fcol - 1, trow, tcol);

				 if (block[trow][tcol].getUnit()->isItWhite()){
					 white_right_rook[2] -= 2;
					 wKing[2] -= 3;
				 }
				 else{
					 black_right_rook[2] -= 2;
					 bKing[2] -= 3;
				 }


			 }
			 else { //left
				 moveTo(trow,tcol - 1,trow,0);
				
				 moveTo(frow, fcol, frow, fcol + 1); //move king 
				 moveTo(frow, fcol + 1, trow, tcol);


				 if (block[trow][tcol].getUnit()->isItWhite()){
					 white_left_rook[2] -= 2;
					 wKing[2] -= 3;
				 }
				 else{
					 black_left_rook[2] -= 2;
					 bKing[2] -= 3;
				 }

			 }
			 break;

		 case '4':
			 frow = extra.at(3) - '0';
			 fcol = extra.at(4) - '0';

			 block[frow][fcol].setUnit( block[frow][fcol].getUnit()->getName().substr(0,1) + "P" ); //set the value at that position back to Peon 
			 goback(); //make peon go back

			 break;
			 
		 case '5':

			 frow = extra.at(3) - '0';
			 fcol = extra.at(4) - '0';
			 trow = extra.at(1) - '0';
			 tcol = extra.at(2) - '0';

			 moveTo(frow, fcol, trow, tcol);
			 
			 block[trow][fcol].setUnit(block[trow][tcol].getUnit()->isItWhite()? "BP":"WP");


		 default: // missing 5
			 break;

		 }// end switch

	 }//end for loop

	return true;
 }


 bool Board::isYourKingBeenAttack(){
	
	 if (playerOneTurn){
		 return beingAttacked(wKing[0], wKing[1]);
	 }
	 else {
		 return beingAttacked(bKing[0],bKing[1]);
	 }
	
 }



 bool Board::checkIfUnitCanMove(int row, int col){

	 bool check = false;

	 if (block[row][col].ithasUnit()){
		
		 if (block[row][col].getUnit()->isItWhite() != playerOneTurn){

			 block[row][col].getUnit()->setIsItWhite(playerOneTurn);
			 check = !isYourKingBeenAttack();
			 block[row][col].getUnit()->setIsItWhite(!playerOneTurn);
		 }
		
	 }
	 else {
		
		 block[row][col].setUnit(Unit(row,col,playerOneTurn));
		 check = !isYourKingBeenAttack();
		 block[row][col].setItHasUnit(false);
	 }


	 return check;
 }

 bool Board::checkIfPlayerHaveMovement(){
	 

	 //go by all the entire board looking for units that belong to current player
	 //if it find that a unit can make a possible movement return true
	 for (int i = 0; i < 8; i++){	 
		 for (int j = 0; j < 8; j++){
		 
			 // theres a unit in this specific block and it belong to current player
			 if (block[i][j].ithasUnit() && block[i][j].getUnit()->isItWhite() == playerOneTurn){
				 
				 if (block[i][j].getUnit()->canMove().size() > 0){ 
					 return true; // unit at block i,j has possible movements
				 }
			 }
		 
		 }
	 
	 }

	 //return false if didnt found a unit that could move
	 return false;
 }



 std::string Board::getBoard(){
	 std::string value = "";

	 value += "      A      B      C      D      E      F      G      H   \n";

	 for (int i = 0; i < 8; i++){				// 

		 value += "    ------ ------ ------ ------ ------ ------ ------ ------\n";
		 for (int j2 = 0; j2 < 3; j2++){
			 if (j2 == 1){
				 std::ostringstream num;
				 num << i + 1;
				 value += " " + num.str() + " |";
			 }else{
				 value += "   |";
			 }
			 for (int j = 0; j < 8; j++){

				 if (!block[i][j].itIsColor1()){

					 if (j2 == 1 && block[i][j].ithasUnit()){
						 value += "  " + block[i][j].getUnit()->getName() + "  ";
					 }
					 else {
						 value += "      ";
					 }
				 }
				 else {

					 if (j2 == 1 && block[i][j].ithasUnit()){
						 value += (char)-37;
						 value += (char)-37;
						 value += block[i][j].getUnit()->getName();
						 value += (char)-37;
						 value += (char)-37;
					 }
					 else {
						 value += (char)-37;
						 value += (char)-37;
						 value += (char)-37;
						 value += (char)-37;
						 value += (char)-37;
						 value += (char)-37;
					 }
				 }

				 value += "|";
			 }
			 if (j2 == 1){
				std::ostringstream num;
				num << i + 1;
				value += " " + num.str() + "\n";
			 }else{
				 value += "\n";
			}
		 }

	 }
	 value += "    ------ ------ ------ ------ ------ ------ ------ ------\n";
	 value += "      A      B      C      D      E      F      G      H   \n";



	 return value;
 }


 bool Board::yourKingMove(){
	 bool check = false;

	 if (playerOneTurn){ //whites
		 check = (wKing[2] != 0); //true if it move
	 }
	 else {
		 check = (bKing[2] != 0); //true if it move
	 }

	 return check;
 }

 bool Board::rook_at_pos_move(int row, int col){
	 
	 bool check = true;
	 
	 if (block[row][col].getUnit()->getName().at(1) != 'R')
		 return true;

	 if (row == white_left_rook[0] && col == white_left_rook[1]){
		 check = (white_left_rook[2] != 0);
	 }
	 else if (row == white_right_rook[0] && col == white_right_rook[1]){
		 check = (white_right_rook[2] != 0);
	 }
	 else if (row == black_left_rook[0] && col == black_left_rook[1]){
		 check = (black_left_rook[2] != 0);
	 }
	 else if (row == black_right_rook[0] && col == black_right_rook[1]){
		 check = (black_right_rook[2] != 0);
	 }

	 return check;
 }


 void Board::setPromotion(std::string name){
	 
	 std::string before = history[history.size() -1];
	 int row = before.at(3) - '0';
	 int col = before.at(4) - '0';
	 
	 if (before.at(0) > '2')
		 return;


	 if (block[row][col].getUnit()->getName().at(1) == 'P' && (row == 0 || row == 7)){
		 
		 block[row][col].setUnit(name); //change block value
		
		 history.push_back("4" + before.substr(3, 2) + before.substr(3, 2) + before.substr(5, 2) + name); //add to history
	 }

 }



//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//--------------------------------------setting Main ---------------------------------------------



//-Stages--------------------------------------------------

void start(); // Main Stage
void wrongInput(); //Wrong input Stage
void play(); //Play Stage

//----Methods for play Stage ------------------------------------------------------------------

//print possible movement from given input
void printMovement(std::vector<int> movement); 

// print the game and option you can do 
std::string printInfo(std::string &extra, bool skipFrom, bool kingBeenAttack,bool currentPlayerCanMove, std::string from);

//check if the first input you put is valid 
// true that is valid
// false that is an invalid input
bool checkFrom(int &frow, int &fcol, std::string &from, std::string &extra, bool currentPlayerCanMove);

//check if the second input you put is valid
// true that is a valid input
//false that is an invalid input
bool checkTo(int &tcol, int &trow, std::string &to, std::string &extra, std::vector<int> movement, bool &skipFrom, std::string from);

//return true if vector movement contains position (row,col)
// false if it dosen't
bool contains(std::vector<int> movement, int row, int col);

//check if input is a valid input
// return true if input is valid and it also set row and col
//return false if input is not valid ONLY
bool validInput(std::string input, int *row, int *col);		

//Print Options for peon to get promoted
std::string choosePromotion();

const int startPage = -200050000; // # for main stage

//keeps track on what Scene the playaer is 
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
		//system("cls"); //clear screen
		std::cout << "\033[2J\033[1;1H";
		std::cout << "\n";
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
	
	board = Board();
	board.InitializeBoard();
	
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
		//system("cls"); //clear screen
		std::cout << "\033[2J\033[1;1H";
		std::cout << "\n";
		
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
	
	//std::getline(std::cin, from); //gets the line
	std::cin >> from;

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
	
	//std::getline(std::cin, to);
	std::cin >> to;

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

		//std::getline(std::cin, input);
		std::cin >>input;

		if (input.compare("Q") == 0){ check = false; }
		else if (input.compare("R") == 0) { check = false; }
		else if (input.compare("B") == 0) { check = false; }
		else if (input.compare("N") == 0) { check = false; }

		std::cout << "\n\n";
	}

	return input;
}



