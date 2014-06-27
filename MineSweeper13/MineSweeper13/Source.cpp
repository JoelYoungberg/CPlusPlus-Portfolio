//Joel R. Youngberg
//Minesweeper Game
//CSC 7 Discrete Structures
//19Feb2014

//Including all applicable libraries
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iomanip>
using namespace std;

//Global/Constants

//Structure Declaration for playing board
struct Slot {
	int slotVal;// 0 = No Bomb -1 = Bomb
	string hide;//display hidden-invisible
	string cover;//Slot on board is covered
	string bomb;//Slot on board is a bomb
	string flagDisplay;//Slot on board is flagged
	bool reveal;//Slot on board is revealed
	bool flag;//Slot on board has flag
};

struct RowCol {
	int rowHold;
	int colHold;
};


//Function Prototypes
//Board Setup and display
void displayBoard(Slot **, int, int);
void createMineField(Slot **, int, int, int, int, int);//Create GameBoard/Fill with bombs/Values etc.
void coverBoard(Slot **, int, int);
void displayUpdate(Slot **, int, int);

//Board Cascading-Uncovering
void directionN(Slot **, int, int, int&);
void directionW(Slot **, int, int, int&);
void directionE(Slot **, int, int, int&);
void directionS(Slot **, int, int, int&);

void cascadeCheck(Slot **, int, int, int&);

void cascadeCheckSE(Slot **, int, int, int&);
void cascadeCheckSW(Slot **, int, int, int&);
void cascadeCheckNE(Slot **, int, int, int&);
void cascadeCheckNW(Slot **, int, int, int&);

//AI Solver Functions
//Clearing additional zeros (opening up board)
RowCol clearZerosR(Slot **, int, RowCol);

//Basic Bomb Flagging (slot with one in 3X3 that only has one uncovered block, which is surrounded by 1's)
void findBomb1(Slot **, int, RowCol, int, int);

void findBombCoveredEqual1(Slot**, int);//Finds bomb if slot value is 1 and there is 1 uncovered slot in the border

void findBombCoveredEqualMatch(Slot**, int);

void clearOnes(Slot **, int);//Clears surrounding covered values around a one with a bomb in the perimeter...

void clearTwos(Slot **, int);//Clears twos in same manner...

void flag2s(Slot **, int);

