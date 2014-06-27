/*
 *File: Project 02 17A
 *Author: Joel Youngberg
 *Date Created: 09 Oct 13
 *Title: Othello/Reversi
 *Purpose: Program that executes
 *a game of Othello/Reversi
 */

//Including all applicable libraries

#include <iostream>//I/O
#include <iomanip>//Formatting
#include <string>//For strings
#include <fstream>//Read & Write to file
#include "SlotBase.h"//Base class/object
#include "Slot.h"//Inherited polymorphic class/object
#include "PolymorphicSlot.h"//Inherited polymorphic class/object

using namespace std;

//Global variables and constants

//Do not use these unless applicable!! Good way to earn an F!
//Use dynamic allocation where possible



//All function prototypes
//Board display
void displayBoard(Slot<int> **, int, int);
//White move prototypes
int checkForBlackNW(Slot<int> **, int, int);
int flipBlackNW(Slot<int> **, int, int);
int checkForBlackN(Slot<int> **, int, int);
int flipBlackN(Slot<int> **, int, int);
int checkForBlackNE(Slot<int> **, int, int);
int flipBlackNE(Slot<int> **, int, int);
int checkForBlackE(Slot<int> **, int, int);
int flipBlackE(Slot<int> **, int, int);
int checkForBlackSE(Slot<int> **, int, int);
int flipBlackSE(Slot<int> **, int, int);
int checkForBlackS(Slot<int> **, int, int);
int flipBlackS(Slot<int> **, int, int);
int checkForBlackSW(Slot<int> **, int, int);
int flipBlackSW(Slot<int> **, int, int);
int checkForBlackW(Slot<int> **, int, int);
int flipBlackW(Slot<int> **, int, int);
//Black move prototypes
int checkForWhiteNW(Slot<int> **, int, int);
int flipWhiteNW(Slot<int> **, int, int);
int checkForWhiteN(Slot<int> **, int, int);
int flipWhiteN(Slot<int> **, int, int);
int checkForWhiteNE(Slot<int> **, int, int);
int flipWhiteNE(Slot<int> **, int, int);
int checkForWhiteE(Slot<int> **, int, int);
int flipWhiteE(Slot<int> **, int, int);
int checkForWhiteSE(Slot<int> **, int, int);
int flipWhiteSE(Slot<int> **, int, int);
int checkForWhiteS(Slot<int> **, int, int);
int flipWhiteS(Slot<int> **, int, int);
int checkForWhiteSW(Slot<int> **, int, int);
int flipWhiteSW(Slot<int> **, int, int);
int checkForWhiteW(Slot<int> **, int, int);
int flipWhiteW(Slot<int> **, int, int);

//Starting executable code @ function main:
int main()
{
  //Declaring Variables

    Slot<int> **brdAry; //2Dimensional Array for board
    int NUM_ROWS, NUM_COLS;
    int grid1, grid2;//To hold user board choices
    int flipNW =0, flipN =0, flipNE =0, flipE =0;
    int flipSE =0, flipS =0, flipSW =0, flipW =0;
    static int passTrn =0;//Storing amount of times user passes turn (twice in a row ends game)
    int tlWhite =0, tlBlack =0;//Storing end game score tallys
    int white =0, black =0, tie =0;

    //File I/O variables
    int blkTemp =0, wtTemp =0;
    int blkHigh =0, wtHigh =0;
    int wtNTemp =0, blkNTemp =0, tNTemp =0;
    int totWwt =0, totWblk =0, totTies =0;
    int sub =0;


    cout << "Welcome to Othello/Reversi!" << endl;
    cout << endl;
    do{//Validation of size loop
    cout << "Please enter the size of the game board" << endl;
    cout << "which you would like to play on." << endl;
    cout << "The official/recommended size is 8." << endl;
    cout << endl;
    cout << "Please enter a single integer to represent the length & width" << endl;
    cout << "of the board. (i.e. typing an 8 will result in an 8X8 board)." << endl;
    cout << "This edition supports board sizes up to 36X36." << endl;
    cout << endl;
    cout << "Please enter an even number between 8-36 for your board size:" << endl;
    cin >> NUM_ROWS;
    NUM_ROWS +=2;//Increasing board size secretly to prevent out of bounds errors
                 //when players are choosing slots on the border of the game board

    NUM_COLS = NUM_ROWS;//Board must always be square
    }while(NUM_ROWS < 8 || NUM_ROWS %2 != 0 || NUM_ROWS > 38);//Validation of size loop end

    brdAry = new Slot<int>*[NUM_ROWS];//Dynamically allocating 2D array of pointers

        for (int i = 0; i < NUM_ROWS; i++)//Dynamically allocating 2D array of pointers
        brdAry[i] = new Slot<int>[NUM_COLS];

    //This was no longer needed because the constructor does this initialization
        //upon creation of each object...
    //initialization of structure array to empty/zero slot value - plugging in graphic strings
    //for(int i = 0; i < NUM_ROWS; i++){//Fill array with zeros (set to empty)
        //for (int j = 0; j < NUM_COLS; j++){
            //brdAry[i][j].slotVal = 0;
           // brdAry[i][j].empty = "[]";
            //brdAry[i][j].white = " *";
            //brdAry[i][j].black = " O";
            //brdAry[i][j].invis = "  ";
        //}
    //}

    //Initialize four center values depending on size chosen by user(game setup)
    int initNum1 = NUM_ROWS/2 -1;
    int initNum2 = initNum1;

    brdAry[initNum1][initNum2].setSlotVal(1);//Top Left initialization
    brdAry[initNum1+1][initNum2].setSlotVal(2);
    brdAry[initNum1][initNum2+1].setSlotVal(2);
    brdAry[initNum1+1][initNum2+1].setSlotVal(1);

    //Initialize outer border of array to make it invisible to user (out of bounds prevention)
    for (int i =0; i < NUM_ROWS; i++){
        brdAry[i][0].setSlotVal(3);//Initializing left column to 3 for invisibility
        brdAry[0][i].setSlotVal(3);//Initializing top row to 3 for invisibilty
        brdAry[NUM_ROWS-1][i].setSlotVal(3);//Bottom row - invisibility
        brdAry[i][NUM_COLS-1].setSlotVal(3);//right column - invisibility
    }


    do{//Repeat both turns (black and white)
    ///////////////////////////////////////////////////////////////////////////////////////////////
    do{//Move loop for black's turn!!//////////////////// black black black black black ///////////
    ///////////////////////////////////////////////////////
       displayBoard(brdAry,NUM_ROWS,NUM_COLS);
    cout << endl;
    cout << "(0)Black's Turn: Please select a position to place your piece: " << endl;
    cout << "Enter the row number first, followed by the column number." << endl;
    cout << "Separate the numbers with a space:(i.e. x x) " << endl;
    cout << "If there are no legal moves, enter -1 -1 to pass the turn." << endl;

    cin >> grid1;
    cin >> grid2;

    if(grid1 == -1){
        passTrn++;
        cout << "Passing Turn..." << endl;
        break;
    }
    //Validating Move - Did the user choose a slot within the scope of the board?
    if (grid1 < 1 || grid1 > NUM_ROWS || grid2 < 1 || grid2 > NUM_ROWS){
        cout << endl;
        cout << "At least one of your position coordinates was off the board..." << endl;
        cout << "Please enter a valid position or enter -1 -1 to pass the turn." << endl;
        continue;
    }
    //Validating Move - Did the user choose an empty slot?
    if (brdAry[grid1][grid2].getSlotVal() == 1 || brdAry[grid1][grid2].getSlotVal() == 2){
            cout << endl;
            cout << "That board position has already been taken..." << endl;
            cout << "Please enter a different position or enter -1 -1 to pass the turn." << endl;
            continue;
        }

    //Checking northwest direction for valid move (black)
    flipNW = checkForWhiteNW(brdAry, grid1, grid2);
    if(flipNW == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to black (move is valid)
        brdAry[grid1][grid2].setSlotVal(2);
        //Flipping all whites to black in NW direction
        flipWhiteNW(brdAry, grid1, grid2);
    }

    //Checking north direction for valid move (black)
    flipN = checkForWhiteN(brdAry, grid1, grid2);
    if(flipN == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to black (move is valid)
        brdAry[grid1][grid2].setSlotVal(2);
        //Flipping all whites to black in N direction
        flipWhiteN(brdAry, grid1, grid2);
    }

    //Checking northeast direction for valid move (black)
    flipNE = checkForWhiteNE(brdAry, grid1, grid2);
    if(flipNE == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to black (move is valid)
        brdAry[grid1][grid2].setSlotVal(2);
        //Flipping all whites to black in N direction
        flipWhiteNE(brdAry, grid1, grid2);
    }

    //Checking east direction for valid move (black)
    flipE = checkForWhiteE(brdAry, grid1, grid2);
    if(flipE == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to black (move is valid)
        brdAry[grid1][grid2].setSlotVal(2);
        //Flipping all whites to black in N direction
        flipWhiteE(brdAry, grid1, grid2);
    }

    //Checking southeast direction for valid move (white)
    flipSE = checkForWhiteSE(brdAry, grid1, grid2);
    if(flipSE == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to black (move is valid)
        brdAry[grid1][grid2].setSlotVal(2);
        //Flipping all whites to black in N direction
        flipWhiteSE(brdAry, grid1, grid2);
    }

    //Checking south direction for valid move (black)
    flipS = checkForWhiteS(brdAry, grid1, grid2);
    if(flipS == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to black (move is valid)
        brdAry[grid1][grid2].setSlotVal(2);
        //Flipping all whites to black in N direction
        flipWhiteS(brdAry, grid1, grid2);
    }

    //Checking southwest direction for valid move (black)
    flipSW = checkForWhiteSW(brdAry, grid1, grid2);
    if(flipSW == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to black (move is valid)
        brdAry[grid1][grid2].setSlotVal(2);
        //Flipping all whites to black in N direction
        flipWhiteSW(brdAry, grid1, grid2);
    }

    //Checking west direction for valid move (black)
    flipW = checkForWhiteW(brdAry, grid1, grid2);
    if(flipW == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to black (move is valid)
        brdAry[grid1][grid2].setSlotVal(2);
        //Flipping all whites to black in N direction
        flipWhiteW(brdAry, grid1, grid2);
    }

    //Validating Move - Did at least one flip occur?
    if(flipNW + flipN + flipNE + flipE +
       flipSE + flipS + flipSW + flipW == 0){
        cout << "Position " << grid1 << " " << grid2 << " is not a valid move." << endl;
        cout << "You must select a position that causes at least one flip to occur." << endl;
        cout << "If you cannot find a valid position, enter -1 twice" << endl;
        cout << "separated by a space (i.e. -1 -1) to pass the turn: " << endl;


    }
    }while(flipNW + flipN + flipNE + flipE +
           flipSE + flipS + flipSW + flipW == 0);




    ////////////////////////////////////////////////////////////////////////////////////////////////
    do{//Move loop for white's turn!!////white white white white white white white white///////////
    //////////////////////////////////////////////////////////////////////////////////////////////
    displayBoard(brdAry,NUM_ROWS,NUM_COLS);//display board
    cout << endl;
    cout << "(*)White's Turn: Please select a position to place your piece: " << endl;
    cout << "Enter the row number first, followed by the column number." << endl;
    cout << "Separate the numbers with a space:(i.e. x x) " << endl;
    cout << "If there are no legal moves, enter -1 -1 to pass the turn." << endl;

    cin >> grid1;
    cin >> grid2;

    if(grid1 == -1){
        passTrn++;
        cout << "Passing Turn..." << endl;
        break;
    }
    //Validating Move - Did the user choose an empty slot?
    if(brdAry[grid1][grid2].getSlotVal() == 1 || brdAry[grid1][grid2].getSlotVal() == 2){
            cout << "That board position has already been taken..." << endl;
            cout << "Please enter a different position or enter -1 to pass the turn." << endl;
            continue;
        }

    //Checking northwest direction for valid move (white)
    flipNW = checkForBlackNW(brdAry, grid1, grid2);
    if(flipNW == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to white (move is valid)
        brdAry[grid1][grid2].setSlotVal(1);
        //Flipping all blacks to white in NW direction
        flipBlackNW(brdAry, grid1, grid2);
    }

    //Checking north direction for valid move (white)
    flipN = checkForBlackN(brdAry, grid1, grid2);
    if(flipN == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to white (move is valid)
        brdAry[grid1][grid2].setSlotVal(1);
        //Flipping all blacks to white in N direction
        flipBlackN(brdAry, grid1, grid2);
    }

    //Checking northeast direction for valid move (white)
    flipNE = checkForBlackNE(brdAry, grid1, grid2);
    if(flipNE == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to white (move is valid)
        brdAry[grid1][grid2].setSlotVal(1);
        //Flipping all blacks to white in N direction
        flipBlackNE(brdAry, grid1, grid2);
    }

    //Checking east direction for valid move (white)
    flipE = checkForBlackE(brdAry, grid1, grid2);
    if(flipE == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to white (move is valid)
        brdAry[grid1][grid2].setSlotVal(1);
        //Flipping all blacks to white in N direction
        flipBlackE(brdAry, grid1, grid2);
    }

    //Checking southeast direction for valid move (white)
    flipSE = checkForBlackSE(brdAry, grid1, grid2);
    if(flipSE == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to white (move is valid)
        brdAry[grid1][grid2].setSlotVal(1);
        //Flipping all blacks to white in N direction
        flipBlackSE(brdAry, grid1, grid2);
    }

    //Checking south direction for valid move (white)
    flipS = checkForBlackS(brdAry, grid1, grid2);
    if(flipS == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to white (move is valid)
        brdAry[grid1][grid2].setSlotVal(1);
        //Flipping all blacks to white in N direction
        flipBlackS(brdAry, grid1, grid2);
    }

    //Checking southwest direction for valid move (white)
    flipSW = checkForBlackSW(brdAry, grid1, grid2);
    if(flipSW == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to white (move is valid)
        brdAry[grid1][grid2].setSlotVal(1);
        //Flipping all blacks to white in N direction
        flipBlackSW(brdAry, grid1, grid2);
    }

    //Checking west direction for valid move (white)
    flipW = checkForBlackW(brdAry, grid1, grid2);
    if(flipW == 1){//Checking if move was valid for northwest direction
        //Set chosen piece to white (move is valid)
        brdAry[grid1][grid2].setSlotVal(1);
        //Flipping all blacks to white in N direction
        flipBlackW(brdAry, grid1, grid2);
    }

    //Validating Move - Did at least one flip occur?
    if(flipNW + flipN + flipNE + flipE +
       flipSE + flipS + flipSW + flipW ==0){
        cout << "Position " << grid1 << " " << grid2 << " is not a valid move." << endl;
        cout << "You must select a position that causes at least one flip to occur." << endl;
        cout << "If you cannot find a valid position, enter -1 twice" << endl;
        cout << "separated by a space (i.e. -1 -1) to pass the turn: " << endl;


    }
    }while(flipNW + flipN + flipNE + flipE +
           flipSE + flipS + flipSW + flipW == 0);//End Loop for white's turn

    if(passTrn == 1)//Resetting static passTrn variable so that two passes at
        passTrn = 0;//Different times from different players don't add to two and trigger

    }while(passTrn != 2);//End looping black and white's turns if passTrn gets to two

    //Calculate end of game statistics (color with most wins)
    for (int i =0; i < NUM_ROWS; i++)
    {
        for(int j =0; j < NUM_COLS; j++)
        {
            if(brdAry[i][j].getSlotVal() == 1)
                tlWhite++;
            if(brdAry[i][j].getSlotVal() == 2)
                tlBlack++;
        }
    }

    //Creating objects for polymorphism demonstration - bonus points
    PolySlot<int> poly;
    Slot<int> slot;
    poly.setPrsAmt(100);
    slot.setPrsAmt(50);


    if (tlWhite > tlBlack){
        cout << endl;
        cout << "White wins the game!!!!" << endl;
        //Demonstration of polymorphism bonus points
        if(tlWhite >= tlBlack + 10){
        slot.praiseWinner();
        cout << "White score before bonus: " << tlWhite <<endl;
        tlWhite += 50;
        }
        if(tlWhite >= tlBlack + 70){//Accounting for bonus 50 already received
        poly.praiseWinner();
        tlWhite += 100;
        }
        cout << "White total score: " << tlWhite << " pieces" << endl;
        cout << "Black total score: " << tlBlack << " pieces" << endl;
        white++;
        sub = 1;
        }
    else if (tlBlack > tlWhite){
        cout << endl;
        cout << "Black wins the game!!!!" << endl;
        //Demonstration of polymorphism bonus points
        if(tlBlack >= tlWhite + 10){
        slot.praiseWinner();
        cout << "Black score before bonus: " << tlBlack << endl;
        tlBlack += 50;
        }
        if(tlBlack >= tlWhite + 70){//Accounting for bonus 50 already received
        poly.praiseWinner();
        tlBlack += 100;
        }
        cout << "Black total score: " << tlBlack << " pieces" << endl;
        cout << "White total score: " << tlWhite << " pieces" << endl;
        black++;
        sub =2;
    }
    else if (tlBlack == tlWhite){
        cout << endl;
        cout << "It's a tie game!!!!" << endl;
        cout << "Black total score: " << tlBlack << " pieces" << endl;
        cout << "White total score: " << tlWhite << " pieces" << endl;
        tie++;
        sub = 3;
        }

    fstream file;// Read/Write object
    file.open("G:\\RCC\\C++\\winloss.txt", ios::app);//opening/creating file
    if (!file)
        cout << "Error opening/creating/writing to file... check filepath line 416..." << endl;

    //Writing the win/loss statistics to the file
    file << tlBlack << endl;
    file << tlWhite << endl;
    file << white << endl;
    file << black << endl;
    file << tie << endl;

    //Close file
    file.close();

    file.open("G:\\RCC\\C++\\winloss.txt", ios::in);//opening/file to read
    if (!file)
        cout << "Error opening/creating/writing to file... check filepath line 430..." << endl;
    while(file){
        file >> blkTemp;
        if(blkTemp > blkHigh)
            blkHigh = blkTemp;//Reassign high score for black if higher

        file >> wtTemp;
        if(wtTemp > wtHigh)
            wtHigh = wtTemp;//Reassign high score for white if higher

        file >> wtNTemp;
        totWwt += wtNTemp;//Running total wins for white

        file >> blkNTemp;
        totWblk += blkNTemp;//Running total wins for black

        file >> tNTemp;
        totTies += tNTemp;//Running total ties
    }

    //Close file
    file.close();

    if(sub ==1){
    cout << endl;
    cout << "Black high score: " << blkHigh << endl;
    cout << "White high score: " << wtHigh << endl;
    cout << "Total wins white: " << totWwt-1 << endl;
    cout << "Total wins black: " << totWblk << endl;
    cout << "Total ties: " << totTies << endl;
    }
    else if(sub == 2){
        cout << endl;
        cout << "Black high score: " << blkHigh << endl;
        cout << "White high score: " << wtHigh << endl;
        cout << "Total wins white: " << totWwt << endl;
        cout << "Total wins black: " << totWblk-1 << endl;
        cout << "Total ties: " << totTies << endl;
    }
    else if(sub == 3){
        cout << endl;
        cout << "Black high score: " << blkHigh << endl;
        cout << "White high score: " << wtHigh << endl;
        cout << "Total wins white: " << totWwt << endl;
        cout << "Total wins black: " << totWblk << endl;
        cout << "Total ties: " << totTies-1 << endl;
    }


    //Free dynamic memory - No memory leaks here!!
                for (int i = 0; i < NUM_ROWS; i++){
                delete [] brdAry[i];
                brdAry[i] =0;
                }
                delete [] brdAry;
                brdAry = 0;

  /////////////////////////////////////////////////////////////////////////////////////////////
  //Exit Program///////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////
    return 0;
}
void displayBoard(Slot<int> **brdAry, int NUM_ROWS, int NUM_COLS){

    cout << endl;
    cout << "    ";
    for(int i = 1; i < NUM_ROWS-1; i++)
        cout << setw(2) << i;
        cout << endl;
        cout << endl;
    for(int i = 1; i < NUM_ROWS-1; i++){//Display array
        if(i < 10)
            cout << " " << i;
        else
            cout << i;
        for (int j = 0; j < NUM_COLS; j++)
        {
            if (brdAry[i][j].getSlotVal() == 0)
                cout << setw(2) << brdAry[i][j].getEmpty();
            if (brdAry[i][j].getSlotVal() == 1)
                cout << setw(2) << brdAry[i][j].getWhite();
            if (brdAry[i][j].getSlotVal() == 2)
                cout << setw(2) << brdAry[i][j].getBlack();
            if (brdAry[i][j].getSlotVal() == 3)
                cout << setw(2) << brdAry[i][j].getInvis();
        }
      cout << endl;
     }
    }
