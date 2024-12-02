#include "Player.h"
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "objPosArrayList.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerDir = STOP;

    // more actions to be included

    playerPosList = new objPosArrayList();  

    int board_X = mainGameMechsRef -> getBoardSizeX();
    int board_Y = mainGameMechsRef -> getBoardSizeY();

    playerPosList -> insertHead(objPos(board_X /2, board_Y/2, '*'));

}


Player::~Player()
{
    delete playerPosList;
}

objPosArrayList *Player::getPlayerPosList() const
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    mainGameMechsRef-> clearInput();

    if(input != 0)  // if not null character
    {

        //MacUILib_printf("Input received: %c\n", mainGameMechsRef->getInput());
        switch(input)
        {                      
            case ' ':   // Exit if space bar is pressed
            case 27:    // Exit if ESC is pressed
                mainGameMechsRef->setExitTrue();
                break;
            case 'w': case 'W': // UP
                if(playerDir != DOWN && playerDir != UP)
                {
                    playerDir = UP;
                }
                break;
            case 'a': case 'A': // LEFT
                if(playerDir != RIGHT && playerDir != LEFT)
                {
                    playerDir = LEFT;
                }
                break;
            case 's': case 'S': // DOWN
                if(playerDir != UP && playerDir != DOWN)
                {
                    playerDir = DOWN;
                }
                break;
            case 'd': case 'D': // RIGHT
                if(playerDir != LEFT && playerDir != RIGHT)
                {
                    playerDir = RIGHT;
                }
                break;
                
            default:
                break;
        }
        mainGameMechsRef->clearInput();
    }
}


void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    //shorten access for boundary checking:
    int board_X = mainGameMechsRef->getBoardSizeX();
    int board_Y = mainGameMechsRef->getBoardSizeY();

    objPos newHead = playerPosList -> getHeadElement();

    switch(playerDir)
    {
        case STOP:
            break;
        case UP:
            newHead.pos->y--;
            break;
        case LEFT:
            newHead.pos->x--;
            break;
        case DOWN:
            newHead.pos->y++;
            break;
        case RIGHT:
            newHead.pos->x++;
            break;
    }

    // Border wraparound
    //if the postion reaches a border, switch the postion to the other end
    if (newHead.pos->x < 0) newHead.pos->x = (board_X -1);    // Wrap horizontally
    if (newHead.pos->x > (board_X - 1)) newHead.pos->x = 0;
    if (newHead.pos->y < 0) newHead.pos->y = (board_Y -1);     // Wrap vertically
    if (newHead.pos->y > (board_Y - 1)) newHead.pos->y = 0;
    
    //move snake body around:

    objPos foodPos = mainGameMechsRef->getFoodPos();
        
    if ((newHead.pos->x == foodPos.pos->x) && (newHead.pos->y == foodPos.pos->y))
    {
        // Snake eats food: Add a new head (no tail removal here)
        mainGameMechsRef->generateFood(playerPosList); // Regenerate food
        playerPosList->insertHead(newHead);  // Insert the new head at the front
        mainGameMechsRef->incrementScore();
    }
    else
    {
        // No food eaten: Add the new head and remove the tail
        playerPosList->insertHead(newHead);
        playerPosList->removeTail();
    }

}

// More methods to be added

// void Player::growSnake()
// {
//     //delete this if not used in project.cpp!!


//     objPos foodPos = mainGameMechsRef->getFoodPos();

//     objPos newHead = playerPosList -> getHeadElement();

    
    
//     if ((newHead.pos->x == foodPos.pos->x) && (newHead.pos->y == foodPos.pos->y))
//     {
//         // Snake eats food: Add a new head (no tail removal here)
//         mainGameMechsRef->generateFood(playerPosList); // Regenerate food
//         playerPosList->insertHead(newHead);  // Insert the new head at the front
//         mainGameMechsRef->incrementScore();
//     }
//     else
//     {
//         // No food eaten: Add the new head and remove the tail
//         playerPosList->insertHead(newHead);
//         playerPosList->removeTail();
//     }
// }


bool Player::selfCollisionCheck()
{
    objPos newHead = playerPosList -> getHeadElement();

    for(int i = 1; i < playerPosList-> getSize(); i++)
    {
        objPos limb = playerPosList -> getElement(i);

        if(newHead.pos -> x == limb.pos -> x && newHead.pos ->  y == limb.pos -> y)
        {
            return true;
        }

        
    }
    
    return false;
}