//Start Program Execution
int main()
{
	//Declaring Variables///////////////
	Slot **mineField; //2Dimensional array for playing board
	RowCol retRC;
	retRC.rowHold = 1;
	retRC.colHold = 1;

	RowCol RCback;
	RCback.colHold = 1;
	RCback.rowHold = 1;

	RowCol RCback1;
	RCback1.colHold = 1;
	RCback1.rowHold = 1;

	RowCol retRC1;
	retRC1.colHold = 1;
	retRC1.rowHold = 1;

	int NUM_ROWS=0, NUM_COLS=0;//Number of rows and columns on board grid
	int numBombs=0;//Number of Bombs(user specified)
	int rdBdSp1 = 0, rdBdSp2 = 0;//Random board space1, 2
	int rowCh=0; int colCh=0;
	bool reCascade = 0;
	int cascade = 0;//Cascade or not to cascade boolean
	char solver;
	bool firstTurn = 0;
	bool noZero = 0;
	
	//Initialize the random number seed
	//For choosing random slots on board, bomb placement, etc.
	srand(static_cast<unsigned int>(time(0)));
	
	//Opening Statement - Prompt for # of Bombs Desired
	cout << "Welcome to MineSweeper!" << endl;
	cout << endl;
	cout << "Please enter the number of Bombs You Wish to Find: ";
	cin >> numBombs;

	NUM_ROWS = numBombs;
	NUM_COLS = numBombs;

	//Check - Is number of Bombs Even or Odd?
	//If odd, add one to Rows and Cols
	if (numBombs % 2 != 0)
	{
		NUM_ROWS++;
		NUM_COLS++;
	}

	NUM_ROWS += 2;//Increasing board size secretly to prevent out of bounds errors
	NUM_COLS += 2;//when players are choosing slots on the border of the game board

	mineField = new Slot*[NUM_ROWS];//Dynamically allocating 2D array of pointers

	for (int i = 0; i < NUM_ROWS; i++)//Dynamically allocating 2D array of pointers
		mineField[i] = new Slot[NUM_COLS];

	for (int i = 0; i < NUM_ROWS; i++){//Initializing Array of Structures
		for (int j = 0; j < NUM_COLS; j++){
			mineField[i][j].slotVal = 0;
			mineField[i][j].hide = " ";
			mineField[i][j].cover = "[]";
			mineField[i][j].bomb = "*";
			mineField[i][j].reveal = 0;
			mineField[i][j].flag = 0;
			mineField[i][j].flagDisplay = "^";
		}//End Double For Loop
	}//End Initialization Double For Loop

	//Initialize outer border of array to make it invisible to user (out of bounds prevention)
	for (int i = 0; i < NUM_ROWS; i++){
		mineField[i][0].slotVal = 9;//Initializing left column to 9 for invisibility
		mineField[0][i].slotVal = 9;//Initializing top row to 9 for invisibilty
		mineField[NUM_ROWS - 1][i].slotVal = 9;//Bottom row - invisibility
		mineField[i][NUM_COLS - 1].slotVal = 9;//right column - invisibility
	}//End Invis Loop

	//Function calls///////////////////

	//Set Up MineField (Gameboard)
	createMineField(mineField, NUM_ROWS, NUM_COLS, numBombs, rdBdSp1,rdBdSp2);
	
	//Test Display of Board (Completely Revealed)
	displayBoard(mineField, NUM_ROWS, NUM_COLS);
	cout << "Test Display of Board Completely Revealed..." << endl;

	//Cover Board Here
	coverBoard(mineField,NUM_ROWS,NUM_COLS);

	//Prompt user for running AI solver
	cout << "Would you like to launch the AI Solver? (y/n) " << endl;
	cin >> solver;

	do{

		cout << "Enter the row number, followed by the column number: " << endl;
		cout << "(separate the numbers with a space): " << endl;

		if (solver == 'y' || solver == 'Y'){
//////////////////////////////////////////////////AI Function calls...////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			//Make first move (pick a random board slot)
			if (firstTurn <= 1)
			{
				rowCh = rand() % numBombs + 1;//[1, bomb/board dimension entered by user]
				colCh = rand() % numBombs + 1;//[1, bomb/board dimension entered by user]
				firstTurn++;
			}
			else{
				//Clear out excess zeros calls....
				RCback = clearZerosR(mineField, numBombs, retRC);//Clear all zero values on board

				rowCh = RCback.rowHold;
				colCh = RCback.colHold;
				if (rowCh == -2 || colCh == -2){
					RCback = clearZerosR(mineField, numBombs, retRC);//Clear all zero values on board - second run....

					rowCh = RCback.rowHold;
					colCh = RCback.colHold;
					if (rowCh == -2 || colCh == -2){
						RCback = clearZerosR(mineField, numBombs, retRC);//Clear all zero values on board - third run....

						rowCh = RCback.rowHold;
						colCh = RCback.colHold;
						if (rowCh == -2 || colCh == -2)
							continue;
					}// End If
				}//End If
			}//End Else clear out excess zero calls

			

			cout << "Row Choice: " << rowCh << endl;
			cout << "Col Choice: " << colCh << endl;

			

		}//End AI Solver if statement////////////////////////////////////////////////////////////////////////////////////////////////
		else{// User input for regular game of minesweeper...///////////////////////////////////////////////////////////////////////
			cin >> rowCh;
			cin >> colCh;
		}



		//Flipping display to reveal on original chosen slot
		mineField[rowCh][colCh].reveal++;


		//Reveal Board Based on user choice/Normal Gameplay
		//First check if initial user choice is a bomb
		if (mineField[rowCh][colCh].slotVal != -1 && mineField[rowCh][colCh].slotVal != 9){//While not a bomb, check in all directions from user choice

			//Cascade Check - main uncovering algorithm
			cascade = 0;
			cascadeCheck(mineField, rowCh, colCh, cascade);//North

			
		}// End If Statement

	} while (mineField[rowCh][colCh].slotVal != -1);

	//Start level 2 moves here after breaking from loop (i.e. flag bombs that are diagonal from 1...)
	//If the number in the center of a 3X3 is equal to 1, and there is only 1 covered slot on the border, flag it...
	/////////////First Flagging Section///////////////////////////////////////////
	findBombCoveredEqual1(mineField, numBombs);
	//updating display
	displayUpdate(mineField, NUM_ROWS, NUM_COLS);

	//Additional selections on board here....
	clearOnes(mineField, numBombs);
	//updating display
	displayUpdate(mineField, NUM_ROWS, NUM_COLS);

	clearTwos(mineField, numBombs);
	//updating display
	displayUpdate(mineField, NUM_ROWS, NUM_COLS);
	
		cout << "end of program reached.... ^'s are bombs which have been found(flagged) ..." << endl;

	//Free dynamic memory
	for (int i = 0; i < NUM_ROWS; i++){
		delete[] mineField[i];
		mineField[i] = 0;
	}
	delete[] mineField;
	mineField = 0;
	


	return 0;//End Program////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


void directionS(Slot **mineField, int rowCh, int colCh, int &cascade){
	//Check For Cascade
	//A Cascade only occurs when all adjacent squares to 
	//the one chosen do not contain mines and are not equal to 9 (invis outer boundary)
	if (mineField[rowCh - 1][colCh - 1].slotVal == -1 || mineField[rowCh - 1][colCh - 1].slotVal == 9)//NW
		cascade++;
	if (mineField[rowCh - 1][colCh].slotVal == -1 || mineField[rowCh - 1][colCh].slotVal == 9)//N
		cascade++;
	if (mineField[rowCh - 1][colCh + 1].slotVal == -1 || mineField[rowCh - 1][colCh + 1].slotVal == 9)//NE
		cascade++;
	if (mineField[rowCh][colCh + 1].slotVal == -1 || mineField[rowCh][colCh + 1].slotVal == 9)//E
		cascade++;
	if (mineField[rowCh + 1][colCh + 1].slotVal == -1 || mineField[rowCh + 1][colCh + 1].slotVal == 9)//SE
		cascade++;
	if (mineField[rowCh + 1][colCh].slotVal == -1 || mineField[rowCh + 1][colCh].slotVal == 9)//S
		cascade++;
	if (mineField[rowCh + 1][colCh - 1].slotVal == -1 || mineField[rowCh + 1][colCh - 1].slotVal == 9)//SW
		cascade++;
	if (mineField[rowCh][colCh - 1].slotVal == -1 || mineField[rowCh][colCh - 1].slotVal == 9)//W
		cascade++;


	if (cascade == 0){//If there were no bombs or 9's (boundary) - reveal all (in 3X3)//
		mineField[rowCh - 1][colCh - 1].reveal++;//NW
		mineField[rowCh - 1][colCh].reveal++;//N
		mineField[rowCh - 1][colCh + 1].reveal++;//NE
		mineField[rowCh][colCh + 1].reveal++;//E
		mineField[rowCh + 1][colCh + 1].reveal++;//SE
		mineField[rowCh + 1][colCh].reveal++;//S
		mineField[rowCh + 1][colCh - 1].reveal++;//SW
		mineField[rowCh][colCh - 1].reveal++;//W

		//then run cascade check function on all eight new squares
		//set cascade back to zero first...
		//increment user choices by one in each direction and call function again on each...
		cascade = 0;
		directionS(mineField, rowCh + 1, colCh, cascade);//S
	}
}

void directionE(Slot **mineField, int rowCh, int colCh, int &cascade){
	//Check For Cascade
	//A Cascade only occurs when all adjacent squares to 
	//the one chosen do not contain mines and are not equal to 9 (invis outer boundary)
	if (mineField[rowCh - 1][colCh - 1].slotVal == -1 || mineField[rowCh - 1][colCh - 1].slotVal == 9)//NW
		cascade++;
	if (mineField[rowCh - 1][colCh].slotVal == -1 || mineField[rowCh - 1][colCh].slotVal == 9)//N
		cascade++;
	if (mineField[rowCh - 1][colCh + 1].slotVal == -1 || mineField[rowCh - 1][colCh + 1].slotVal == 9)//NE
		cascade++;
	if (mineField[rowCh][colCh + 1].slotVal == -1 || mineField[rowCh][colCh + 1].slotVal == 9)//E
		cascade++;
	if (mineField[rowCh + 1][colCh + 1].slotVal == -1 || mineField[rowCh + 1][colCh + 1].slotVal == 9)//SE
		cascade++;
	if (mineField[rowCh + 1][colCh].slotVal == -1 || mineField[rowCh + 1][colCh].slotVal == 9)//S
		cascade++;
	if (mineField[rowCh + 1][colCh - 1].slotVal == -1 || mineField[rowCh + 1][colCh - 1].slotVal == 9)//SW
		cascade++;
	if (mineField[rowCh][colCh - 1].slotVal == -1 || mineField[rowCh][colCh - 1].slotVal == 9)//W
		cascade++;


	if (cascade == 0){//If there were no bombs or 9's (boundary) - reveal all (in 3X3)//
		mineField[rowCh - 1][colCh - 1].reveal++;//NW
		mineField[rowCh - 1][colCh].reveal++;//N
		mineField[rowCh - 1][colCh + 1].reveal++;//NE
		mineField[rowCh][colCh + 1].reveal++;//E
		mineField[rowCh + 1][colCh + 1].reveal++;//SE
		mineField[rowCh + 1][colCh].reveal++;//S
		mineField[rowCh + 1][colCh - 1].reveal++;//SW
		mineField[rowCh][colCh - 1].reveal++;//W

		//then run cascade check function on all eight new squares
		//set cascade back to zero first...
		//increment user choices by one in each direction and call function again on each...
		cascade = 0;
		directionE(mineField, rowCh, colCh + 1, cascade);//E
	}
}

void directionW(Slot **mineField, int rowCh, int colCh, int &cascade){
	//Check For Cascade
	//A Cascade only occurs when all adjacent squares to 
	//the one chosen do not contain mines and are not equal to 9 (invis outer boundary)
	if (mineField[rowCh - 1][colCh - 1].slotVal == -1 || mineField[rowCh - 1][colCh - 1].slotVal == 9)//NW
		cascade++;
	if (mineField[rowCh - 1][colCh].slotVal == -1 || mineField[rowCh - 1][colCh].slotVal == 9)//N
		cascade++;
	if (mineField[rowCh - 1][colCh + 1].slotVal == -1 || mineField[rowCh - 1][colCh + 1].slotVal == 9)//NE
		cascade++;
	if (mineField[rowCh][colCh + 1].slotVal == -1 || mineField[rowCh][colCh + 1].slotVal == 9)//E
		cascade++;
	if (mineField[rowCh + 1][colCh + 1].slotVal == -1 || mineField[rowCh + 1][colCh + 1].slotVal == 9)//SE
		cascade++;
	if (mineField[rowCh + 1][colCh].slotVal == -1 || mineField[rowCh + 1][colCh].slotVal == 9)//S
		cascade++;
	if (mineField[rowCh + 1][colCh - 1].slotVal == -1 || mineField[rowCh + 1][colCh - 1].slotVal == 9)//SW
		cascade++;
	if (mineField[rowCh][colCh - 1].slotVal == -1 || mineField[rowCh][colCh - 1].slotVal == 9)//W
		cascade++;


	if (cascade == 0){//If there were no bombs or 9's (boundary) - reveal all (in 3X3)//
		mineField[rowCh - 1][colCh - 1].reveal++;//NW
		mineField[rowCh - 1][colCh].reveal++;//N
		mineField[rowCh - 1][colCh + 1].reveal++;//NE
		mineField[rowCh][colCh + 1].reveal++;//E
		mineField[rowCh + 1][colCh + 1].reveal++;//SE
		mineField[rowCh + 1][colCh].reveal++;//S
		mineField[rowCh + 1][colCh - 1].reveal++;//SW
		mineField[rowCh][colCh - 1].reveal++;//W

		//then run cascade check function on all eight new squares
		//set cascade back to zero first...
		//increment user choices by one in each direction and call function again on each...
		cascade = 0;
		directionW(mineField, rowCh, colCh - 1, cascade);//W
	}
}

void directionN(Slot **mineField, int rowCh, int colCh, int &cascade){
	//Check For Cascade
	//A Cascade only occurs when all adjacent squares to 
	//the one chosen do not contain mines and are not equal to 9 (invis outer boundary)
	if (mineField[rowCh - 1][colCh - 1].slotVal == -1 || mineField[rowCh - 1][colCh - 1].slotVal == 9)//NW
		cascade++;
	if (mineField[rowCh - 1][colCh].slotVal == -1 || mineField[rowCh - 1][colCh].slotVal == 9)//N
		cascade++;
	if (mineField[rowCh - 1][colCh + 1].slotVal == -1 || mineField[rowCh - 1][colCh + 1].slotVal == 9)//NE
		cascade++;
	if (mineField[rowCh][colCh + 1].slotVal == -1 || mineField[rowCh][colCh + 1].slotVal == 9)//E
		cascade++;
	if (mineField[rowCh + 1][colCh + 1].slotVal == -1 || mineField[rowCh + 1][colCh + 1].slotVal == 9)//SE
		cascade++;
	if (mineField[rowCh + 1][colCh].slotVal == -1 || mineField[rowCh + 1][colCh].slotVal == 9)//S
		cascade++;
	if (mineField[rowCh + 1][colCh - 1].slotVal == -1 || mineField[rowCh + 1][colCh - 1].slotVal == 9)//SW
		cascade++;
	if (mineField[rowCh][colCh - 1].slotVal == -1 || mineField[rowCh][colCh - 1].slotVal == 9)//W
		cascade++;


	if (cascade == 0){//If there were no bombs or 9's (boundary) - reveal all (in 3X3)//
		mineField[rowCh - 1][colCh - 1].reveal++;//NW
		mineField[rowCh - 1][colCh].reveal++;//N
		mineField[rowCh - 1][colCh + 1].reveal++;//NE
		mineField[rowCh][colCh + 1].reveal++;//E
		mineField[rowCh + 1][colCh + 1].reveal++;//SE
		mineField[rowCh + 1][colCh].reveal++;//S
		mineField[rowCh + 1][colCh - 1].reveal++;//SW
		mineField[rowCh][colCh - 1].reveal++;//W

		//then run cascade check function on all eight new squares
		//set cascade back to zero first...
		//increment user choices by one in each direction and call function again on each...
		cascade = 0;
		directionN(mineField, rowCh - 1, colCh, cascade);//N
	}
}

//SE
void cascadeCheckSE(Slot**mineField, int rowCh, int colCh, int &cascade){
	//Check For Cascade
	//A Cascade only occurs when all adjacent squares to 
	//the one chosen do not contain mines and are not equal to 9 (invis outer boundary)
	if (mineField[rowCh - 1][colCh - 1].slotVal == -1 || mineField[rowCh - 1][colCh - 1].slotVal == 9)//NW
		cascade++;
	if (mineField[rowCh - 1][colCh].slotVal == -1 || mineField[rowCh - 1][colCh].slotVal == 9)//N
		cascade++;
	if (mineField[rowCh - 1][colCh + 1].slotVal == -1 || mineField[rowCh - 1][colCh + 1].slotVal == 9)//NE
		cascade++;
	if (mineField[rowCh][colCh + 1].slotVal == -1 || mineField[rowCh][colCh + 1].slotVal == 9)//E
		cascade++;
	if (mineField[rowCh + 1][colCh + 1].slotVal == -1 || mineField[rowCh + 1][colCh + 1].slotVal == 9)//SE
		cascade++;
	if (mineField[rowCh + 1][colCh].slotVal == -1 || mineField[rowCh + 1][colCh].slotVal == 9)//S
		cascade++;
	if (mineField[rowCh + 1][colCh - 1].slotVal == -1 || mineField[rowCh + 1][colCh - 1].slotVal == 9)//SW
		cascade++;
	if (mineField[rowCh][colCh - 1].slotVal == -1 || mineField[rowCh][colCh - 1].slotVal == 9)//W
		cascade++;


	if (cascade == 0){//If there were no bombs or 9's (boundary) - reveal all (in 3X3)//
		mineField[rowCh - 1][colCh - 1].reveal++;//NW
		mineField[rowCh - 1][colCh].reveal++;//N
		mineField[rowCh - 1][colCh + 1].reveal++;//NE
		mineField[rowCh][colCh + 1].reveal++;//E
		mineField[rowCh + 1][colCh + 1].reveal++;//SE
		mineField[rowCh + 1][colCh].reveal++;//S
		mineField[rowCh + 1][colCh - 1].reveal++;//SW
		mineField[rowCh][colCh - 1].reveal++;//W

		//then run cascade check function on all eight new squares
		//set cascade back to zero first...
		//increment user choices by one in each direction and call function again on each...
		cascade = 0;
		if (mineField[rowCh + 1][colCh + 1].reveal != 0){
			directionS(mineField, rowCh + 1, colCh + 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh + 1][colCh + 1].reveal != 0){
			directionE(mineField, rowCh + 1, colCh + 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh + 1][colCh + 1].reveal != 0){
			directionN(mineField, rowCh+1, colCh+1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh + 1][colCh + 1].reveal != 0){
			directionW(mineField, rowCh + 1, colCh + 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh + 1][colCh + 1].reveal != 0){
			cascadeCheckSE(mineField, rowCh + 1, colCh + 1, cascade);//SE
		}
	}

}
//SW
void cascadeCheckSW(Slot**mineField, int rowCh, int colCh, int &cascade){
	//Check For Cascade
	//A Cascade only occurs when all adjacent squares to 
	//the one chosen do not contain mines and are not equal to 9 (invis outer boundary)
	if (mineField[rowCh - 1][colCh - 1].slotVal == -1 || mineField[rowCh - 1][colCh - 1].slotVal == 9)//NW
		cascade++;
	if (mineField[rowCh - 1][colCh].slotVal == -1 || mineField[rowCh - 1][colCh].slotVal == 9)//N
		cascade++;
	if (mineField[rowCh - 1][colCh + 1].slotVal == -1 || mineField[rowCh - 1][colCh + 1].slotVal == 9)//NE
		cascade++;
	if (mineField[rowCh][colCh + 1].slotVal == -1 || mineField[rowCh][colCh + 1].slotVal == 9)//E
		cascade++;
	if (mineField[rowCh + 1][colCh + 1].slotVal == -1 || mineField[rowCh + 1][colCh + 1].slotVal == 9)//SE
		cascade++;
	if (mineField[rowCh + 1][colCh].slotVal == -1 || mineField[rowCh + 1][colCh].slotVal == 9)//S
		cascade++;
	if (mineField[rowCh + 1][colCh - 1].slotVal == -1 || mineField[rowCh + 1][colCh - 1].slotVal == 9)//SW
		cascade++;
	if (mineField[rowCh][colCh - 1].slotVal == -1 || mineField[rowCh][colCh - 1].slotVal == 9)//W
		cascade++;


	if (cascade == 0){//If there were no bombs or 9's (boundary) - reveal all (in 3X3)//
		mineField[rowCh - 1][colCh - 1].reveal++;//NW
		mineField[rowCh - 1][colCh].reveal++;//N
		mineField[rowCh - 1][colCh + 1].reveal++;//NE
		mineField[rowCh][colCh + 1].reveal++;//E
		mineField[rowCh + 1][colCh + 1].reveal++;//SE
		mineField[rowCh + 1][colCh].reveal++;//S
		mineField[rowCh + 1][colCh - 1].reveal++;//SW
		mineField[rowCh][colCh - 1].reveal++;//W

		//then run cascade check function on all eight new squares
		//set cascade back to zero first...
		//increment user choices by one in each direction and call function again on each...
		cascade = 0;
		if (mineField[rowCh + 1][colCh - 1].reveal != 0){
			directionS(mineField, rowCh + 1, colCh - 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh + 1][colCh - 1].reveal != 0){
			directionE(mineField, rowCh + 1, colCh - 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh + 1][colCh - 1].reveal != 0){
			directionN(mineField, rowCh + 1, colCh - 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh + 1][colCh - 1].reveal != 0){
			directionW(mineField, rowCh + 1, colCh - 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh + 1][colCh - 1].reveal != 0){
			cascadeCheckSW(mineField, rowCh + 1, colCh - 1, cascade);//SW
		}
	}

}
//NE
void cascadeCheckNE(Slot**mineField, int rowCh, int colCh, int &cascade){
	//Check For Cascade
	//A Cascade only occurs when all adjacent squares to 
	//the one chosen do not contain mines and are not equal to 9 (invis outer boundary)
	if (mineField[rowCh - 1][colCh - 1].slotVal == -1 || mineField[rowCh - 1][colCh - 1].slotVal == 9)//NW
		cascade++;
	if (mineField[rowCh - 1][colCh].slotVal == -1 || mineField[rowCh - 1][colCh].slotVal == 9)//N
		cascade++;
	if (mineField[rowCh - 1][colCh + 1].slotVal == -1 || mineField[rowCh - 1][colCh + 1].slotVal == 9)//NE
		cascade++;
	if (mineField[rowCh][colCh + 1].slotVal == -1 || mineField[rowCh][colCh + 1].slotVal == 9)//E
		cascade++;
	if (mineField[rowCh + 1][colCh + 1].slotVal == -1 || mineField[rowCh + 1][colCh + 1].slotVal == 9)//SE
		cascade++;
	if (mineField[rowCh + 1][colCh].slotVal == -1 || mineField[rowCh + 1][colCh].slotVal == 9)//S
		cascade++;
	if (mineField[rowCh + 1][colCh - 1].slotVal == -1 || mineField[rowCh + 1][colCh - 1].slotVal == 9)//SW
		cascade++;
	if (mineField[rowCh][colCh - 1].slotVal == -1 || mineField[rowCh][colCh - 1].slotVal == 9)//W
		cascade++;


	if (cascade == 0){//If there were no bombs or 9's (boundary) - reveal all (in 3X3)//
		mineField[rowCh - 1][colCh - 1].reveal++;//NW
		mineField[rowCh - 1][colCh].reveal++;//N
		mineField[rowCh - 1][colCh + 1].reveal++;//NE
		mineField[rowCh][colCh + 1].reveal++;//E
		mineField[rowCh + 1][colCh + 1].reveal++;//SE
		mineField[rowCh + 1][colCh].reveal++;//S
		mineField[rowCh + 1][colCh - 1].reveal++;//SW
		mineField[rowCh][colCh - 1].reveal++;//W

		//then run cascade check function on all eight new squares
		//set cascade back to zero first...
		//increment user choices by one in each direction and call function again on each...
		cascade = 0;
		if (mineField[rowCh - 1][colCh + 1].reveal != 0){
			directionS(mineField, rowCh - 1, colCh + 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh - 1][colCh + 1].reveal != 0){
			directionE(mineField, rowCh - 1, colCh + 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh - 1][colCh + 1].reveal != 0){
			directionN(mineField, rowCh - 1, colCh + 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh - 1][colCh + 1].reveal != 0){
			directionW(mineField, rowCh - 1, colCh + 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh - 1][colCh + 1].reveal != 0){
			cascadeCheckNE(mineField, rowCh - 1, colCh + 1, cascade);//NE
		}
	}

}
//NW
void cascadeCheckNW(Slot**mineField, int rowCh, int colCh, int &cascade){
	//Check For Cascade
	//A Cascade only occurs when all adjacent squares to 
	//the one chosen do not contain mines and are not equal to 9 (invis outer boundary)
	if (mineField[rowCh - 1][colCh - 1].slotVal == -1 || mineField[rowCh - 1][colCh - 1].slotVal == 9)//NW
		cascade++;
	if (mineField[rowCh - 1][colCh].slotVal == -1 || mineField[rowCh - 1][colCh].slotVal == 9)//N
		cascade++;
	if (mineField[rowCh - 1][colCh + 1].slotVal == -1 || mineField[rowCh - 1][colCh + 1].slotVal == 9)//NE
		cascade++;
	if (mineField[rowCh][colCh + 1].slotVal == -1 || mineField[rowCh][colCh + 1].slotVal == 9)//E
		cascade++;
	if (mineField[rowCh + 1][colCh + 1].slotVal == -1 || mineField[rowCh + 1][colCh + 1].slotVal == 9)//SE
		cascade++;
	if (mineField[rowCh + 1][colCh].slotVal == -1 || mineField[rowCh + 1][colCh].slotVal == 9)//S
		cascade++;
	if (mineField[rowCh + 1][colCh - 1].slotVal == -1 || mineField[rowCh + 1][colCh - 1].slotVal == 9)//SW
		cascade++;
	if (mineField[rowCh][colCh - 1].slotVal == -1 || mineField[rowCh][colCh - 1].slotVal == 9)//W
		cascade++;


	if (cascade == 0){//If there were no bombs or 9's (boundary) - reveal all (in 3X3)//
		mineField[rowCh - 1][colCh - 1].reveal++;//NW
		mineField[rowCh - 1][colCh].reveal++;//N
		mineField[rowCh - 1][colCh + 1].reveal++;//NE
		mineField[rowCh][colCh + 1].reveal++;//E
		mineField[rowCh + 1][colCh + 1].reveal++;//SE
		mineField[rowCh + 1][colCh].reveal++;//S
		mineField[rowCh + 1][colCh - 1].reveal++;//SW
		mineField[rowCh][colCh - 1].reveal++;//W

		//then run cascade check function on all eight new squares
		//set cascade back to zero first...
		//increment user choices by one in each direction and call function again on each...
		cascade = 0;
		if (mineField[rowCh - 1][colCh - 1].reveal != 0){
			directionS(mineField, rowCh - 1, colCh - 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh - 1][colCh - 1].reveal != 0){
			directionE(mineField, rowCh - 1, colCh - 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh - 1][colCh - 1].reveal != 0){
			directionN(mineField, rowCh - 1, colCh - 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh - 1][colCh - 1].reveal != 0){
			directionW(mineField, rowCh - 1, colCh - 1, cascade);
		}
		cascade = 0;
		if (mineField[rowCh - 1][colCh - 1].reveal != 0){
			cascadeCheckNW(mineField, rowCh - 1, colCh - 1, cascade);//NW
		}
	}

}

void cascadeCheck(Slot**mineField,int rowCh,int colCh, int &cascade){
	//Check For Cascade
	//A Cascade only occurs when all adjacent squares to 
	//the one chosen do not contain mines and are not equal to 9 (invis outer boundary)
	if (mineField[rowCh - 1][colCh - 1].slotVal == -1 || mineField[rowCh - 1][colCh - 1].slotVal == 9)//NW
		cascade++;
	if (mineField[rowCh - 1][colCh].slotVal == -1 || mineField[rowCh - 1][colCh].slotVal == 9)//N
		cascade++;
	if (mineField[rowCh - 1][colCh + 1].slotVal == -1 || mineField[rowCh - 1][colCh + 1].slotVal == 9)//NE
		cascade++;
	if (mineField[rowCh][colCh + 1].slotVal == -1 || mineField[rowCh][colCh + 1].slotVal == 9)//E
		cascade++;
	if (mineField[rowCh + 1][colCh + 1].slotVal == -1 || mineField[rowCh + 1][colCh + 1].slotVal == 9)//SE
		cascade++;
	if (mineField[rowCh + 1][colCh].slotVal == -1 || mineField[rowCh + 1][colCh].slotVal == 9)//S
		cascade++;
	if (mineField[rowCh + 1][colCh - 1].slotVal == -1 || mineField[rowCh + 1][colCh - 1].slotVal == 9)//SW
		cascade++;
	if (mineField[rowCh][colCh - 1].slotVal == -1 || mineField[rowCh][colCh - 1].slotVal == 9)//W
		cascade++;

	
	if (cascade == 0){//If there were no bombs or 9's (boundary) - reveal all (in 3X3)//
		mineField[rowCh - 1][colCh - 1].reveal++;//NW
		mineField[rowCh - 1][colCh].reveal++;//N
		mineField[rowCh - 1][colCh + 1].reveal++;//NE
		mineField[rowCh][colCh + 1].reveal++;//E
		mineField[rowCh + 1][colCh + 1].reveal++;//SE
		mineField[rowCh + 1][colCh].reveal++;//S
		mineField[rowCh + 1][colCh - 1].reveal++;//SW
		mineField[rowCh][colCh - 1].reveal++;//W


		//If the slot has not been revealed... check and reveal
		//then run cascade check function on four diagonal 3X3s
		//set cascade back to zero first...
		
		cascade = 0;
		if (mineField[rowCh - 1][colCh - 1].reveal != 0){
			cascadeCheckSE(mineField, rowCh - 1, colCh - 1, cascade);//NW
		}
		cascade = 0;
		if (mineField[rowCh - 1][colCh + 1].reveal != 0){
			cascadeCheckSW(mineField, rowCh - 1, colCh + 1, cascade);//NE
		}
		cascade = 0;
		if (mineField[rowCh + 1][colCh - 1].reveal != 0){
			cascadeCheckNE(mineField, rowCh + 1, colCh - 1, cascade);//SW
		}
		cascade = 0;
		if (mineField[rowCh + 1][colCh + 1].reveal != 0){
			cascadeCheckNW(mineField, rowCh + 1, colCh + 1, cascade);//SE
		}
	}
	
}

void displayUpdate(Slot **mineField, int NUM_ROWS, int NUM_COLS){
	//Reveal one slot in all directions and display
	cout << endl;
	cout << "    ";
	for (int i = 1; i < NUM_ROWS - 1; i++)
		cout << setw(2) << i;
	cout << endl;
	cout << endl;
	for (int i = 1; i < NUM_ROWS - 1; i++){//Display array
		if (i < 10)
			cout << " " << i;
		else
			cout << i;
		for (int j = 0; j < NUM_COLS; j++)
		{
			if (mineField[i][j].slotVal == -1 && mineField[i][j].flag != 1)//If bomb and not flagged, show cover
				cout << setw(2) << mineField[i][j].cover;
			else if (mineField[i][j].slotVal == -1 && mineField[i][j].flag == 1)//If bomb and flagged, show flag
				cout << setw(2) << mineField[i][j].flagDisplay;
			else if (mineField[i][j].slotVal < 9 && mineField[i][j].flag == 1)//If flagged and slot value is below 9, show flag
				cout << setw(2) << mineField[i][j].flagDisplay;
			else if (mineField[i][j].reveal == 1){
				if (mineField[i][j].slotVal >= 0 && mineField[i][j].slotVal < 9){//If reveal is 1, and slot value is below 9, show underlying slot value
					cout << setw(2) << mineField[i][j].slotVal;
				}
			}
			else if (mineField[i][j].slotVal >= 9)//Otherwise if underlying slot value is 9 or higher, make invisible(invisible border)
				cout << setw(2) << mineField[i][j].hide;
			else{
				cout << setw(2) << mineField[i][j].cover;//Otherwise show cover
			}
		}
		cout << endl;
	}
	cout << endl;
}

void coverBoard(Slot **mineField, int NUM_ROWS, int NUM_COLS){
	//Covered Board Display
	cout << endl;
	cout << "    ";
	for (int i = 1; i < NUM_ROWS - 1; i++)
		cout << setw(2) << i;
	cout << endl;
	cout << endl;
	for (int i = 1; i < NUM_ROWS - 1; i++){//Display array
		if (i < 10)
			cout << " " << i;
		else
			cout << i;
		for (int j = 0; j < NUM_COLS; j++)
		{
			if (mineField[i][j].slotVal == -1)
				cout << setw(2) << mineField[i][j].cover;
			if (mineField[i][j].slotVal >= 0 && mineField[i][j].slotVal < 9)
				cout << setw(2) << mineField[i][j].cover;
			if (mineField[i][j].slotVal >= 9)
				cout << setw(2) << mineField[i][j].hide;
		}
		cout << endl;
	}
	cout << endl;
	////////////End Covered Board Display
}

void displayBoard(Slot **mineField, int NUM_ROWS, int NUM_COLS){

	cout << endl;
	cout << "    ";
	for (int i = 1; i < NUM_ROWS-1; i++)
		cout << setw(2) << i;
	cout << endl;
	cout << endl;
	for (int i = 1; i < NUM_ROWS-1; i++){//Display array
		if (i < 10)
			cout << " " << i;
		else
			cout << i;
		for (int j = 0; j < NUM_COLS; j++)
		{
			if (mineField[i][j].slotVal == -1)
				cout << setw(2) << mineField[i][j].bomb;
			if (mineField[i][j].slotVal >= 0 && mineField[i][j].slotVal < 9)
				cout << setw(2) << mineField[i][j].slotVal;
			if (mineField[i][j].slotVal >= 9)
				cout << setw(2) << mineField[i][j].hide;
		}
		cout << endl;
	}
	cout << endl;
}

void createMineField(Slot **mineField, int NUM_ROWS, int NUM_COLS, int numBombs, int rdBdSp1, int rdBdSp2){

	

	//Setting Bombs in Array
	for (int k = 0; k <= numBombs; k++){
		do{
			rdBdSp1 = rand() % (NUM_ROWS - 2) + 1;//[1,Number of Rows/Columns]
			rdBdSp2 = rand() % (NUM_ROWS - 2) + 1;//[1,Number of Rows/Columns]

			if (mineField[rdBdSp1][rdBdSp2].slotVal != -1){
				mineField[rdBdSp1][rdBdSp2].slotVal--;//Decrementing slotvalue of random board space
			}
			else{ continue; } //If it hasn't already been decremented... start over loop

		} while (mineField[rdBdSp1][rdBdSp2].slotVal != -1);//If already decremented, end loop
	}//End Random Bomb Setting Loop

	//Setting Surrounding (Hint) Numbers around Bombs
	//Looping through entire 2D array with double for loops
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{//If -1(Bomb) is found, increment surrounding values on board +1
			//If those values are not already -1
			if (mineField[i][j].slotVal == -1){
				if (mineField[i - 1][j - 1].slotVal != -1)
					mineField[i - 1][j - 1].slotVal++;//NW
				if (mineField[i - 1][j].slotVal != -1)
					mineField[i - 1][j].slotVal++;//N
				if (mineField[i - 1][j + 1].slotVal != -1)
					mineField[i - 1][j + 1].slotVal++;//NE
				if (mineField[i][j + 1].slotVal != -1)
					mineField[i][j + 1].slotVal++;//E
				if (mineField[i + 1][j + 1].slotVal != -1)
					mineField[i + 1][j + 1].slotVal++;//SE
				if (mineField[i + 1][j].slotVal != -1)
					mineField[i + 1][j].slotVal++;//S
				if (mineField[i + 1][j - 1].slotVal != -1)
					mineField[i + 1][j - 1].slotVal++;//SW
				if (mineField[i][j - 1].slotVal != -1)
					mineField[i][j - 1].slotVal++;//W
			}

		}//End Double For Loop
	}//End Bomb Searching Double For Loop

}