////////////////////////////////////////////////////////////////////////////////////////////////
//Eight Directional Check & Flip Definitions White Move Checking for black//////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
int checkForBlackNW(Slot<int> **brdAry, int grid1, int grid2){
     int check =0;
    do{
        grid1--;//Checking northwest one spot
        grid2--;
        check++;
    }while(brdAry[grid1][grid2].getSlotVal() == 2);

    if (brdAry[grid1][grid2].getSlotVal() == 1 && check > 1)
        return 1;
    else return 0;
}//End function checkForBlackNW
int flipBlackNW(Slot<int> **brdAry, int grid1, int grid2){

        grid1--;//Move northwest one spot
        grid2--;

    while(brdAry[grid1][grid2].getSlotVal() == 2){//looping until something other than 2 is found
        brdAry[grid1][grid2].setSlotVal(1);//Changing black piece to white
        grid1--;//Move northwest one spot
        grid2--;
    };

    if (brdAry[grid1][grid2].getSlotVal() == 1)
        return 1;
    else return 0;
}// End Function Flip Black NW
//////////////////////////////////////////////////////////////////////////////////////////////
int checkForBlackN(Slot<int> **brdAry, int grid1, int grid2){
     int check =0;
    do{
        grid1--;//Checking north one spot
        check++;
    }while(brdAry[grid1][grid2].getSlotVal() == 2);

    if (brdAry[grid1][grid2].getSlotVal() == 1 && check > 1)
        return 1;
    else return 0;
}//End function checkForBlackN

