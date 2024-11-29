#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerDir = STOP;

    // more actions to be included
    playerPos.pos->x = mainGameMechsRef -> getBoardSizeX() / 2;
    playerPos.pos->y = mainGameMechsRef -> getBoardSizeY() /2;
    playerPos.symbol = '@';
}


Player::~Player()
{
    // delete any heap members here
    // no keyword 'new' in the constructor 
    // leave destructor empty FOR NOW 
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
    
    // PPA3 input processing logic    
    
    switch(input)
        {                      
            case 'W': //want to move up 
            case 'w':
                if(playerDir == LEFT || playerDir == RIGHT) 
                {
                    playerDir = UP;     // Change direction to UP, if possible
                }
                break;

            case 'A': //want to move left
            case 'a':
                if(playerDir == UP || playerDir == DOWN) 
                {
                    playerDir = LEFT;     // Change direction to LEFT, if possible
                }
                break;
            
            case 'S': //want to move down 
            case 's':
                if(playerDir == LEFT || playerDir == RIGHT) 
                {
                    playerDir = DOWN;     // Change direction to DOWN, if possible
                }
                break;

            case 'D': //want to move right
            case 'd':
                if(playerDir == UP || playerDir == DOWN) 
                {
                    playerDir = RIGHT;     // Change direction to RIGHT, if possible
                }
                break;

            default:
                break;
        }       
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    //shorten access:
    int board_X = mainGameMechsRef->getBoardSizeX();
    int board_Y = mainGameMechsRef->getBoardSizeY();


        switch (playerDir) 
        {
           case UP:
                playerPos.pos->y--;
                break;
            case DOWN:
                playerPos.pos->y++;
                break;
            case LEFT:
                playerPos.pos->x--;
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
    if (playerPos.pos->y > (board_X - 1)) playerPos.pos->y = 0;

}

// More methods to be added