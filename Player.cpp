#include "Player.h"
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerDir = STOP;

    // more actions to be included

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
  
    char input = mainGameMechsRef -> getInput();
    
    // Debug:
    MacUILib_printf("Debug: Input in updatePlayerDir: %c\n", input); 

    // PPA3 input processing logic    

    if(mainGameMechsRef -> getInput() != 0) //if not null char
    {
        switch(input)
            {  
                case 'W': // UP
                case 'w':
                    if(playerDir == LEFT || playerDir == RIGHT) 
                    {
                        playerDir = UP;   
                    }
                    break;

                case 'A': // LEFT
                case 'a':
                    if(playerDir == UP || playerDir == DOWN) 
                    {
                        playerDir = LEFT;     
                    }
                    break;
            
                case 'S': // DOWN 
                case 's':
                    if(playerDir == LEFT || playerDir == RIGHT) 
                    {
                        playerDir = DOWN; 
                    }
                    break;

                case 'D': // RIGHT
                case 'd':
                    if(playerDir == UP || playerDir == DOWN) 
                    {
                        playerDir = RIGHT;     
                    }
                    break;
            // EXIT
            //keep this HERE or not??
                case ' ':   // Exit if space bar is pressed
                case 27:    // Exit if ESC is pressed
                    mainGameMechsRef -> setExitTrue();
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
    
    MacUILib_printf("Debug: New Player Position: [x: %d, y: %d]\n", playerPos.pos->x, playerPos.pos->y);

}

// More methods to be added