int flipBlackN(Slot<int> **brdAry, int grid1, int grid2){

        grid1--;//Move north one spot

    while(brdAry[grid1][grid2].getSlotVal() == 2){//looping until something other than 2 is found
        brdAry[grid1][grid2].setSlotVal(1);//Changing black piece to white
        grid1--;//Move north one spot

    };

    if (brdAry[grid1][grid2].getSlotVal() == 1)
        return 1;
    else return 0;
}//End Function Flip BlackN
//////////////////////////////////////////////////////////////////////////////////////////////
int checkForBlackNE(Slot<int> **brdAry, int grid1, int grid2){
     int check =0;
    do{
        grid1--;//Checking northeast one spot
        grid2++;
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 2);

    if (brdAry[grid1][grid2].getSlotVal() == 1 && check > 1)
        return 1;
    else return 0;
}//End function checkForBlackNE

int flipBlackNE(Slot<int> **brdAry, int grid1, int grid2){

        grid1--;//Move northeast one spot
        grid2++;

    while(brdAry[grid1][grid2].getSlotVal() == 2){//looping until something other than 2 is found
        brdAry[grid1][grid2].setSlotVal(1);//Changing black piece to white
        grid1--;//Move northeast one spot
        grid2++;
        };

    if (brdAry[grid1][grid2].getSlotVal() == 1)
        return 1;
    else return 0;
}//End Function Flip BlackNE
/////////////////////////////////////////////////////////////////////////////////////////////
int checkForBlackE(Slot<int> **brdAry, int grid1, int grid2){
     int check =0;
    do{
        //Checking east one spot
        grid2++;
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 2);

    if (brdAry[grid1][grid2].getSlotVal() == 1 && check > 1)
        return 1;
    else return 0;
}//End function checkForBlackE

