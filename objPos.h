#ifndef OBJPOS_H
#define OBJPOS_H

// Not really a C++ thing
typedef struct 
{
    int x;
    int y;
} Pos;

class objPos
{
    public:
        Pos* pos;      //pointer on the heap  
        char symbol;

        //default constructor:
        objPos();
        //specialized constructor:
        objPos(int xPos, int yPos, char sym);
        
        // Respect the rule of six / minimum four
        // [TODO] Implement the missing special member functions to meet the minimum four rule


        objPos( const objPos &thisPos);             //copy constructor
        objPos& operator=(const objPos& thisPos);   //copy assignment operator 
        ~objPos();                                  //destrucor

        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  

        objPos getObjPos() const;
        char getSymbol() const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
        
        bool isPosEqual(const objPos* refPos) const;
};

#endif