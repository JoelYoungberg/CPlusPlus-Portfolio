/*
 *File: Project 01
 *Author: Joel Youngberg
 *Date Created: 9 Jul 13
 *Title: Archaeologist Dig Game
 *Purpose: Game where player tries to
 *obtain all parts of an artifact
 *before running out of funding to
 *excavate further...
 */

//Including all applicable libraries

#include <iostream>//I/O
#include <cstdlib>//Random Number Generation
#include <ctime>//Random Number Generation
#include <algorithm>//For random_shuffle function
#include <fstream>//For writing to and reading a file
#include <string>//For reading file
#include <iomanip>//Formatting
using namespace std;

//Global variables and constants
const int NUM_STAT_COL = 4;
const int NUM_LVL_ROWS = 2;
//Do not use these if possible!!

//All function prototypes
bool hasBeenUsed(int, static int[],const int);
void displayDugSO(int, string[]);
void find1(float &,int &);
void find2(float &,int &);
void find3(float &,int &);
void find4(float &,int &);
void recordStats(int &,int &,int &,float &, int, static float [][NUM_STAT_COL]);
void displayStats(string, int);

//Prototypes for bonus round
bool hasBeenUsed2(int, static int[], const int);
char displayDug(int);
void displayDugXO(int,string[]);
void digResult1(float &,int &,int &);
void digResult2(float &,int &);
void digResult3(float &,int &);
void digResult4(float &,int &);
void digResult5(float &,int &);
void digResult6(float &,int &);
void recordStats2(int &,int &,int &,float &, int, static float [][NUM_STAT_COL]);



//Starting executable code @ function main:

int main()
{
  //Declaring Variables
    //Initialize Randomization to be different each time
    srand(static_cast<unsigned int>(time(0)));
    //Array for holding dig site values
    const int SIZE1 = 20;
    int digSites [SIZE1] = {1,1,1,1,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4};//array for controlling find scenario odds
    static int usedOrNot1 [SIZE1] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};//array for storing boolean

    static float playerStats[NUM_LVL_ROWS][NUM_STAT_COL]= {0,0,0,0,0,0,0,0};
    int digSiteChoice;//user input variable
    int digFind;//Simplification variable for random array value transition to switch st.
    float money = 6000;//running money total
    int shardCount =0;//total of urn pieces found
    int winsLv1 = 0;
    int lossesLv1 = 0;
    int winsLv2 = 0;
    int lossesLv2 = 0;
    int gamesPlayed = 0;
    string name;
    string displayDug1[SIZE1] = {"S0","S1","S2","S3","S4","S5","S6","S7","S8","S9","S10","S11","S12","S13","S14","S15","S16","S17","S18","S19"};

    //Shuffle dig site values to create different game each time it is run
    random_shuffle(&digSites[0], &digSites[20]);

    cout << "Welcome to the archaeological dig game! Can you uncover all of" << endl;
    cout << "the pieces of the mystery artifact before you run out of money?" << endl;
    cout << endl;
    cout << "You have been commissioned to find the lost sacred relic" << endl;
    cout << "'The Urn of Souls'! The World History Granting Institution has" << endl;
    cout << "awarded your team $6000 for an exploration of the Himalayan " << endl;
    cout << "Mountains, with the hope that you will recover the rare " << endl;
    cout << "artifact. Clues from your research have narrowed the search to " << endl;
    cout << "a final area in which you have chosen to begin excavating." << endl;
    cout << "Legend states that the artifact was broken into 7 pieces long" << endl;
    cout << "ago during a struggle between two great kings over its mythic power." << endl;
    cout << "Although the rumors concerining the Urn's power over bringing the" << endl;
    cout << "dead back to life have not been confirmed, its value has. This ancient"<< endl;
    cout << "relic is worth $50,000 to the right buyer!! Use caution, however, because" << endl;
    cout << "each place you dig will cost your team $400" << endl;
    cout << "Can you uncover the complete artifact before your" << endl;
    cout << "funds run out?" << endl;
    cout << endl;

    //Pause after story before game entrance... thought it gives it a nice transition
    cout << endl;
    cout << "Please enter your name: " << endl;
    cin >> name;

    //Looping until win/loss - player loses at money < 400, wins at 7 shards/pieces of urn
    while (money >= 400 && shardCount < 7){

    //Looping if choice is not between 0-19 and if site hase been chosen before...
    do {
    do {
    cout << "                           The Himalayan Mountains" << endl;
        cout << "                                                 ... " << endl;
        cout << "                                   ..           ...... " << endl;
        cout << "                        ...     ......       .......... " << endl;
        cout << "              ...     ......   .........   .............      ..  " << endl;
        cout << "             .....   ........ ........... ...............   ..... " << endl;
        cout << "           ....... ....................... ........................ " << endl;
        cout << "         '''''''("<<displayDug1[4]<<")'''''''("<<displayDug1[19]<<")''''''''''''("<<displayDug1[5]<<")''''''''''''("<<displayDug1[12]<<")'''' " << endl;
        cout << "      ''''("<<displayDug1[9]<<")''''''''''''''''''''''''''''''''''("<<displayDug1[2]<<")''''''''''''''''''' " << endl;
        cout << "    ''''''''''''''''''''("<<displayDug1[11]<<")''''''("<<displayDug1[15]<<")'''''''''''''''("<<displayDug1[1]<<")'''''''("<<displayDug1[3]<<")'''' " << endl;
        cout << "  ("<<displayDug1[13]<<")'''''''("<<displayDug1[18]<<")'''''''''''''''''''''("<<displayDug1[14]<<")'''''''''''''''''''''''("<<displayDug1[8]<<")''''' " << endl;
        cout << " ''''''''''''''''''''''''''("<<displayDug1[7]<<")''''''''''''''("<<displayDug1[17]<<")'''''''''''''''''''''''''''' " << endl;
        cout << "''''''("<<displayDug1[0]<<")'''''''("<<displayDug1[6]<<")''''''''''''''("<<displayDug1[10]<<")'''''''''''''''''''''("<<displayDug1[16]<<")'''''''''''''''' " << endl;
    cout << "Please choose a dig location from the map above! Enter the number of the " << endl;
    cout << "dig site which you wish to dig and check for pieces of the artifact..." << endl;
    cout << "(you cannot dig at any location more than once)" << endl;
    cout << "(you must choose a number between 0-19)" << endl;


    //Getting excavation site choice from user:
    cin >> digSiteChoice;

    hasBeenUsed(digSiteChoice,usedOrNot1,SIZE1);

    displayDugSO(digSiteChoice,displayDug1);

    //First validation of entry, must be between 0-19
        }while(digSiteChoice < 0 || digSiteChoice > 19);
            //Second Validation, entry must be a new entry which has not
            //been entered before:
        }while(hasBeenUsed(digSiteChoice,usedOrNot1,SIZE1));

    //Passing excavation choice to array digSites to obtain
    //randomized value between 1-4
    digSites[digSiteChoice];


    //Set result equal to new variable to simplify and pass to switch statement
     digFind = digSites[digSiteChoice];

     //The switch statement with the passed randomized value
     //decides the outcome of the dig!

     switch (digFind)
     {
     case 1:{
         find1(money, shardCount);

         system ("pause");
         break;
     }
     case 2:{
         find2(money, shardCount);

         system ("pause");
         break;
     }
     case 3:{
         find3(money, shardCount);

         system ("pause");
         break;
     }
     case 4:{
         find4(money, shardCount);

         system ("pause");
         break;
     }
     }//Close switch statement

}//Close While loop win/loss

    if (shardCount == 7){
        cout << endl;
        cout << endl;
        cout << "Excellent work!! You have recovered the Urn of Souls!!!" << endl;
        cout << "After putting the pieces together to restore the urn" << endl;
        cout << "and presenting it to The World History Granting Institution" << endl;
        cout << "The institution paid you $50,000!!! for the urn" << endl;
        cout << endl;
        cout <<"       |*********|    "<< endl;
        cout <<"     |#^#^#^#^#^#^#|   "<< endl;
        cout <<"   |%%%%%%%%%%%%%%%%%|   "<< endl;
        cout <<"    |***************|   "<< endl;
        cout <<"     |#^#^#^#^#^#^#|   "<< endl;
        cout <<"      |%%%%%%%%%%%|   "<< endl;
        cout <<"       |*********|   "<< endl;
        cout << endl;
        cout << "    The Urn of Souls!!!!" << endl;
        cout << endl;
        money += 50000;
        cout << "Your total bounty for this adventure is $" << money << endl;
        cout << endl;
        winsLv1 +=1;
        gamesPlayed +=1;
        recordStats(winsLv1,lossesLv1,gamesPlayed,money,NUM_LVL_ROWS,playerStats);
        system ("pause");
    }else {
        cout << endl;
        cout << "I am sorry, you have run out of money and The World History" << endl;
        cout << "Granting Institution has decided to stop funding" << endl;
        cout << "your search for the Urn of Souls" << endl;
        cout << endl;
        lossesLv1 += 1;
        gamesPlayed += 1;

        recordStats(winsLv1,lossesLv1,gamesPlayed,money,NUM_LVL_ROWS,playerStats);
        displayStats(name, gamesPlayed);
    }



    if (shardCount == 7){


        /*
          Level 2: Bonus Round: Egypt
         *Can you find the jackal
         *idol before the competition?
         */

          //Declaring Variables for Level 2


                const int SIZE = 30;
                int digSites2 [SIZE] = {1,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,5,6,6,6,6,6};//array for find scenario odds- only one idol(1)+more money gains(2)
                string displayDug[SIZE] = {"X0","X1","X2","X3","X4","X5","X6","X7","X8","X9","X10","X11","X12","X13","X14","X15","X16","X17","X18","X19","X20","X21","X22","X23","X24","X25","X26","X27","X28","X29"};
                static int usedOrNot [SIZE] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};//array for storing boolean values to decrement
                int digSiteChoice2 =0;
                int digFind2 =0;
                int userFound = 0;
                int viktorFound = 0;

            //Shuffle dig site values to create different game each time it is run
                random_shuffle(&digSites2[0], &digSites2[30]);

            //Opening Statement
            cout << "Great job! You made it to the level 2 bonus round!!!" << endl;
            cout << endl;
                cout << "You have decided to utilize the funds from your last expedition" << endl;
                cout << "to follow your dream as an archaeologist... you are now funding" << endl;
                cout << "yourself on a new venture to search for the coveted Black Onyx " << endl;
                cout << "Anubis idol, otherwise known as the 'Jackal of Egypt'. " << endl;
                cout << "artifact. Clues from your research have narrowed the search to " << endl;
                cout << "a final area in which you have chosen to begin excavating." << endl;
                cout << "However, this time your research was compromised by one of " << endl;
                cout << "your fiercest competitors and enemies, the illustrious Viktor" << endl;
                cout << "Findingston!! Viktor broke into your research facility and found "<< endl;
                cout << "your research. He knows your clues and is racing you to find the" << endl;
                cout << "Jackal first! Can you find the Jackal of Egypt before Viktor" << endl;
                cout << "gets it? Be careful where you dig because each attempt will" << endl;
                cout << "cost you $500.00 this time, and although there are many other " << endl;
                cout << "exciting treasures to find, only the Jackal of Egypt will bring" << endl;
                cout << "a whopping $100,000.00 to the right buyer!!" << endl;
                cout << endl;
                cout << "Be careful and be quick!! Viktor is closing in on the Jackal too!!" << endl;
                cout << "If you don't find it in time, Viktor will beat you to it..." << endl;

                //Pause after story before game entrance... thought it gives it a nice transition again
                    cout << endl;
                    system ("pause");

                    //Looping until win/loss - player loses at money < 400, wins at 8 shards/pieces of urn
                        while (money >= 500 && userFound == 0 && viktorFound < 15){

                do{
                do{
               cout << endl;
               cout << "                             /.\. " << endl;
               cout << "               /.\.          /...\.\ " << endl;
               cout << "              /...\.\        /.....\.\      /.\.   " << endl;
               cout << "             /.....\.\      /.......\.\    /...\.\ " << endl;
               cout << "            /.......\.\    /.........\.\  /.....\.\ " << endl;
               cout << "           /.........\.\  /...........\.\/.......\.\     " << endl;
               cout << "__________/...........\./.............\.\........\.\__________" << endl;
               cout << "-------("<<displayDug[0]<<")---------("<<displayDug[5]<<")----------("<<displayDug[17]<<")--------------("<<displayDug[14]<<")---" << endl;
               cout << "--("<<displayDug[1]<<")-----------------------("<<displayDug[21]<<")-------------("<<displayDug[2]<<")-----------" << endl;
               cout << "-----------------("<<displayDug[15]<<")------------------("<<displayDug[26]<<")-----------------" << endl;
               cout << "--("<<displayDug[7]<<")----("<<displayDug[24]<<")-----------------("<<displayDug[20]<<")----------------("<<displayDug[11]<<")----" << endl;
               cout << "--------------------("<<displayDug[3]<<")--------------------("<<displayDug[13]<<")-------------" << endl;
               cout << "-----("<<displayDug[27]<<")------------------("<<displayDug[22]<<")-------------------("<<displayDug[18]<<")-----" << endl;
               cout << "-------------------------------------("<<displayDug[28]<<")--------------------" << endl;
               cout << "--("<<displayDug[12]<<")----------("<<displayDug[10]<<")----------------------("<<displayDug[16]<<")-------("<<displayDug[4]<<")--" << endl;
               cout << "---------------------------("<<displayDug[19]<<")-------------------("<<displayDug[23]<<")------" << endl;
               cout << "-----("<<displayDug[8]<<")---------------------("<<displayDug[27]<<")---------------------------" << endl;
               cout << "--------------("<<displayDug[25]<<")---------------------("<<displayDug[6]<<")-------("<<displayDug[29]<<")------" << endl;
               cout << "--------------------------------------------------------------" << endl;
                    cout << "Please choose a dig location from the map above!" << endl;
                    cout << "Enter the number of the dig site which you wish" << endl;
                    cout << "to dig and check for the Jackal of Egypt..." << endl;
                    cout << "(you cannot dig at any location more than once)" << endl;
                    cout << "(you must choose a number between 0-29)" << endl;

                    //Getting excavation site choice from user:
                        cin >> digSiteChoice2;
                        hasBeenUsed2(digSiteChoice2,usedOrNot,SIZE);
                        displayDugXO(digSiteChoice2,displayDug);

                }while(digSiteChoice2 < 0 || digSiteChoice2 > 29);
                    }while(hasBeenUsed2(digSiteChoice2,usedOrNot,SIZE));


                    //Passing excavation choice to array digSites to obtain
                    //randomized value between 1-4
                    digSites2[digSiteChoice2];


                    //Set result equal to new variable to simplify and pass to switch statement
                     digFind2 = digSites2[digSiteChoice2];

                     //The switch statement with the passed randomized value
                     //decides the outcome of the dig!
                     cout << setprecision(2) << showpoint << fixed;

                     switch (digFind2)
                     {
                     case 1:{
                         digResult1(money,userFound,winsLv2);
                         system ("pause");
                         break;
                     }
                     case 2:{
                         digResult2(money,viktorFound);
                         system ("pause");
                         break;
                     }
                     case 3:{
                         digResult3(money,viktorFound);
                         system ("pause");
                         break;
                     }
                     case 4:{
                         digResult4(money,viktorFound);
                         system ("pause");
                         break;
                     }
                     case 5:{
                         digResult5(money,viktorFound);
                         system ("pause");
                         break;
                     }
                     case 6:{
                         digResult6(money,viktorFound);
                         system ("pause");
                         break;
                     }
                 }//Close switch statement
             }//Close Win Loss Loop

                        if(viktorFound == 15){
                            cout << "Oh no, Viktor beat you, he has found the Jackal of Egypt!" << endl;
                            cout << "Better luck next time..." << endl;
                            lossesLv2 += 1;
                        }
                        else if(userFound == 1){
                            cout << "You are a rich archaeologist now!!" << endl;
                            cout << "But better still, you have beaten your arch rival Viktor Findingston!!" << endl;
                        }

                        //Call Record Stats Function2
                        recordStats2(winsLv2,lossesLv2,gamesPlayed,money,NUM_LVL_ROWS,playerStats);

                        //Display stats with bonus round material here
                        displayStats(name, gamesPlayed);


    }//Close (if shard == 7)//Close Bonus Round





//Exit Program - - Close main
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    return 0;
}//Exit Program - - Close main

bool hasBeenUsed(int digSiteChoice, static int usedOrNot1[], const int SIZE1){

        usedOrNot1[digSiteChoice] -- ; //Decrementing array usedOrNot(all 2's) to return value to boolean function hasBeenUsed
        return usedOrNot1[digSiteChoice];
    }

void displayDugSO(int digSiteChoice,string displayDug1[]){

    displayDug1[digSiteChoice] = "O";
}

void find1(float &money,int &shardCount){
    cout << endl;
    cout << "You found a shard of the Urn of Souls!!" << endl;
    cout << endl;
    cout <<"              ___    "<< endl;
    cout <<"           __/ ^#|   "<< endl;
    cout <<"        __/%%%%%%|   "<< endl;
    cout <<"       |*********/   "<< endl;
    cout << endl;
    cout << "The excavation cost $400.00, but it was worth it!"<< endl;
    cout << "The World History Granting Institution is excited!!!"<< endl;
    cout << "They awarded your team an additional $250 to show"<< endl;
    cout << "their thanks and support your expedition further!"<< endl;
    money -= 150;
    shardCount += 1;
    cout << "You have a total of: " << shardCount << " piece(s) of the Urn!" << endl;
    cout << "and you have $" << money << "left..." << endl;
    cout << endl;
}

void find2(float &money,int &shardCount){
    cout << endl;
    cout << "Awwwww maaaaaaaan there's nothing here...." << endl;
    cout << endl;
    cout <<"       ??????????    "<< endl;
    cout <<"     ???        ???   "<< endl;
    cout <<"     ??          ??   "<< endl;
    cout <<"              ????   "<< endl;
    cout <<"          ??????     "<< endl;
    cout <<"         ???   "<< endl;
    cout <<"         ??     "<< endl;
    cout << endl;
    cout <<"         ?? "<<endl;
    cout <<"        ????"<<endl;
    cout <<"         ?? "<<endl;
    cout << endl;
    cout << "I'm sorry, you and your team were unable to find anything at this site..." << endl;
    cout << "The excavation cost $400, and you left feeling jipped... better do a little" << endl;
    cout << "more research..."<< endl;
    money -= 400;
    cout << "You have a total of: " << shardCount << " piece(s) of the Urn..." << endl;
    cout << "and you now have $" << money << "left..." << endl;
    cout << endl;
}

void find3(float &money,int &shardCount){
    cout <<"               You found some old coins......." << endl;
    cout << endl;
    cout << "                     ooooo " << endl;
    cout << "                  o    $    o " << endl;
    cout << "                o    $$$$$    o " << endl;
    cout << "              o    $$  $  $$    o " << endl;
    cout << "             o    $$   $   $$    o " << endl;
    cout << "            o      $$  $          o " << endl;
    cout << "            o        $$$$$        o " << endl;
    cout << "            o          $  $$      o " << endl;
    cout << "             o    $$   $   $$    o " << endl;
    cout << "              o    $$  $  $$    o " << endl;
    cout << "                o    $$$$$    o " << endl;
    cout << "                  o    $    o " << endl;
    cout << "                     ooooo " << endl;
    cout << endl;
    cout << "The coins are only worth about $150..." << endl;
    cout << "The excavation cost $400, so it was not really worth it..."<< endl;
    cout << "but at least you found something to dampen the blow of the cost..." << endl;
    money -= 250;
    cout << "You have a total of: " << shardCount << " piece(s) of the Urn!" << endl;
    cout << "and you have $" << money << "left..." << endl;
    cout << endl;
}

void find4(float &money,int &shardCount){
    cout << endl;
    cout << "You and your team were attacked by wild, ravenous yetis" << endl;
    cout << "during the excavation!!!" << endl;
    cout <<"      RAAAAAAAAAAWWWWWWRRRRRRR!!!!" << endl;
    cout << endl;
    cout <<"            #########    "<< endl;
    cout <<"           ###O###O###   "<< endl;
    cout <<"           ####@#@####   "<< endl;
    cout <<"           ###|||||###   "<< endl;
    cout <<"            #########  "<< endl;
    cout <<"             #######    "<< endl;
    cout <<"         ###############   "<< endl;
    cout <<"     ######################  "<< endl;
    cout <<"     #### ############# ####  "<< endl;
    cout <<"     #### ############# #### "<< endl;
    cout <<"     $$$$ ############# $$$$"<< endl;
    cout <<"          #####   #####  "<< endl;
    cout <<"          #####   #####  "<< endl;
    cout <<"          #####   #####  "<< endl;
    cout <<"          #####   #####  "<< endl;
    cout << endl;
    cout << "The excavation cost $400, and you lost another $300 in supplies because" << endl;
    cout << "you had to leave things behind as you fled to safety!!" << endl;
    money -= 700;
    cout << "You have a total of: " << shardCount << " piece(s) of the Urn!" << endl;
    cout << "and you have $" << money << "left..." << endl;
}

void recordStats(int &winsLv1,int &lossesLv1,int &gamesPlayed,float &money, int NUM_LVL_ROWS, static float playerStats[][NUM_STAT_COL]){

    //Fill array with player stats
    playerStats[0][0] += winsLv1;
    playerStats[0][1] += lossesLv1;
    playerStats[0][2] += gamesPlayed;

    if(playerStats[0][3] < money)
    playerStats[0][3] = money;

    //Create labels for output file:
    string labelWins = "Wins: ";
    string labelLosses = "Losses: ";
    string labelGamesPlayed = "GamesPlayed: ";
    string labelMoneyScore = "HighMoneyScore: ";

    //Send win/loss/score record to file
    ofstream fout;
    // open file for appending
    fout.open("C:\\Users\\ElectricDrake\\Desktop\\numberOfWins_Losses.txt",ios::app);
    fout << labelWins << playerStats[0][0] << endl;//Printing number of wins for Level 1 to file
    fout << labelLosses << playerStats[0][1] << endl;//Printing number of losses for Level 1 to file
    fout << labelGamesPlayed << playerStats[0][2] << endl;//Printing number of games played to file
    fout << labelMoneyScore << playerStats[0][3] << endl;//Printing total money/score to file
    fout.close();

}

void recordStats2(int &winsLv2,int &lossesLv2,int &gamesPlayed,float &money, int NUM_LVL_ROWS, static float playerStats[][NUM_STAT_COL]){



    //Fill array with player stats
    playerStats[1][0] += winsLv2;
    playerStats[1][1] += lossesLv2;
    playerStats[1][2] += gamesPlayed;

    if(playerStats[1][3] < money)
           playerStats[1][3] = money;

    //Create labels for output file:
    string labelWins = "BonusRoundWins: ";
    string labelLosses = "BonusRoundLosses: ";
    string labelGamesPlayed = "GamesPlayed: ";
    string labelMoneyScore = "HighMoneyScore: ";

    //Send win/loss/score record to file
    ofstream fout;
    // open file for appending
    fout.open("C:\\Users\\Public\\numberOfWins_Losses.txt",ios::app);
    fout << labelWins << playerStats[1][0] << endl;//Printing number of wins for Level 1 to file
    fout << labelLosses << playerStats[1][1] << endl;//Printing number of losses for Level 1 to file
    fout << labelGamesPlayed << playerStats[1][2] << endl;//Printing number of games played to file
    fout << labelMoneyScore << playerStats[1][3] << endl;//Printing total money/score to file
    fout.close();

}
void displayStats(string name, int gamesPlayed){//displaying win, loss, games played, and high score stats

    //variables
    string getLabelWins;
    string getLabelLosses;
    string getLabelGmPl;
    string getLabelScore;

    int totWins=0, runtotWins=0;
    int totLoss=0, runtotLoss=0;
    int totGmPl=0, runtotGmPl=0;
    int score=0, highScore=0;

        ifstream inFile;

        inFile.open("C:\\Users\\Public\\numberOfWins_Losses.txt");

        while (inFile){


            for(int i = 0; i < 20; i++){
        inFile >> getLabelWins >> totWins;//reading output storage file into temp variables
        inFile >> getLabelLosses >> totLoss;
        inFile >> getLabelGmPl >> totGmPl;
        inFile >> getLabelScore >> score;

        runtotWins += totWins;
        runtotLoss += totLoss;
        runtotGmPl += totGmPl;

        }

        inFile.close();

        }


        cout << "The current stats for " << name << " are: " << endl;
        cout << "Wins: " << totWins << endl;
        cout << "Losses: " << totLoss << endl;
        cout << "Games Played: " << totGmPl << endl;
        cout << "Score: $" << score << endl;
        cout << endl;

}