int flipBlackE(Slot<int> **brdAry, int grid1, int grid2){

        //Move east one spot
        grid2++;

    while(brdAry[grid1][grid2].getSlotVal() == 2){//looping until something other than 2 is found
        brdAry[grid1][grid2].setSlotVal(1);//Changing black piece to white
        //Move east one spot
        grid2++;
        };

    if (brdAry[grid1][grid2].getSlotVal() == 1)
        return 1;
    else return 0;
}//End Function Flip BlackE
/////////////////////////////////////////////////////////////////////////////////////////////
int checkForBlackSE(Slot<int> **brdAry, int grid1, int grid2){
      int check =0;
    do{
        //Checking southeast one spot
        grid1++;
        grid2++;
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 2);

    if (brdAry[grid1][grid2].getSlotVal() == 1 && check > 1)
        return 1;
    else return 0;
}//End function checkForBlackSE

int flipBlackSE(Slot<int> **brdAry, int grid1, int grid2){

        //Move southeast one spot
        grid1++;
        grid2++;

    while(brdAry[grid1][grid2].getSlotVal() == 2){//looping until something other than 2 is found
        brdAry[grid1][grid2].setSlotVal(1);//Changing black piece to white
        //Move southeast one spot
        grid1++;
        grid2++;

    };

    if (brdAry[grid1][grid2].getSlotVal() == 1)
        return 1;
    else return 0;
}//End Function Flip BlackSE
/////////////////////////////////////////////////////////////////////////////////////////////
int checkForBlackS(Slot<int> **brdAry, int grid1, int grid2){
    int check =0;
    do{
        //Checking south one spot
        grid1++;
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 2);

    if (brdAry[grid1][grid2].getSlotVal() == 1 && check > 1)
        return 1;
    else return 0;
}//End function checkForBlackS

int flipBlackS(Slot<int> **brdAry, int grid1, int grid2){

        //Move south one spot
        grid1++;


    while(brdAry[grid1][grid2].getSlotVal() == 2){//looping until something other than 2 is found
        brdAry[grid1][grid2].setSlotVal(1);//Changing black piece to white
        //Move south one spot
        grid1++;


    };

    if (brdAry[grid1][grid2].getSlotVal() == 1)
        return 1;
    else return 0;
}//End Function Flip BlackS
/////////////////////////////////////////////////////////////////////////////////////////////
int checkForBlackSW(Slot<int> **brdAry, int grid1, int grid2){
     int check =0;
    do{
        //Checking southwest one spot
        grid1++;
        grid2--;
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 2);

    if (brdAry[grid1][grid2].getSlotVal() == 1 && check > 1)
        return 1;
    else return 0;
}//End function checkForBlackSW

int flipBlackSW(Slot<int> **brdAry, int grid1, int grid2){

        //Move southwest one spot
        grid1++;
        grid2--;

    while(brdAry[grid1][grid2].getSlotVal() == 2){//looping until something other than 2 is found
        brdAry[grid1][grid2].setSlotVal(1);//Changing black piece to white
        //Move southwest one spot
        grid1++;
        grid2--;

    };

    if (brdAry[grid1][grid2].getSlotVal() == 1)
        return 1;
    else return 0;
}//End Function Flip BlackSW
/////////////////////////////////////////////////////////////////////////////////////////////
int checkForBlackW(Slot<int> **brdAry, int grid1, int grid2){
     int check =0;
    do{
        //Checking west one spot
        grid2--;
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 2);

    if (brdAry[grid1][grid2].getSlotVal() == 1 && check > 1)
        return 1;
    else return 0;
}//End function checkForBlackW

