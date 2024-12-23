 
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
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // Player direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList *getPlayerPosList() const; // Upgraded 
        void updatePlayerDir();
        void movePlayer();

        bool selfCollisionCheck();

    private:

        objPosArrayList* playerPosList; //upgraded
        enum Dir playerDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif