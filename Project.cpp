
#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h" 
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; //Global pointer meant to instantiate a player object on the heap
GameMechs *myGM; 

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM -> getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs();
    myPlayer = new Player(myGM);

}

void GetInput(void)
{

    if(myGM -> getInput() != 0) //if input isn't null 
    {
        switch(myGM -> getInput())
        {
            case ' ':   //exit if space bar is pressed
            case 27:    //exit if ESC is pressed
                myGM -> setExitTrue();
                break;

            //add more cases here for food, score, lose, etc.

            default:
                break;
        
        }
    }
   
}

void RunLogic(void)
{
    myPlayer -> updatePlayerDir();  //update player direction 
    myPlayer -> movePlayer();       //update player movement 
        //ADD this

    //update player speed here too? or in get input? 
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    // draw screen 

    // ATTEMPT 1 

    // for(int i=0; i < (myGM -> getBoardSizeX()); i++) //for less than the amount of rows, 0-9 rows
    // {
    //     for(int j=0; j < (myGM -> getBoardSizeY()); j++) //for less than the amount of coloumns, 0-19 columns
    //     {
    //         //print '#' if in the first or last row, 0 or 9
    //         //print '#' if in the first or last column, 0 or 19
    //         if(i == 0 || i == ((myGM -> getBoardSizeX()) -1) || j == 0 || j == ((myGM -> getBoardSizeY()) -1))
    //         {
    //             MacUILib_printf("#");
    //         }
    //         // if the postion is the same as the current player position, print the player symbol 
    //         // else if(i == player.y && j == player.x)
    //         // {
    //         //     MacUILib_printf("%c", player.symbol);
    //         // }

    //         // Print a few randomly generated items on the board too
    //         else
    //         {
    //             int printedItem = 0; //tracking flag for if printed an item at this postion
    //             int k;
    //             for(k =0; k< 5; k++) //for looping through items in array
    //             {
    //                 if(myGM -> getItemList()[k].pos -> x == j && myGM -> getItemList()[k].pos -> y == i)  // If an item is at position (j, i)
    //                 {
    //                     MacUILib_printf("%c", myGM -> getItemList()[k].symbol); //print item
    //                     printedItem = 1; //change flag to true to show it's been printed
    //                 }
    //             }

    //             //if no random char was printed
    //             if(printedItem != 1)
    //             {
    //                 MacUILib_printf(" ");
    //             }
    //         }
    //     }
    //     MacUILib_printf("\n"); //move to next line
    // }

    // GET PLAYER X and Y HERE

    int playerX = myPlayer->getPlayerPos().pos->x;
    int playerY = myPlayer->getPlayerPos().pos->y;

    // BASIC RUNNING FRAME:

    for(int i=0; i < (myGM -> getBoardSizeX()); i++) //for less than the amount of rows, 0-9 rows
    {
        for(int j=0; j < (myGM -> getBoardSizeY()); j++) //for less than the amount of coloumns, 0-19 columns
        {
            //print '#' if in the first or last row, 0 or 9
            //print '#' if in the first or last column, 0 or 19
            if(i == 0 || i == ((myGM -> getBoardSizeX()) -1) || j == 0 || j == ((myGM -> getBoardSizeY()) -1))
            {
                MacUILib_printf("#");
            }
            // if the postion is the same as the current player position, print the player symbol 
            else if (i == playerY && j == playerX)
            {
                MacUILib_printf("%c", myPlayer->getPlayerPos().symbol);
                //runs but doesn't display anything
            }
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n"); //move to next line
    }


    // print statements 
    objPos playerPos = myPlayer -> getPlayerPos();

    MacUILib_printf("Player [x, y, sym] = [%d, %d, %c]\n", playerPos.pos -> x, playerPos.pos -> y, playerPos.symbol);

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    delete myPlayer; 
    delete myGM;

    MacUILib_uninit();
}
