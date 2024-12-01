
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

    //seed random generation (need later)
    //srand(time(0));
}

void GetInput(void)
{
    // if(MacUILib_hasChar() != 0)
    // {
    //     char input = MacUILib_getChar();
    //     MacUILib_printf("Debug: Input recieved in getInput: %c", input);
    //     myGM->setInput(input);
    // }

    //change later to, if this doesn't work 
    myGM -> getAsyncInput();

    // TO TEST, DOESN'T WORK 
    //char input = myGM -> getAsyncInput(); // assuming this method reads input asynchronously

    // if (input != 0) {
    //     // Set the input for game mechanics to process
    //     myGM->setInput(input);  // This could be used in any part of the game logic

    //     // Update the player's direction based on the input
    //     myPlayer->updatePlayerDir();  // Update player direction based on the input

    //     // Handle other game logic, like quitting or special keys
    //     if (input == ' ' || input == 27) {  // Space or ESC for exit
    //         myGM->setExitTrue();
    //     }
    // }

}

void RunLogic(void)
{
    char input = myGM->getInput();
    MacUILib_printf("Debug: Input in RunLogic: %c", input);

    myPlayer->updatePlayerDir();
    myPlayer->movePlayer(); 

    
    // Adjust player speed
    //these still aren't working, but can ignore for now
    // if (input == '+') {
    //     myGM->increaseSpeed();
    //     MacUILib_printf("Debug: Player speed increased to %d.\n", myGM->getPlayerSpeed());
    // } else if (input == '-') {
    //     myGM->decreaseSpeed();
    //     MacUILib_printf("Debug: Player speed decreased to %d.\n", myGM->getPlayerSpeed());
    // }
    
    //myGM -> clearInput(); //DO I NEED THIS HERE OR IN DRAW

    //update player speed here too? or in get input? 

    // logic updated:
    // MacUILib_printf("Debug: Input received '%c' (%d)\n", input, input);
    
    // if(input != 0) //if input isn't null 
    // {
    //     switch(input)
    //     {
    //         case ' ':   // Exit if space bar is pressed
    //         case 27:    // Exit if ESC is pressed
    //             myGM -> setExitTrue();
    //             MacUILib_printf("Debug: Exit triggered\n");
    //             break;

    //         case 'p':
    //             MacUILib_printf("Debug: The score is: %d\n", myGM->getScore());
    //             break; //don't think this is working

    //         //these don't work either 
    //         case 43: // '+'
    //             myGM -> increaseSpeed();
    //             MacUILib_printf("Player speed increased\n");
    //                 //update print statement later
    //             break;
    //         case 45: // '-'
    //             myGM -> decreaseSpeed();
    //             MacUILib_printf("Player speed decreased\n");
    //             break;


    //         //add more cases here for food, score, lose, etc.

    //         default:
    //             break;
        
    //     }
    //     // Clear input after processing
    //     myGM->clearInput();
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
    // int playerX = myPlayer->getPlayerPos().pos->x;
    // int playerY = myPlayer->getPlayerPos().pos->y;

    // GET SYMBOL
    //char playerSymbol = myPlayer->getPlayerPos().symbol;

    // BASIC RUNNING FRAME: MINE
    // for(int i=0; i < boardX; i++) //for 1 less than the amount of ROWS
    // {
    //     for(int j=0; j < boardY; j++) //for 1 less than the amount of COLUMNS
    //     {
    //         //print '#' if in the first or last row, 0 or 9
    //         //print '#' if in the first or last column, 0 or 19
    //         if(i == 0 || i == (boardX -1) || j == 0 || j == (boardY -1))
    //         {
    //             MacUILib_printf("#");
    //         }
    //         // if the postion is the same as the current player position, print the player symbol 

    //         else if(i == playerx && j == playery)
    //         {
    //             MacUILib_printf("%c", playerPos.symbol); // Place player's symbol on the board
    //             MacUILib_printf("A"); //test
    //         } 

    //         else
    //         {
    //             MacUILib_printf(" ");
    //         }
    //     }
    //     MacUILib_printf("\n"); //move to next line
    // }

    // TEST TO WORK FRAME AND PRINT:
    for (int i = 0; i < boardY; i++)
    {
        for (int j = 0; j < boardX; j++)
        {
            if (i == 0 || i == (boardY - 1))
            { 
                // Top/Bottom borders
                MacUILib_printf("#");
            } 
            else if (j == 0 || j == (boardX - 1))
            { 
                // Side borders
                MacUILib_printf("#");
            } 
            else if(i == playery && j == playerx)
            {
                // Print Player symbol on board
                MacUILib_printf("%c", playerPos.symbol); 
            } 
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("%c",'\n');
    }

    if(myGM -> getInput() == 't')
    {
        myGM-> incrementScore();
        MacUILib_printf("The score is: %d\n", score);
    }

    // need to check if score increments 
    // need to check if it matches ppas 

    // PRINT STATEMENTS FOR GAME PLAY
    MacUILib_printf("Press the escape key or space bar to quit.\n Use WASD to move.\n");
    MacUILib_printf("Score: %d\n", score);

    // Debug: Print player postion 
    //objPos playerPos = myPlayer -> getPlayerPos();
    MacUILib_printf("Player [x, y, sym] = [%d, %d, %c]\n", playerPos.pos -> x, playerPos.pos -> y, playerPos.symbol);

    if(myGM -> getExitFlagStatus() == true)
    {
        MacUILib_clearScreen();
        MacUILib_printf("The Game is Forcefully Exited\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
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
        MacUILib_printf("You've exited the game!\n");
    }

    delete myPlayer; 
    delete myGM;

    MacUILib_uninit();
}