int flipBlackW(Slot<int> **brdAry, int grid1, int grid2){

        //Move west one spot
        grid2--;

    while(brdAry[grid1][grid2].getSlotVal() == 2){//looping until something other than 2 is found
        brdAry[grid1][grid2].setSlotVal(1);//Changing black piece to white
        //Move west one spot
        grid2--;

    };

    if (brdAry[grid1][grid2].getSlotVal() == 1)
        return 1;
    else return 0;
}//End Function Flip BlackW
////////////////////////////////////////////////////////////////////////////////////////////////
//Eight Directional Check & Flip Definitions Black Move Checking for White//////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
int checkForWhiteNW(Slot<int> **brdAry, int grid1, int grid2){
     int check =0;
    do{
        grid1--;//Checking northwest one spot
        grid2--;
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 1);

    if (brdAry[grid1][grid2].getSlotVal() == 2 && check > 1)
        return 1;
    else return 0;
}//End function checkForWhiteNW
int flipWhiteNW(Slot<int> **brdAry, int grid1, int grid2){

        grid1--;//Move northwest one spot
        grid2--;

    while(brdAry[grid1][grid2].getSlotVal() == 1){//looping until something other than 1 is found
        brdAry[grid1][grid2].setSlotVal(2);//Changing white piece to black
        grid1--;//Move northwest one spot
        grid2--;
    };

    if (brdAry[grid1][grid2].getSlotVal() == 2)//When a black is found, return
        return 1;
    else return 0;
}// End Function Flip White NW
//////////////////////////////////////////////////////////////////////////////////////////////
int checkForWhiteN(Slot<int> **brdAry, int grid1, int grid2){
    int check =0;
    do{
        grid1--;//Checking north one spot
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 1);

    if (brdAry[grid1][grid2].getSlotVal() == 2 && check > 1)
        return 1;
    else return 0;
}//End function checkForWhiteN

int flipWhiteN(Slot<int> **brdAry, int grid1, int grid2){

        grid1--;//Move north one spot


    while(brdAry[grid1][grid2].getSlotVal() == 1){//looping until something other than 1 is found
        brdAry[grid1][grid2].setSlotVal(2);//Changing white piece to black
        grid1--;//Move north one spot

    };

    if (brdAry[grid1][grid2].getSlotVal() == 2)
        return 1;
    else return 0;
}//End Function Flip WhiteN
//////////////////////////////////////////////////////////////////////////////////////////////
int checkForWhiteNE(Slot<int> **brdAry, int grid1, int grid2){
     int check =0;
    do{
        grid1--;//Checking northeast one spot
        grid2++;
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 1);

    if (brdAry[grid1][grid2].getSlotVal() == 2 && check > 1)
        return 1;
    else return 0;
}//End function checkForWhiteNE

int flipWhiteNE(Slot<int> **brdAry, int grid1, int grid2){

        grid1--;//Move northeast one spot
        grid2++;

    while(brdAry[grid1][grid2].getSlotVal() == 1){//looping until something other than 1 is found
        brdAry[grid1][grid2].setSlotVal(2);//Changing white piece to black
        grid1--;//Move northeast one spot
        grid2++;

    };

    if (brdAry[grid1][grid2].getSlotVal() == 2)
        return 1;
    else return 0;
}//End Function Flip WhiteNE
/////////////////////////////////////////////////////////////////////////////////////////////
int checkForWhiteE(Slot<int> **brdAry, int grid1, int grid2){
     int check =0;
    do{
        //Checking east one spot
        grid2++;
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 1);

    if (brdAry[grid1][grid2].getSlotVal() == 2 && check > 1)
        return 1;
    else return 0;
}//End function checkForWhiteE

