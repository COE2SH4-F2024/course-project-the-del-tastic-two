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

        int minSpeed;
        int maxSpeed; 
        int playerSpeed;  //for current speed

        //potentially delete these:
        objPos* itemList;  // Array to hold the generated items
        int itemCount;     // Number of items generated
    
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

        int getAsyncInput();
        void generateFood();

        //Change the speed
        // int getMaxSpeed() const;
        // int getMinSpeed() const;
        // int getPlayerSpeed() const;

        // void increaseSpeed();
        // void decreaseSpeed();



        // ATTEMPT TO GEN; OTHERWISE IGNORE: 
        //should i be doing the draw screen stuff here????
        //void generateItems(const char* goalString, int listSize); 
        // Generate random items

        // // Getter functions to access private members
        // objPos* getItemList() const;
        // int getItemCount() const;

        // //try generate:
        // void GenerateItems(struct objPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char* str);

};

#endif