RowCol clearZerosR(Slot **mineField, int numBombs, RowCol retRC){
	//First loop through entire revealed board (double for loop for 2d array)
	for (int i = 1; i < numBombs+1; i++){
		for (int j = 1; j < numBombs+1; j++){//Check if slot has been revealed
			if (mineField[i][j].reveal != 0 && mineField[i][j].slotVal == 0)//If slot has been revealed, check if value is 0
			{//If value is zero, check surrounding slots - if any are covered and not equal to 9 (border), return first covered slot as choice
				if (mineField[i - 1][j - 1].reveal == 0 && mineField[i - 1][j - 1].slotVal != 9 && mineField[i - 1][j - 1].slotVal == 0){//NW
					retRC.rowHold = i - 1;
					retRC.colHold = j - 1;
					return retRC;
				}
				else if (mineField[i - 1][j].reveal == 0 && mineField[i - 1][j].slotVal != 9 && mineField[i - 1][j].slotVal == 0){//N
					retRC.rowHold = i - 1;
				    retRC.colHold = j;
				    return retRC;
			    }
				else if (mineField[i - 1][j + 1].reveal == 0 && mineField[i - 1][j + 1].slotVal != 9 && mineField[i - 1][j + 1].slotVal == 0){//NE
					retRC.rowHold = i - 1;
				    retRC.colHold = j + 1;
				    return retRC;
			    }
				else if (mineField[i][j + 1].reveal == 0 && mineField[i][j + 1].slotVal != 9 && mineField[i][j + 1].slotVal == 0){//E
					retRC.rowHold = i;
			        retRC.colHold = j + 1;
			        return retRC;
		        }
				else if (mineField[i + 1][j + 1].reveal == 0 && mineField[i + 1][j + 1].slotVal != 9 && mineField[i + 1][j + 1].slotVal == 0){//SE
					retRC.rowHold = i + 1;
					retRC.colHold = j + 1;
					return retRC;
	            }
				else if (mineField[i + 1][j].reveal == 0 && mineField[i + 1][j].slotVal != 9 && mineField[i + 1][j].slotVal == 0){//S
					retRC.rowHold = i + 1;
					retRC.colHold = j;
					return retRC;
                }
				else if (mineField[i + 1][j - 1].reveal == 0 && mineField[i + 1][j - 1].slotVal != 9 && mineField[i + 1][j - 1].slotVal == 0){//SW
					retRC.rowHold = i + 1;
					retRC.colHold = j - 1;
					return retRC;
				}
				else if (mineField[i][j - 1].reveal == 0 && mineField[i][j - 1].slotVal != 9 && mineField[i][j - 1].slotVal == 0){//W
					retRC.rowHold = i;
					retRC.colHold = j - 1;
					return retRC;
				}
			}//End if statement
		}//End Double for
	}//End Double for
	//End search for zeros
	retRC.rowHold = -2;
	retRC.colHold = -2;
	return retRC;
}

