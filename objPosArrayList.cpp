#include "objPosArrayList.h"

//#include <iostream>
//using namespace std;

objPosArrayList::objPosArrayList()
{
    listSize = 0;                       // no data at fist in the list
    arrayCapacity = ARRAY_MAX_CAP;      //200 by max size
    aList = new objPos[arrayCapacity];  //created a 200-int array on the Heap
}

// Copy constructor (R6M4 2/4)
objPosArrayList::objPosArrayList(const objPosArrayList &sList)
{
    // DEEP COPY:
    listSize = sList.listSize;
    arrayCapacity = sList.arrayCapacity;

    aList = new objPos[ARRAY_MAX_CAP];

    for (int i=0; i<listSize; i++)
    {
        aList[i] = sList.aList[i];
    }
}

// Copy Assignment Operator (3/4)
objPosArrayList& objPosArrayList::operator=(const objPosArrayList &sList)
{
    if(this != &sList)  // Avoid self assignment
    {
        this->listSize = sList.listSize;
        this->arrayCapacity = sList.arrayCapacity;

        aList = new objPos[arrayCapacity];

        // Do deep copy    
        for(int i = 0; i < this->listSize; i++)
        {
            this->aList[i] = sList.aList[i];
        }

    }
    return *this;
    // this-> ensures that no implicit copied instance is created, which leads to memory inefficiency
}

// Destructor
objPosArrayList::~objPosArrayList()
{
    delete[] aList;     // Deallocating Heap space
    aList = nullptr;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

// Insert
void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize < arrayCapacity)
    {
        listSize++;
        for(int i = listSize -1 ; i > 0; i --)
        {
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos;
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize < arrayCapacity)
    {
        aList[listSize] = thisPos;
        listSize++;
    }
}

void objPosArrayList::insertTails(int num)
{
    if(listSize < arrayCapacity)
    {
        listSize = listSize + num;
    }
}

void objPosArrayList::removeHead()
{
    if(listSize >= 1)
    {
        for(int i =0; i < listSize -1; i++)
        {
            aList[i] = aList[i + 1];
        }
        listSize--;
    }

}

void objPosArrayList::removeTail()
{
    if(listSize >= 1)
    {
        aList[listSize - 1] = objPos();
        listSize--;
    }
    
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}

void objPosArrayList::removeElement(int index)
{
    if(listSize >= 1 && index>= 0 && index < listSize)
    {
        for( int i = index; i < listSize -1; i++)
        {
            aList[i] = aList[i+1];
        }
        listSize--;
    }
}
