
#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h" 
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; //Global pointer meant to instantiate a player object on the heap
GameMechs *myGM; // Container class (on the heap)

bool collision;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    //while(myGM -> getExitFlagStatus() == false) //ignore
    while(!myGM -> getExitFlagStatus()) //while it's not true
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
    //myPlayer = new Player(myGM);

    myPlayer = new Player(myGM);

    // first call the foodGeneration function to initially populate it
    myGM->generateFood(myPlayer->getPlayerPosList());

    collision = false;
}

void GetInput(void)
{
    myGM -> getAsyncInput();

    char input = myGM->getInput();
    MacUILib_printf("Debug: Captured Input: %c\n", input);

    // works !
    // Debug feature: Regenerate food when 'f' is pressed
    if (myGM->getInput() == 'f') {
        MacUILib_printf("Debug: Food regeneration triggered.\n");
        myGM->generateFood(myPlayer->getPlayerPosList());
        myGM->clearInput(); // Clear input after processing
    }
}

void RunLogic(void)
{
    //char input = myGM->getInput();
    //MacUILib_printf("Debug: Input in RunLogic: %c", input);

 

    myPlayer->updatePlayerDir();
    myPlayer->movePlayer(); 
    myPlayer -> selfCollisionCheck();

    collision = myPlayer -> selfCollisionCheck();
    if(collision == true)
    {
        myGM -> setLoseFlag();
        myGM -> setExitTrue();
    }


    //myPlayer->growSnake();
    

    
}


void DrawScreen(void)
{
    MacUILib_clearScreen();    

    // GET BOARDSIZE
    int boardX = myGM -> getBoardSizeX();
    int boardY = myGM -> getBoardSizeY();
    
    // GET SCORE
    int score = myGM -> getScore();



    // GET PLAYER X and Y HERE
    // objPos playerPosArrayList = myPlayer->getPlayerPosList();

    // int playerx = playerPosArrayList.pos -> x;
    // int playery = playerPosArrayList.pos -> y;

    // // GET FOOD POSITION
    objPos foodPos = myGM -> getFoodPos();

    //attempt 3:
        // PRINT
    for (int x = 0; x < boardY; x++)
    {
        for (int y = 0; y < boardX; y++)
        {
            if (x == 0 || x == (boardY - 1) || y == 0 || y == (boardX - 1))
            { 
                // Borders
                MacUILib_printf("%c", '#');
            }
            else
            {
                bool playerPrinted = false;

                // Check if the current position is occupied by any part of the player
                for (int k = 0; k < myPlayer->getPlayerPosList()->getSize(); k++)
                {
                    objPos playerBody = myPlayer->getPlayerPosList()->getElement(k);

                    if (playerBody.pos->x == y && playerBody.pos->y == x)
                    {
                        MacUILib_printf("%c", playerBody.symbol);
                        playerPrinted = true;
                        break;
                    }
                }

                // Check if the current position is occupied by the food
                if (!playerPrinted)
                {
                    if (foodPos.pos->x == y && foodPos.pos->y == x)
                    {
                        MacUILib_printf("%c", foodPos.symbol);
                    }
                    else
                    {
                        MacUILib_printf("%c", ' ');
                    }
                }
            }
        }
        MacUILib_printf("%c", '\n');
    }


    // PRINT STATEMENTS FOR GAME PLAY
    MacUILib_printf("\tGameplay Instructions: \n");
    MacUILib_printf("Press the escape key or space bar to quit.\n\tUse WASD to move.\n");
    MacUILib_printf("Score: %d\n", score);

    MacUILib_printf("Press 'f' to randomly change food postion\n");

    // Debug: Print player postion 
    //objPos playerPos = myPlayer -> getPlayerPos();
    
    //MacUILib_printf("Player [x, y, sym] = [%d, %d, %c]\n", playerPos.pos -> x, playerPos.pos -> y, playerPos.symbol);

    // DON'T THINK THIS IS RIGHT TBH
    if(myGM -> getExitFlagStatus() == true)
    {
        MacUILib_clearScreen();
        MacUILib_printf("The Game is Forcefully Exited\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
    //MacUILib_Delay(myPlayer->playerSpeed()); // control the speed yourself
}


void CleanUp(void)
{
    MacUILib_clearScreen();   
    
    if(myGM -> getLoseFlagStatus() == true)
    {
        MacUILib_printf("\n Thanks for playing! You lost\n");
        MacUILib_printf("Final score was: %d\n", myGM -> getScore());
    }
    else 
    {
        MacUILib_printf("Player has exited the game!\n");
    }

    // Delete items on the heap
    delete myPlayer; 
    delete myGM;

    MacUILib_uninit();
}
