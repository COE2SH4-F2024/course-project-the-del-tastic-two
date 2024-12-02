#include "objPos.h"

//potentially delete this
#include <iostream> 
using namespace std; //do i need this 

objPos::objPos()
{
    pos = new Pos; // Allocate memory for position
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL

    //memory allocation to pointer pos, struct on the heap
    //arrow pointer to access x and y 
}

objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule

// start of my work: 

// Copy Contructor 
objPos::objPos( const objPos &thisPos)
{
    //do a deep copy here 

    // this->pos = new Pos;
    // this->pos->x = obj.pos->x;
    // this->pos->y = obj.pos->y;
    // this->symbol = obj.symbol;
    
    pos = new Pos;      //allocated memory
    pos->x = thisPos.pos->x;
    pos->y = thisPos.pos->y;
    symbol = thisPos.symbol;
}

// Copy Assignment Operator 
objPos& objPos::operator=(const objPos &thisPos)
{
    // if (this == &other) // Self-assignment check
    // {
    //     return *this; // Avoid unnecessary work
    // }

    // if (pos != nullptr) 
    //     delete pos; // Free existing memory if allocated

    // // Allocate new resources and copy data from `other`
    // pos = new Pos(*other.pos); // Use copy constructor of `Pos`
    // symbol = other.symbol; // Directly copy the symbol field

    if(this != &thisPos)
    {
        pos = new Pos;
        pos->x = thisPos.pos->x;
        pos->y = thisPos.pos->y;
        symbol = thisPos.symbol;
        // check if this new version works
    }
    return *this;
}

// Destructor 
objPos::~objPos()
{
    delete pos;     //clean any dynamically allocated memory 
}

// end of my work for rule of six/min four 

void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