void findBomb1(Slot **mineField, int numBombs, RowCol retRC1, int NUM_ROWS, int NUM_COLS){
	//First loop through entire revealed board (double for loop for 2d array)
	//Counter Variable flagCtr
	int flagCtr=0;//Adding accumulation of slot values to determine if bomb or not
	for (int i = 1; i < numBombs+1; i++){//Loop through entire board
		for (int j = 1; j < numBombs+1; j++){
			//Checking perimeter of each slot on board - If all values are one and they add to 8... flag as bomb
			//If slot value is visible (revealed) add the slot value to the accumulation (flagCtr)
			if (mineField[i - 1][j - 1].reveal != 0 && mineField[i - 1][j - 1].slotVal == 1){//NW
				flagCtr += mineField[i - 1][j - 1].slotVal;
			}
			if (mineField[i - 1][j].reveal != 0 && mineField[i - 1][j].slotVal == 1){//N
				flagCtr += mineField[i - 1][j].slotVal;
			}
			if (mineField[i - 1][j + 1].reveal != 0 && mineField[i - 1][j + 1].slotVal == 1){//NE
				flagCtr += mineField[i - 1][j + 1].slotVal;
			}
			if (mineField[i][j + 1].reveal != 0 && mineField[i][j + 1].slotVal == 1){//E
				flagCtr += mineField[i][j + 1].slotVal;
			}
			if (mineField[i + 1][j + 1].reveal != 0 && mineField[i + 1][j + 1].slotVal == 1){//SE
				flagCtr += mineField[i + 1][j + 1].slotVal;
			}
			if (mineField[i + 1][j].reveal != 0 && mineField[i + 1][j].slotVal != 0){//S
				flagCtr += mineField[i + 1][j].slotVal;
			}
			if (mineField[i + 1][j - 1].reveal != 0 && mineField[i + 1][j - 1].slotVal == 1){//SW
				flagCtr += mineField[i + 1][j - 1].slotVal;
			}
			if (mineField[i][j - 1].reveal != 0 && mineField[i][j - 1].slotVal == 1){//W
				flagCtr += mineField[i][j - 1].slotVal;
			}

			if (flagCtr == 8)
			mineField[i][j].flag++;
			flagCtr = 0;

		}//End Double for loop (searching entire board)
	}//End Double for End search for 1 value diagonal corners to flag

	
		
}//End Find Bomb1

