#include "objPos.h"

objPos::objPos()
{
    pos = new Pos; // Allocate memory for position
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
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

// Copy Contructor 
objPos::objPos( const objPos &thisPos)
{
    //do a deep copy here 
    
    pos = new Pos;      //allocated memory
    pos->x = thisPos.pos->x;
    pos->y = thisPos.pos->y;
    symbol = thisPos.symbol;
}

// Copy Assignment Operator 
objPos& objPos::operator=(const objPos &thisPos)
{
    if(this != &thisPos)
    {
        //Allocate memory 
        pos = new Pos;
        pos->x = thisPos.pos->x;
        pos->y = thisPos.pos->y;
        symbol = thisPos.symbol;
    }
    return *this;
}

// Destructor 
objPos::~objPos()
{
    delete pos;     //clean any dynamically allocated memory 
}

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
