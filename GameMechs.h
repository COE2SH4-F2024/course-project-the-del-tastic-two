#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;

        objPos food;
        objPos player; //added 
    
    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // is this one needed at all? Why or why not?

            //should be needed if we assign new to any, or alloacate to the heap
            //if not, a default constructor is called
            //or if we need to adhere to the rule of six, minimum four
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        void incrementScore();
        
        // More methods should be added here

        void getAsyncInput();
        //void generateFood();

        // Method 1 (above and beyond approach NOT taken)

        void generateFood(objPosArrayList *blockOff);
        //don't want to create food where player object is

        objPos getFoodPos() const;  //getter
                                    //will return objPos type

};

#endif