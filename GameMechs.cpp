#include "GameMechs.h"
#include "MacUILib.h"

#include "Player.h"
#include "objPos.h"

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

    //ignore these also
    maxSpeed = 5;
    minSpeed = 1; 
    playerSpeed = 3;

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    // exitFlag = false;
    // loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    // nothing on the heap
    // destructor can stay empty for now!

    delete food.pos;

}

// should i be doing a copy constructor and a copy assignment operator?

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
    //potentially increase by more than one if special char reached?
    //if _(char = some specific char)_ then score += 5 or something
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
    //don't know what happened here tbh
    // if(input == '\0')
    // {
    //     setExitTrue();
    // }

}

// FOOD GENERATION

void GameMechs::generateFood(objPos blockOff)
{
    // You only need to block off the layer position FOR NOW
    // Easier for now, but will need to be upgraded in iteration 3
    // Because you need to account for the snake, 
        //so multiple spots in the board

    // Seed random generator 
    srand(time(NULL));

    // Keep generating until get a valid position
    while (true)
    {
        // Generate random x and y within the valid range (excluding borders)
        int xCandidate = (rand() % (boardSizeX - 2)) + 1; // From 1 to boardSizeX - 2
        int yCandidate = (rand() % (boardSizeY - 2)) + 1; // From 1 to boardSizeY - 2

        // Check if generated postion is same as player position
        if (xCandidate == blockOff.pos->x && yCandidate == blockOff.pos->y)
        {
            continue; // If yes, skip this postion and try again
        }

        // Set the food's position and symbol
        food.pos->x = xCandidate;
        food.pos->y = yCandidate;
        food.symbol = 'o'; // Chosen symbol for food

        // DO I NEED TO RANDOMLY GENERATE THE SYMBOL AS WELL??

        break;
    }
}

objPos GameMechs::getFoodPos() const
{
    return food;
} 


// __________________________________________________



// FOR ATTEMPT INITIAL, OTHERWISE IGNORE
// void GameMechs::generateFood()
// {
//     food.pos -> x = rand() % (boardSizeX -2) + 1;
//     food.pos -> y = rand() % (boardSizeY -2) + 1;
//     food.symbol = '*';
// }



//add methods to set/get the speed
// CONSIDER MOVING TO PLAYER.CPP INSTEAD!!

// int GameMechs::getMaxSpeed() const
// {
//     return maxSpeed;
// }
// int GameMechs::getMinSpeed() const
// {
//     return minSpeed;
// }
// int GameMechs::getPlayerSpeed() const
// {
//     return playerSpeed;
// }

// void GameMechs::increaseSpeed()
// {
//     if(playerSpeed > minSpeed || playerSpeed < maxSpeed)
//     {
//         playerSpeed++;
//         MacUILib_printf("Player Speed was increased to: %d", playerSpeed);
//     }
// }

// void GameMechs::decreaseSpeed()
// {
//     if(playerSpeed > minSpeed || playerSpeed < maxSpeed)
//     {
//         playerSpeed--;
//         MacUILib_printf("Player Speed was increased to: %d", playerSpeed);
//     }
// }