#include "GameMechs.h"
#include "MacUILib.h"

#include "Player.h"
#include "objPos.h"

#include "objPosArrayList.h"

//Constructor
GameMechs::GameMechs()
{

    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;

    food.pos = new Pos(); // Initialize food object

    food.setObjPos(-10, -10, 'o'); //initialize food object outside of the game board 
}

// Constructor with custom board size
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// Destructor
GameMechs::~GameMechs()
{
    delete food.pos;
}

// Getter for exit flag status
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

// Getter for lose flag status
bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

// Getter for user input  
char GameMechs::getInput()
{
    return input; 
}

// Getter for current score
int GameMechs::getScore() const
{
    return score;
}

// Increment score by 1
void GameMechs::incrementScore()
{
    score++;
}

// Getter for board width (X)
int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

// Getter for board height (Y)
int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

// Set exit flag to true
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

// Set lose flag to true
void GameMechs::setLoseFlag()
{
    loseFlag = true;  //if true, player has lost the game
}
   

// Manually set input character
void GameMechs::setInput(char this_input)
{
    input = this_input; //manually setting the input if necessary
}

// Clear input
void GameMechs::clearInput()
{
    input = 0;
    //reset the input to null
}

// Asynchronously check and fetch user input
void GameMechs::getAsyncInput()
{   
    if(MacUILib_hasChar() != 0)
    {
        input = MacUILib_getChar();
    }
}

// FOOD GENERATION
void GameMechs::generateFood(objPosArrayList* blockOff)
{
    srand(time(NULL)); // Seed random generator

    while (true)
    {
        // Generate random x and y within the valid range (excluding borders)
        int xCandidate = (rand() % (boardSizeX - 2)) + 1; // From 1 to boardSizeX - 2
        int yCandidate = (rand() % (boardSizeY - 2)) + 1; // From 1 to boardSizeY - 2

        // Check if generated position matches the single blockOff position (head of list)
        objPos blockOffHead = blockOff->getHeadElement();
        if (xCandidate == blockOffHead.pos->x && yCandidate == blockOffHead.pos->y)
        {
            continue; // Skip this position and try again
        }

        // Check if generated position collides with any positions in the blockOff list
        bool isBlocked = false;
        for (int i = 0; i < blockOff->getSize(); i++) // Loop through all positions in blockOff
        {
            objPos playerPos = blockOff->getElement(i);
            if (xCandidate == playerPos.pos->x && yCandidate == playerPos.pos->y)
            {
                isBlocked = true;
                break; // Exit loop early if collision detected
            }
        }

        if (!isBlocked)
        {
            // Set the food's position and symbol
            food.pos->x = xCandidate;
            food.pos->y = yCandidate;
            food.symbol = 'o'; // Chosen symbol for food
            break; // Valid position found, exit loop
        }
    }
}

objPos GameMechs::getFoodPos() const
{
    return food;
} 
