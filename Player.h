 
 #ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList *getPlayerPosList() const; // Upgraded 
        void updatePlayerDir();
        void movePlayer();

        // More methods to be added here

        void growSnake();

        bool selfCollisionCheck();

        //int currentSpeed;
        //int playerSpeed();

    private:
        //objPos playerPos; // Upgrade this in iteration 3. 

        objPosArrayList* playerPosList; //upgraded
        enum Dir playerDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif