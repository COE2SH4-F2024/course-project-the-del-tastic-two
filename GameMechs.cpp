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

    // boardSizeX = 10;
    // boardSizeY = 20;

    boardSizeX = 20;
    boardSizeY = 10;

    maxSpeed = 5;
    minSpeed = 1; 
    playerSpeed = 3;

    //ignore for now:
    // itemList = nullptr;
    // itemCount = 0;

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    // exitFlag = false;
    // loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;


    // //for random gen:
    // // Initialize the board size
    // this->boardSizeX = boardX;
    // this->boardSizeY = boardY;

    // // Initialize the item list to store generated items
    // this->itemList = new objPos[boardX * boardY];  // Adjust this size as needed
    // this->itemCount = 0;  // Initially, no items are generated

}

// do you need a destructor?
GameMechs::~GameMechs()
{
    // nothing on the heap
    // destructor can stay empty for now!

    //ignore only for the gen function
    // delete[] this->itemList;
    // delete[] itemList;
    //redo to delete contents of list on the heap also
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

//try for input, reference input in project.cpp if still a problem
int GameMechs::getAsyncInput()
{
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
        return input;
    }
}

void GameMechs::generateFood()
{
    food.pos -> x = rand() % (boardSizeX -2) + 1;
    food.pos -> y = rand() % (boardSizeY -2) + 1;
    food.symbol = '*';
}



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






// // this is mine, but geniunely think it's so wrong oml


// objPos* GameMechs::getItemList() const 
// {
//     return itemList;  // Return the pointer to the array of items
// }

// // Getter function to access the itemCount
// int GameMechs::getItemCount() const 
// {
//     return itemCount;  // Return the number of items generated
// }

// //try 2:
// void GameMechs::GenerateItems(struct objPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char* str)
// {

//     int count = 0;
//     int strLength = 0;

//     while (str[strLength] != '\0')
//     {
//         strLength++;
//     }

//     int usedPostions[20][10] = {0};
//     srand(time(NULL));
//     int usedSymbols[128] = {0};

//     // Generate random items
//     while(count < listSize)
//     {
//         int xCandidate = (rand() % (xRange -1)) + 1; 
//         int yCandidate = (rand() % (yRange -1)) + 1; 

//         // Check for collision with player's position
//        if (xCandidate == playerPos->pos->x && yCandidate == playerPos->pos->y)  
//         {
//             continue; // Skip if it collides with player positon
//         }
//         if (usedPostions[xCandidate][yCandidate] == 1) 
//         {
//             continue; // Skip if postion already used
//         }
        
//         // Generate a random char from goal string
//         int indexCan = rand() % strLength;       //rand index to choose from
//         char symbolCandidate = str[indexCan];

//         if (symbolCandidate < 0 || symbolCandidate >= 128 || usedSymbols[symbolCandidate]) 
//         {
//             continue; // Skip if the symbol is out of ASCII range or already used
//         }

//             //update the list with the generated values 
//             list[count].pos -> x = xCandidate;
//             list[count].pos -> y = yCandidate; 
//             list[count].symbol = symbolCandidate;

//             //update used postions and symbols
//             usedPostions[xCandidate][yCandidate] = 1;
//             usedSymbols[symbolCandidate] = 1;

//             count++; 
//             //update count, for successfulled added item
//     }
//     itemCount = count;
// }