void findBombCoveredEqual1(Slot** mineField, int numBombs){
	
	//Declaring local variable for counting covered slots
	int covered = 0;
	//Start by looping through entire array of visible slot values...
	for (int i = 1; i < numBombs + 1; i++){//Loop through entire board
		for (int j = 1; j < numBombs + 1; j++){
			//Get each uncovered slot and check in all directions
			if (mineField[i][j].reveal != 0 && mineField[i][j].slotVal == 1){
				//If revealed, check in all directions - count number of covered slots
				//-----Check for boundary == to 9 also here
				if (mineField[i - 1][j - 1].reveal == 0 || mineField[i - 1][j - 1].slotVal == 9){//NW
					covered ++;
				}
				if (mineField[i - 1][j].reveal == 0 || mineField[i - 1][j].slotVal == 9){//N
					covered ++;
				}
				if (mineField[i - 1][j + 1].reveal == 0 || mineField[i - 1][j + 1].slotVal == 9){//NE
					covered ++;
				}
				if (mineField[i][j + 1].reveal == 0 || mineField[i][j + 1].slotVal == 9){//E
					covered ++;
				}
				if (mineField[i + 1][j + 1].reveal == 0 || mineField[i + 1][j + 1].slotVal == 9){//SE
					covered ++;
				}
				if (mineField[i + 1][j].reveal == 0 || mineField[i + 1][j].slotVal == 9){//S
					covered ++;
				}
				if (mineField[i + 1][j - 1].reveal == 0 || mineField[i + 1][j - 1].slotVal == 9){//SW
					covered ++;
				}
				if (mineField[i][j - 1].reveal == 0 || mineField[i][j - 1].slotVal == 9){//W
					covered ++;
				}

			}//End if Revealed and equal to 1

			//Make sure that covered value is not zero...
			//cout << "covered value: " << covered << endl;
			if (covered == 1){
				//Flag covered slot as bomb (it must be a bomb...)
				if (mineField[i - 1][j - 1].reveal == 0){//NW
					mineField[i - 1][j - 1].flag++;
				}
				if (mineField[i - 1][j].reveal == 0){//N
					mineField[i - 1][j].flag++;
				}
				if (mineField[i - 1][j + 1].reveal == 0){//NE
					mineField[i - 1][j + 1].flag++;
				}
				if (mineField[i][j + 1].reveal == 0){//E
					mineField[i][j + 1].flag++;
				}
				if (mineField[i + 1][j + 1].reveal == 0){//SE
					mineField[i + 1][j + 1].flag++;
				}
				if (mineField[i + 1][j].reveal == 0){//S
					mineField[i + 1][j].flag++;
				}
				if (mineField[i + 1][j - 1].reveal == 0){//SW
					mineField[i + 1][j - 1].flag++;
				}
				if (mineField[i][j - 1].reveal == 0){//W
					mineField[i][j - 1].flag++;
				}
			}//End if covered border slots amount is equal to center bomb number

			//Reset covered value for next slot
			covered = 0;

		}//End Loop entire board
	}//End Loop entire board

}// End function findBombCoveredEqual

