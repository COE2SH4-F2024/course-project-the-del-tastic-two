#include "objPos.h"


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

// start of rule of six/min four: 

// Copy Contructor 
objPos::objPos( const objPos &obj)
{ 
    pos = new Pos;      //allocated memory
    pos->x = obj.pos->x;
    pos->y = obj.pos->y;
    symbol = obj.symbol;
}

// Copy Assignment Operator 
objPos& objPos::operator=(const objPos &other)
{
    if(this != &other)
    {
        pos = new Pos;
        pos->x = other.pos->x;
        pos->y = other.pos->y;
        symbol = other.symbol;
    }
    return *this;
}

// Destructor 
objPos::~objPos()
{
    delete pos;     //clean any dynamically allocated memory 
}
// end of rule of six/min four

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
