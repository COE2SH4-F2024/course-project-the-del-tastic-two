
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

    while(!myGM -> getExitFlagStatus()) //while it's not true?
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
    if(MacUILib_hasChar() != 0)
    {
        char input = MacUILib_getChar();
        myGM->setInput(input);
    }

}

void RunLogic(void)
{
    myPlayer -> updatePlayerDir();  //update player direction 
    myPlayer -> movePlayer();       //update player movement 
        //ADD this

    //update player speed here too? or in get input? 

    // logic updated:
    char input = myGM->getInput();
    MacUILib_printf("Debug: Input received '%c' (%d)\n", input, input);
    
    if(input != 0) //if input isn't null 
    {
        switch(input)
        {
            case ' ':   // Exit if space bar is pressed
            case 27:    // Exit if ESC is pressed
                myGM -> setExitTrue();
                MacUILib_printf("Debug: Exit triggered\n");
                break;

            case 'p':
                MacUILib_printf("Debug: The score is: %d\n", myGM->getScore());
                break; //don't think this is working

            //these don't work either 
            case 43: // '+'
                myGM -> increaseSpeed();
                MacUILib_printf("Player speed increased\n");
                    //update print statement later
                break;
            case 45: // '-'
                myGM -> decreaseSpeed();
                MacUILib_printf("Player speed decreased\n");
                break;


            //add more cases here for food, score, lose, etc.

            default:
                break;
        
        }
        // Clear input after processing
        myGM->clearInput();
    }
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
    char playerSymbol = myPlayer->getPlayerPos().symbol;

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
                MacUILib_printf("%c", playerSymbol);
                //runs but doesn't display anything
            }
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n"); //move to next line
    }


    // Debug: Print player postion 
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