//Bonus round function definitions
bool hasBeenUsed2(int digSiteChoice2, static int usedOrNot[], const int SIZE){

    usedOrNot[digSiteChoice2] -- ; //Decrementing array usedOrNot(all 2's) to return value to boolean function hasBeenUsed
    return usedOrNot[digSiteChoice2];
}

void displayDugXO(int digSiteChoice2,string displayDug[]){

    displayDug[digSiteChoice2] = "O";
}

void digResult1(float &money,int &userFound, int &winsLv2){
    cout << endl;
    cout <<              "You found the Jackal of Egypt!!" << endl;
        cout << "                               II" << endl;
        cout << "                               III" << endl;
        cout << "                               IIII" << endl;
        cout << "                               IIIII" << endl;
        cout << "                               IIIIIIII" << endl;
        cout << "                                IIIIIIIIIII" << endl;
        cout << "                                IIIIIIIIIIIIIIIIIII" << endl;
        cout << "                                IIIIIIIIIIIIIIIIII" << endl;
        cout << "                               IIIIIIII" << endl;
        cout << "        IIIII                 IIIIIIII" << endl;
        cout << "      IIIIIIIII              IIIIIIIII" << endl;
        cout << "     IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << endl;
        cout << "    IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << endl;
        cout << "   IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << endl;
        cout << "  IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << endl;
        cout << "  IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << endl;
        cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "The excavation cost $500.00, but it was worth it!"<< endl;
    cout << "The World History Granting Institution found out!!!"<< endl;
    cout << "They bought the Jackal for their collection for $100,000.00!!!"<< endl;
    cout << "Now you can afford to buy a new BENTLEY for Dr. Lehr!, or simply"<< endl;
    cout << "go on another expedition... or two... or three..." << endl;
    money += 100000;
    userFound += 1;
    winsLv2 += 1;
    cout << "You have $" << money << " and are ready for more adventure!!" << endl;
}

void digResult2(float &money,int &viktorFound){
    cout <<"   Not the Jackal... but at least something nice!!" << endl;
    cout << endl;
        cout << "                     ooooo " << endl;
        cout << "                  o    $    o " << endl;
        cout << "                o    $$$$$    o " << endl;
        cout << "              o    $$  $  $$    o " << endl;
        cout << "             o    $$   $   $$    o " << endl;
        cout << "            o      $$  $          o " << endl;
        cout << "            o        $$$$$        o " << endl;
        cout << "            o          $  $$      o " << endl;
        cout << "             o    $$   $   $$    o " << endl;
        cout << "              o    $$  $  $$    o " << endl;
        cout << "                o    $$$$$    o " << endl;
        cout << "                  o    $    o " << endl;
        cout << "                     ooooo " << endl;
        cout << endl;
    cout << "but you did find something valuable... old gold egyptian" << endl;
    cout << "coinage worth about $1500..." << endl;
    cout << "The excavation cost $500, but you still made a hefty profit..."<< endl;
    money += 1000;
    viktorFound += 1;
    cout << "You now have $" << money << endl;
    cout << endl;
}

void digResult3(float &money,int &viktorFound){
    cout << endl;
    cout << "Awwwww maaaaaaaan there's nothing here...." << endl;
    cout << endl;
    cout <<"       ??????????    "<< endl;
    cout <<"     ???        ???   "<< endl;
    cout <<"     ??          ??   "<< endl;
    cout <<"              ????   "<< endl;
    cout <<"          ??????     "<< endl;
    cout <<"         ???   "<< endl;
    cout <<"         ??     "<< endl;
    cout << endl;
    cout <<"         ?? "<<endl;
    cout <<"        ????"<<endl;
    cout <<"         ?? "<<endl;
    cout << endl;
    cout << "I'm sorry, you were unable to find anything at this site..." << endl;
    cout << "The excavation cost $500, and you left feeling jipped... better do a little" << endl;
    cout << "more research..."<< endl;
    money -= 500;
    viktorFound += 1;
    cout << "and you now have $" << money << "left..." << endl;
    cout << endl;
}

