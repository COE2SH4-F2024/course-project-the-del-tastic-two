#include "GameMechs.h"
#include "MacUILib.h"

#include "Player.h"
#include "objPos.h"

#include "objPosArrayList.h"

GameMechs::GameMechs()
{

    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;

    food.pos = new Pos(); // In GameMechs constructor

    food.setObjPos(-10, -10, 'o'); 
    //initialize food object outside of the game board 

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

GameMechs::~GameMechs()
{
    delete food.pos;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    
char GameMechs::getInput()
{
    return input; 
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true; 
    //if true, player has lost the game
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
    //manually setting the input if necessary
}

void GameMechs::clearInput()
{
    input = 0;
    //reset the input to null
}

// More methods should be added here

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