void findBombCoveredEqualMatch(Slot** mineField, int numBombs){
	//This function finds and flags bombs if the amount of covered squares in a 3X3 border is equal to the
	//number in the center of the 3X3...

	//Declaring local variable for counting covered slots
	int covered = 0;
	//Start by looping through entire array of visible slot values...
	for (int i = 1; i < numBombs + 1; i++){//Loop through entire board
		for (int j = 1; j < numBombs + 1; j++){
			//Get each uncovered slot and check in all directions
			if (mineField[i][j].reveal != 0){
				//If revealed, check in all directions - count number of covered slots
				//-----Check for boundary == to 9 also here - count as covered if slot value is equal to 9 (border)
				//If covered or equal to 9 - count
				if (mineField[i - 1][j - 1].flag == 0 && mineField[i - 1][j - 1].reveal == 0 || mineField[i - 1][j - 1].slotVal == 9){//NW
					covered++;
				}
				if (mineField[i - 1][j].flag == 0 && mineField[i - 1][j].reveal == 0 || mineField[i - 1][j].slotVal == 9){//N
					covered++;
				}
				if (mineField[i - 1][j + 1].flag == 0 && mineField[i - 1][j + 1].reveal == 0 || mineField[i - 1][j + 1].slotVal == 9){//NE
					covered++;
				}
				if (mineField[i][j + 1].flag == 0 && mineField[i][j + 1].reveal == 0 || mineField[i][j + 1].slotVal == 9){//E
					covered++;
				}
				if (mineField[i + 1][j + 1].flag == 0 && mineField[i + 1][j + 1].reveal == 0 || mineField[i + 1][j + 1].slotVal == 9){//SE
					covered++;
				}
				if (mineField[i + 1][j].flag == 0 && mineField[i + 1][j].reveal == 0 || mineField[i + 1][j].slotVal == 9){//S
					covered++;
				}
				if (mineField[i + 1][j - 1].flag == 0 && mineField[i + 1][j - 1].reveal == 0 || mineField[i + 1][j - 1].slotVal == 9){//SW
					covered++;
				}
				if (mineField[i][j - 1].flag == 0 && mineField[i][j - 1].reveal == 0 || mineField[i][j - 1].slotVal == 9){//W
					covered++;
				}

			}//End if Revealed and equal to 1 and not flagged...

			//If the number of covered border slots is equal to the center bomb #
			//Make sure that covered value is not zero...
			//cout << "covered value: " << covered << "slot value: " << mineField[i][j].slotVal << endl;
			if (mineField[i][j].slotVal != 0 && mineField[i][j].slotVal == covered){
				//Flag all covered slots as bombs (they must be bombs...)
				if (mineField[i - 1][j - 1].reveal == 0){//NW
					mineField[i - 1][j - 1].flag++;
				}
				if (mineField[i - 1][j].reveal == 0){//N
					mineField[i - 1][j].flag++;
				}
				if (mineField[i - 1][j + 1].reveal == 0){//NE
					mineField[i - 1][j + 1].flag++;
				}
				if (mineField[i][j + 1].reveal == 0){//E
					mineField[i][j + 1].flag++;
				}
				if (mineField[i + 1][j + 1].reveal == 0){//SE
					mineField[i + 1][j + 1].flag++;
				}
				if (mineField[i + 1][j].reveal == 0){//S
					mineField[i + 1][j].flag++;
				}
				if (mineField[i + 1][j - 1].reveal == 0){//SW
					mineField[i + 1][j - 1].flag++;
				}
				if (mineField[i][j - 1].reveal == 0){//W
					mineField[i][j - 1].flag++;
				}
			}//End if covered border slots amount is equal to center bomb number

			//Reset covered value for next slot
			covered = 0;

		}//End Loop entire board
	}//End Loop entire board
}

void clearOnes(Slot ** mineField, int numBombs){
	int numFlags = 0;
	//First loop through entire revealed board (double for loop for 2d array)
	for (int i = 1; i < numBombs + 1; i++){
		for (int j = 1; j < numBombs + 1; j++){//Check if slot has been revealed
			if (mineField[i][j].reveal != 0 && mineField[i][j].slotVal == 1)//If slot has been revealed, check if value is 1
			{//If value is one, check surrounding slots - if any are flagged as bombs count them
				if (mineField[i - 1][j - 1].flag != 0){//NW
					numFlags++;
				}
				if (mineField[i - 1][j].flag != 0){//N
					numFlags++;
				}
				if (mineField[i - 1][j + 1].flag != 0){//NE
					numFlags++;
				}
				if (mineField[i][j + 1].flag != 0){//E
					numFlags++;
				}
				if (mineField[i + 1][j + 1].flag != 0){//SE
					numFlags++;
				}
				if (mineField[i + 1][j].flag != 0){//S
					numFlags++;
				}
				if (mineField[i + 1][j - 1].flag != 0){//SW
					numFlags++;
				}
				if (mineField[i][j - 1].flag != 0){//W
					numFlags++;
				}
			}//End If Slot revealed and equal to 1

			//cout << "numFlags value: " << numFlags << endl;
				///////////////////////////Returning slots picked////////////////////////////////////////////////////////
			if (numFlags == 1){//If one bomb is found in perimeter... reveal all slots except for border slots and the bomb
				if (mineField[i - 1][j - 1].flag == 0 && mineField[i - 1][j - 1].slotVal != 9){//NW
					mineField[i - 1][j - 1].reveal++;//Choosing slot...
				}
				if (mineField[i - 1][j].flag == 0 && mineField[i - 1][j].slotVal != 9){//N
					mineField[i - 1][j].reveal++;
				}
				if (mineField[i - 1][j + 1].flag == 0 && mineField[i - 1][j + 1].slotVal != 9){//NE
					mineField[i - 1][j + 1].reveal++;
				}
				if (mineField[i][j + 1].flag == 0 && mineField[i][j + 1].slotVal != 9){//E
					mineField[i][j + 1].reveal++;
				}
				if (mineField[i + 1][j + 1].flag == 0 && mineField[i + 1][j + 1].slotVal != 9){//SE
					mineField[i + 1][j + 1].reveal++;
				}
				if (mineField[i + 1][j].flag == 0 && mineField[i + 1][j].slotVal != 9){//S
					mineField[i + 1][j].reveal++;
				}
				if (mineField[i + 1][j - 1].flag == 0 && mineField[i + 1][j - 1].slotVal != 9){//SW
					mineField[i + 1][j - 1].reveal++;
				}
				if (mineField[i][j - 1].flag == 0 && mineField[i][j - 1].slotVal != 9){//W
					mineField[i][j - 1].reveal++;
				}
			}//End if flags == 1
			numFlags = 0;//Resetting numFlags value for next board slot...
		}//End Double for
	}//End Double for
}//End function clear ones

void clearTwos(Slot ** mineField, int numBombs){
	int numFlags = 0;
	//First loop through entire revealed board (double for loop for 2d array)
	for (int i = 1; i < numBombs + 1; i++){
		for (int j = 1; j < numBombs + 1; j++){//Check if slot has been revealed
			if (mineField[i][j].reveal != 0 && mineField[i][j].slotVal == 2)//If slot has been revealed, check if value is 2
			{//If value is one, check surrounding slots - if any are flagged as bombs count them
				if (mineField[i - 1][j - 1].flag != 0){//NW
					numFlags++;
				}
				if (mineField[i - 1][j].flag != 0){//N
					numFlags++;
				}
				if (mineField[i - 1][j + 1].flag != 0){//NE
					numFlags++;
				}
				if (mineField[i][j + 1].flag != 0){//E
					numFlags++;
				}
				if (mineField[i + 1][j + 1].flag != 0){//SE
					numFlags++;
				}
				if (mineField[i + 1][j].flag != 0){//S
					numFlags++;
				}
				if (mineField[i + 1][j - 1].flag != 0){//SW
					numFlags++;
				}
				if (mineField[i][j - 1].flag != 0){//W
					numFlags++;
				}
			}//End If Slot revealed and equal to 2

			//cout << "numFlags value: " << numFlags << endl;
			///////////////////////////Returning slots picked////////////////////////////////////////////////////////
			if (numFlags == 2){//If one bomb is found in perimeter... reveal all slots except for border slots and the bomb
				if (mineField[i - 1][j - 1].flag == 0 && mineField[i - 1][j - 1].slotVal != 9){//NW
					mineField[i - 1][j - 1].reveal++;//Choosing slot...
				}
				if (mineField[i - 1][j].flag == 0 && mineField[i - 1][j].slotVal != 9){//N
					mineField[i - 1][j].reveal++;
				}
				if (mineField[i - 1][j + 1].flag == 0 && mineField[i - 1][j + 1].slotVal != 9){//NE
					mineField[i - 1][j + 1].reveal++;
				}
				if (mineField[i][j + 1].flag == 0 && mineField[i][j + 1].slotVal != 9){//E
					mineField[i][j + 1].reveal++;
				}
				if (mineField[i + 1][j + 1].flag == 0 && mineField[i + 1][j + 1].slotVal != 9){//SE
					mineField[i + 1][j + 1].reveal++;
				}
				if (mineField[i + 1][j].flag == 0 && mineField[i + 1][j].slotVal != 9){//S
					mineField[i + 1][j].reveal++;
				}
				if (mineField[i + 1][j - 1].flag == 0 && mineField[i + 1][j - 1].slotVal != 9){//SW
					mineField[i + 1][j - 1].reveal++;
				}
				if (mineField[i][j - 1].flag == 0 && mineField[i][j - 1].slotVal != 9){//W
					mineField[i][j - 1].reveal++;
				}
			}//End if flags == 1
			numFlags = 0;//Resetting numFlags value for next board slot...
		}//End Double for
	}//End Double for
}

void flag2s(Slot ** mineField, int numBombs){
	//Declaring local variable for counting covered slots
	int covered = 0;
	int numFlags = 0;
	//Start by looping through entire array of visible slot values...
	for (int i = 1; i < numBombs + 1; i++){//Loop through entire board
		for (int j = 1; j < numBombs + 1; j++){
			//Get each uncovered slot and check in all directions
			if (mineField[i][j].reveal != 0 && mineField[i][j].slotVal == 2){
				//If revealed, check in all directions - count number of covered slots
				//-----Check for boundary == to 9 also here
				if (mineField[i - 1][j - 1].reveal == 0 || mineField[i - 1][j - 1].slotVal == 9){//NW
					covered++;
				}
				if (mineField[i - 1][j].reveal == 0 || mineField[i - 1][j].slotVal == 9){//N
					covered++;
				}
				if (mineField[i - 1][j + 1].reveal == 0 || mineField[i - 1][j + 1].slotVal == 9){//NE
					covered++;
				}
				if (mineField[i][j + 1].reveal == 0 || mineField[i][j + 1].slotVal == 9){//E
					covered++;
				}
				if (mineField[i + 1][j + 1].reveal == 0 || mineField[i + 1][j + 1].slotVal == 9){//SE
					covered++;
				}
				if (mineField[i + 1][j].reveal == 0 || mineField[i + 1][j].slotVal == 9){//S
					covered++;
				}
				if (mineField[i + 1][j - 1].reveal == 0 || mineField[i + 1][j - 1].slotVal == 9){//SW
					covered++;
				}
				if (mineField[i][j - 1].reveal == 0 || mineField[i][j - 1].slotVal == 9){//W
					covered++;
				}

			}//End if Revealed and equal to 1
			//Flag counter
			if (mineField[i - 1][j - 1].flag != 0){//NW
				numFlags++;
			}
			if (mineField[i - 1][j].reveal == 0 || mineField[i - 1][j].slotVal == 9){//N
				covered++;
			}
			if (mineField[i - 1][j + 1].reveal == 0 || mineField[i - 1][j + 1].slotVal == 9){//NE
				covered++;
			}
			if (mineField[i][j + 1].reveal == 0 || mineField[i][j + 1].slotVal == 9){//E
				covered++;
			}
			if (mineField[i + 1][j + 1].reveal == 0 || mineField[i + 1][j + 1].slotVal == 9){//SE
				covered++;
			}
			if (mineField[i + 1][j].reveal == 0 || mineField[i + 1][j].slotVal == 9){//S
				covered++;
			}
			if (mineField[i + 1][j - 1].reveal == 0 || mineField[i + 1][j - 1].slotVal == 9){//SW
				covered++;
			}
			if (mineField[i][j - 1].reveal == 0 || mineField[i][j - 1].slotVal == 9){//W
				covered++;
			}

			//If there is one bomb flag and one covered square surrounding a value of 2... flag the uncovered square-
			//cout << "covered value: " << covered << endl;
			if (covered == 1 && numFlags == 1){
				//Flag covered slot as bomb (it must be a bomb...)
				if (mineField[i - 1][j - 1].reveal == 0){//NW
					mineField[i - 1][j - 1].flag++;
				}
				if (mineField[i - 1][j].reveal == 0){//N
					mineField[i - 1][j].flag++;
				}
				if (mineField[i - 1][j + 1].reveal == 0){//NE
					mineField[i - 1][j + 1].flag++;
				}
				if (mineField[i][j + 1].reveal == 0){//E
					mineField[i][j + 1].flag++;
				}
				if (mineField[i + 1][j + 1].reveal == 0){//SE
					mineField[i + 1][j + 1].flag++;
				}
				if (mineField[i + 1][j].reveal == 0){//S
					mineField[i + 1][j].flag++;
				}
				if (mineField[i + 1][j - 1].reveal == 0){//SW
					mineField[i + 1][j - 1].flag++;
				}
				if (mineField[i][j - 1].reveal == 0){//W
					mineField[i][j - 1].flag++;
				}
			}//End if covered border slots amount is equal to center bomb number

			//Reset covered value for next slot
			covered = 0;

		}//End Loop entire board
	}//End Loop entire board
}