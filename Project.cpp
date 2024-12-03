#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h" 
#include "Player.h"

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

    //Game loop runs until exit flag is set
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

    //create game objects
    myGM = new GameMechs();
    myPlayer = new Player(myGM);

    //Generate food initially  
    myGM->generateFood(myPlayer->getPlayerPosList());

    //Initialize collision to false
    collision = false;
}

void GetInput(void)
{
    //Take in input
    myGM -> getAsyncInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir(); //update player direction
    myPlayer->movePlayer();  //move player
    myPlayer -> selfCollisionCheck(); //check for self-collision

    collision = myPlayer -> selfCollisionCheck();

    //If collision occurs, end the game
    if(collision == true)
    {
        myGM -> setLoseFlag();
        myGM -> setExitTrue();
    }
}


void DrawScreen(void)
{
    MacUILib_clearScreen();    //clear screen

    // GET BOARDSIZE
    int boardX = myGM -> getBoardSizeX();
    int boardY = myGM -> getBoardSizeY();
    
    // GET SCORE
    int score = myGM -> getScore();

    // // GET FOOD POSITION
    objPos foodPos = myGM -> getFoodPos();

    //Print Board
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
                        MacUILib_printf("%c", playerBody.symbol); //print snakecharacter
                        playerPrinted = true;
                        break;
                    }
                }

                // Check if the current position is occupied by the food
                if (!playerPrinted)
                {
                    
                    if (foodPos.pos->x == y && foodPos.pos->y == x) //checks food x and y coords
                    {
                        MacUILib_printf("%c", foodPos.symbol); //print food symbols
                    }
                    else
                    {
                        //print empty space
                        MacUILib_printf("%c", ' ');
                    }
                }
            }
        }
        MacUILib_printf("%c", '\n');
    }

    // PRINT STATEMENTS FOR GAME PLAY
    MacUILib_printf("\tGameplay Instructions: \n");
    MacUILib_printf("Press the escape key or space bar to quit.\nUse WASD to move.\n");
    MacUILib_printf("Score: %d\n", score);  
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();   //clear screen

    // Display end game message based on outcome
    if(myGM -> getLoseFlagStatus() == true)
    {
        //Message when user self collides
        MacUILib_printf("Thanks for playing! You lost\n");
        MacUILib_printf("Final core was: %d\n", myGM -> getScore());
    }
    else 
    {
        //Message when user manually exits
        MacUILib_printf("Player Exited the Game!\n");
    }

    // Delete items on the heap
    delete myPlayer; 
    delete myGM;

    MacUILib_uninit(); //Uninitialize UI library
}
