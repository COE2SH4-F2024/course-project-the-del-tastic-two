#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    //define private
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;

        objPos food;
        objPos player; //added 
    
    //define public
    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // is this one needed at all? Why or why not?
        
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
        

        // Method 1 (above and beyond approach NOT taken)
        void generateFood(objPosArrayList *blockOff);
        objPos getFoodPos() const;  

};

#endif