int flipWhiteE(Slot<int> **brdAry, int grid1, int grid2){

        //Move east one spot
        grid2++;

    while(brdAry[grid1][grid2].getSlotVal() == 1){//looping until something other than 1 is found
        brdAry[grid1][grid2].setSlotVal(2);//Changing white piece to black
        //Move east one spot
        grid2++;

    };

    if (brdAry[grid1][grid2].getSlotVal() == 2)
        return 1;
    else return 0;
}//End Function Flip WhiteE
/////////////////////////////////////////////////////////////////////////////////////////////
int checkForWhiteSE(Slot<int> **brdAry, int grid1, int grid2){
    int check =0;
    do{
        //Checking southeast one spot
        grid1++;
        grid2++;
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 1);

    if (brdAry[grid1][grid2].getSlotVal() == 2 && check > 1)
        return 1;
    else return 0;
}//End function checkForWhiteSE

int flipWhiteSE(Slot<int> **brdAry, int grid1, int grid2){

        //Move southeast one spot
        grid1++;
        grid2++;

    while(brdAry[grid1][grid2].getSlotVal() == 1){//looping until something other than 1 is found
        brdAry[grid1][grid2].setSlotVal(2);//Changing white piece to black
        //Move southeast one spot
        grid1++;
        grid2++;

    };

    if (brdAry[grid1][grid2].getSlotVal() == 2)
        return 1;
    else return 0;
}//End Function Flip WhiteSE
/////////////////////////////////////////////////////////////////////////////////////////////
int checkForWhiteS(Slot<int> **brdAry, int grid1, int grid2){
    int check =0;
    do{
        //Checking south one spot
        grid1++;
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 1);

    if (brdAry[grid1][grid2].getSlotVal() == 2 && check > 1)
        return 1;
    else return 0;
}//End function checkForWhiteS

int flipWhiteS(Slot<int> **brdAry, int grid1, int grid2){

        //Move south one spot
        grid1++;


    while(brdAry[grid1][grid2].getSlotVal() == 1){//looping until something other than 1 is found
        brdAry[grid1][grid2].setSlotVal(2);//Changing white piece to black
        //Move south one spot
        grid1++;
        };

    if (brdAry[grid1][grid2].getSlotVal() == 2)
        return 1;
    else return 0;
}//End Function Flip WhiteS
/////////////////////////////////////////////////////////////////////////////////////////////
int checkForWhiteSW(Slot<int> **brdAry, int grid1, int grid2){
     int check =0;
    do{
        //Checking southwest one spot
        grid1++;
        grid2--;
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 1);

    if (brdAry[grid1][grid2].getSlotVal() == 2 && check > 1)
        return 1;
    else return 0;
}//End function checkForWhiteSW

int flipWhiteSW(Slot<int> **brdAry, int grid1, int grid2){

        //Move southwest one spot
        grid1++;
        grid2--;

    while(brdAry[grid1][grid2].getSlotVal() == 1){//looping until something other than 1 is found
        brdAry[grid1][grid2].setSlotVal(2);//Changing white piece to black
        //Move southwest one spot
        grid1++;
        grid2--;

    };

    if (brdAry[grid1][grid2].getSlotVal() == 2)
        return 1;
    else return 0;
}//End Function Flip WhiteSW
/////////////////////////////////////////////////////////////////////////////////////////////
int checkForWhiteW(Slot<int> **brdAry, int grid1, int grid2){
     int check =0;
    do{
        //Checking west one spot
        grid2--;
        check++;

    }while(brdAry[grid1][grid2].getSlotVal() == 1);

    if (brdAry[grid1][grid2].getSlotVal() == 2 && check > 1)
        return 1;
    else return 0;
}//End function checkForWhiteW

int flipWhiteW(Slot<int> **brdAry, int grid1, int grid2){

        //Move west one spot
        grid2--;

    while(brdAry[grid1][grid2].getSlotVal() == 1){//looping until something other than 2 is found
        brdAry[grid1][grid2].setSlotVal(2);//Changing black piece to white
        //Move west one spot
        grid2--;

    };

    if (brdAry[grid1][grid2].getSlotVal() == 2)
        return 1;
    else return 0;
}//End Function Flip WhiteW
/////////////////////////////////////////////////////////////////////////////////////////////
