#include "Player.h"
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerDir = STOP;

    // more actions to be included

    //currentSpeed = 100000;

    playerPos.pos = new Pos(); // DELETE 

    playerPos.pos->x = (mainGameMechsRef -> getBoardSizeX() / 2);
    playerPos.pos->y = (mainGameMechsRef -> getBoardSizeY() /2);
    playerPos.symbol = '*'; // Initialize symbol
}


Player::~Player()
{
    // delete any heap members here
    // no keyword 'new' in the constructor 
    // leave destructor empty FOR NOW 

    //delete Pos(); dunno about this 
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    
    return playerPos; 

    //return the object playerPos type through value (check or delete comment)
    //only can do this if you've implemented the rule of four
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

//player speed 
// int Player::playerSpeed()
// {
    
//     if(mainGameMechsRef->getInput() != 0)  // if not null character
//     {
//         switch(mainGameMechsRef->getInput())
//         {                      
//             //player speed controller 
//             case '1':
//                 currentSpeed = 1000000;
//                 //outputSpeed = "Very Slow";
//                 break;
//             case '2':
//                 currentSpeed = 500000;
//                 //outputSpeed = "Slow";
//                 break;
//             case '3':
//                 currentSpeed = 100000;
//                 //outputSpeed = "Regular";
//                 break;
//             case '4':
//                 currentSpeed = 10000;
//                 //outputSpeed = "Fast";
//                 break;
//             case '5':
//                 currentSpeed = 2500;
//                 //outputSpeed = "Very Fast";
//                 break;

//             default:
//                 break;
//         }
//         mainGameMechsRef->clearInput();
//     }
// }


void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    //shorten access for boundary checking:
    int board_X = mainGameMechsRef->getBoardSizeX();
    int board_Y = mainGameMechsRef->getBoardSizeY();

    switch(playerDir)
    {
        case STOP:
            break;
        case UP:
            playerPos.pos->y--;
            break;
        case LEFT:
            playerPos.pos->x--;
            break;
        case DOWN:
            playerPos.pos->y++;
            break;
        case RIGHT:
            playerPos.pos->x++;
            break;
    }

    // Border wraparound
    //if the postion reaches a border, switch the postion to the other end
    if (playerPos.pos->x < 0) playerPos.pos->x = (board_X -1);    // Wrap horizontally
    if (playerPos.pos->x > (board_X - 1)) playerPos.pos->x = 0;
    if (playerPos.pos->y < 0) playerPos.pos->y = (board_Y -1);     // Wrap vertically
    if (playerPos.pos->y > (board_Y - 1)) playerPos.pos->y = 0;
    
    //MacUILib_printf("Debug: New Player Position: [x: %d, y: %d]\n", playerPos.pos->x, playerPos.pos->y);

}

// More methods to be added