void digResult4(float &money,int &viktorFound){
    cout << endl;
    cout <<"     OUCH THAT STINGS...! WHAT WAS THAT!!!!" << endl;
    cout <<"        You were attacked by scorpions" << endl;
    cout << "          during the excavation!!!" << endl;
    cout << endl;
        cout << "              (oo)  " << endl;
        cout << "            (o)  (o) " << endl;
        cout << "           (o)    (o) " << endl;
        cout << "            (O)    V " << endl;
        cout << "             (O) " << endl;
        cout << "          __(oOo)__ " << endl;
        cout << "        ____(oOo)___/ " << endl;
        cout << "       /___(oOOOo)___/ " << endl;
        cout << "       /   (oOOOo) " << endl;
        cout << "         (oo(OOO)oo) " << endl;
        cout << "       (o)   (M)   (o) " << endl;
        cout << "     (o)             (o) " << endl;
        cout << "    () ()           () () " << endl;
    cout << endl;
    cout << "The excavation cost $500, and you lost another $300 because" << endl;
    cout << "you had to buy some antidote to neutralize the scorpion stings!!" << endl;
    money -= 800;
    viktorFound += 1;
    cout << "You now have $" << money << " left..." << endl;
}

void digResult5(float &money, int &viktorFound){
    cout << endl;
    cout << "You found an ancient scarab beetle necklace!!!!" << endl;
    cout << endl;
        cout << "                    o     o    " << endl;
        cout << "                    o     o    " << endl;
        cout << "                     o   o    " << endl;
        cout << "                      o o    " << endl;
        cout << "                      ooo " << endl;
        cout << "                   oOO   OOo " << endl;
        cout << "                 oOO       OOo " << endl;
        cout << "                oOO         OOo " << endl;
        cout << "                 oOO       OOo " << endl;
        cout << "                   oOO   OOo " << endl;
        cout << "                   () ooo () " << endl;
        cout << "                 ||         || " << endl;
        cout << "                ||  (|___|)  || " << endl;
        cout << " _________________|_(.....)_|_________________ " << endl;
        cout << "  <<<<<<<<UUUUUUUUU(.......)UUUUUUUUU>>>>>>>>  " << endl;
        cout << "   <<<<<<<<UUUUUUU(____|____)UUUUUUU>>>>>>>> " << endl;
        cout << "     <<<<<<<<<UUUUU(...|...)UUUUU>>>>>>>>> " << endl;
        cout << "      <<<<<<<<<<<<(....|....)>>>>>>>>>>>> " << endl;
        cout << "        <<<<<<<<<<<(...|...)>>>>>>>>>>> " << endl;
        cout << "                 || (..|..) || " << endl;
        cout << "                ||    (|)    || " << endl;
        cout << "                  ()       () " << endl;
    cout << endl;
    cout << "The excavation cost $500, but it was worth it!!!!" << endl;
    cout << "The necklace is beautifully adorned with jade and gold!!" << endl;
    cout << "It is worth $10,000!!" << endl;
    money += 9500;
    viktorFound += 1;
    cout << "You now have a total of $" << money << endl;
}

void digResult6(float &money,int &viktorFound){
    cout << endl;
    cout <<"   You found an ancient gold ahnk!!!!" << endl;
    cout << endl;
        cout << "         ooooo " << endl;
        cout << "        ooooooo " << endl;
        cout << "       ooo   ooo " << endl;
        cout << "       oo     oo " << endl;
        cout << "        oo   oo " << endl;
        cout << "         oo oo " << endl;
        cout << "  |O ____/OOO ____/O| " << endl;
        cout << "  |OOOOOOOOOOOOOOOOO| " << endl;
        cout << "  |OOOOOOOOOOOOOOOOO| " << endl;
        cout << "  |O/     OOO      O| " << endl;
        cout << "          OOO " << endl;
        cout << "          OOO " << endl;
        cout << "          OOO " << endl;
        cout << "          OOO " << endl;
        cout << "        /OOOOO\ " << endl;
        cout << "       /OOOOOOO\ " << endl;
        cout << "      /OOOOOOOOO\ " << endl;
    cout << endl;
    cout << "This ahnk is worth about $5000..." << endl;
    cout << "The excavation cost $500, but you still made a hefty profit..."<< endl;
    money += 4500;
    viktorFound += 1;
    cout << "You now have $" << money << endl;
    cout << endl;
}




