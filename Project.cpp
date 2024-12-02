
#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h" 
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; //Global pointer meant to instantiate a player object on the heap
GameMechs *myGM; // Container class (on the heap)


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
    myPlayer = new Player(myGM);

    // first call the foodGeneration function to initially populate it
    myGM->generateFood(myPlayer->getPlayerPos());
    //should i be doing this as, it sets it to a random position,
        //but it doesn't start off screen? 
        //should it be tooggled by a button??

}

void GetInput(void)
{
    myGM -> getAsyncInput();

    // works !
    // Debug feature: Regenerate food when 'f' is pressed
    if (myGM->getInput() == 'f') {
        MacUILib_printf("Debug: Food regeneration triggered.\n");
        myGM->generateFood(myPlayer->getPlayerPos());
        myGM->clearInput(); // Clear input after processing
    }
}

void RunLogic(void)
{
    //char input = myGM->getInput();
    //MacUILib_printf("Debug: Input in RunLogic: %c", input);

    myPlayer->updatePlayerDir();
    myPlayer->movePlayer(); 

    //following logic in player file for speed
    //myPlayer->playerSpeed(); 
    
    // Adjust player speed
    //these still aren't working, but can ignore for now
    // if (input == '+') {
    //     myGM->increaseSpeed();
    //     MacUILib_printf("Debug: Player speed increased to %d.\n", myGM->getPlayerSpeed());
    // } else if (input == '-') {
    //     myGM->decreaseSpeed();
    //     MacUILib_printf("Debug: Player speed decreased to %d.\n", myGM->getPlayerSpeed());
    // }
    
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
    objPos playerPos = myPlayer->getPlayerPos();

    int playerx = playerPos.pos -> x;
    int playery = playerPos.pos -> y;

    // GET FOOD POSITION
    objPos foodPos = myGM -> getFoodPos();

    // PRINT
    for (int i = 0; i < boardY; i++)
    {
        for (int j = 0; j < boardX; j++)
        {
            if (i == 0 || i == (boardY - 1))
            { 
                // Top/Bottom borders
                MacUILib_printf("%c",'#');
            } 
            else if (j == 0 || j == (boardX - 1))
            { 
                // Side borders
                MacUILib_printf("%c",'#');
            } 
            else if(i == playery && j == playerx)
            {
                // Print Player symbol on board
                MacUILib_printf("%c", playerPos.symbol); 
            } 
            //else if(i == foodPos.pos -> x && j == foodPos.pos -> y)
            else if (i == foodPos.pos->y && j == foodPos.pos->x)
            {  
                // Draw the food char where food coord are
                // also he has i == foodPos.pos -> y idk why 
                MacUILib_printf("%c", foodPos.symbol);
            }
            else
            {
                MacUILib_printf("%c",' ') ;
            }
        }
        MacUILib_printf("%c",'\n');
    }


    // PRINT STATEMENTS FOR GAME PLAY
    MacUILib_printf("\tGameplay Instructions: \n");
    MacUILib_printf("Press the escape key or space bar to quit.\n\tUse WASD to move.\n");
    MacUILib_printf("Score: %d\n", score);

    MacUILib_printf("Press 'f' to randomly change food postion\n");

    // Debug: Print player postion 
    //objPos playerPos = myPlayer -> getPlayerPos();
    MacUILib_printf("Player [x, y, sym] = [%d, %d, %c]\n", playerPos.pos -> x, playerPos.pos -> y, playerPos.symbol);

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
        MacUILib_printf("\n Thanks for playing!\n");
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
