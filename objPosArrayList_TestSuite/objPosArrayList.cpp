#include "objPosArrayList.h"

#include <iostream>
using namespace std;

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0;                   // no data at fist in the list
    arrayCapacity = ARRAY_MAX_CAP;  //200 by max size
    aList = new objPos[arrayCapacity]; //created a 200-int array on the Heap
}

// don't know if you should be doing copy assingment and copy constructor here
//if yes:

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

// Copy Assignment Operator (R6M4 3/4)
objPosArrayList& objPosArrayList::operator=(const objPosArrayList &sList)
{
    if(this != &sList)  // Avoid self assignment
    {
        this->listSize = sList.listSize;
        this->arrayCapacity = sList.arrayCapacity;

        // Do deep copy    
        for(int i = 0; i < this->listSize; i++)
        {
            this->aList[i] = sList.aList[i];
        }

    }
    return *this;
    // this-> ensures that no implicit copied instance is created, which leads to memory inefficiency
}
// again don't know if I'm supposed to be doing the above two 
//or if they are supposed to be passed by ref??

objPosArrayList::~objPosArrayList()
{
    delete[] aList;     // Deallocating Heap space
}

int objPosArrayList::getSize() const
{
    return listSize;
}

// Insert
void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        cout << "Array is Full!" << endl;
        return;
    }

    // Shifting/Pushing all elements back by one slot
    // Overwriting the value in i+1 position with that in i position
    for(int i=listSize; i>0; i--)
    {
        aList[i] = aList[i-1]; // Shifting all elements towards the tail to create space at the head
    }
    // aList[0] is ready to be OVERWRITTEN by incoming value

    aList[0] = thisPos; // Inserting the element at the head, index: 0
        //don't know if this is right, cause origninally it's aList[0] = element;
    listSize++;     // Increase the size of the List by one
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        cout << "Array is Full!" << endl;
        return;
    }

    aList[listSize] = thisPos;  // Inserting the element at the tail, index: sizeList
    listSize++;  
}

void objPosArrayList::removeHead()
{
    if(listSize == 0)
    {
        cout << "list is empty, no removal is allowed!!" << endl;
        return;
    }
    
    for(int i = 0; i < listSize-1; i++)
    {
        aList[i] = aList[i+1];
    }
    listSize--; // Decrease the size of the list by one
                // Lazy delete
}

void objPosArrayList::removeTail()
{
    if(listSize == 0)
    {
        cout << "list is empty, no removal is allowed!!" << endl;
        return;
    }

    listSize--; // Lazy delete
    
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
    if(index < 0 || index >= listSize)
    {
        cout<< "You've supplied an invalid index." << endl;
        //prints this like 200 times lmao
        return objPos();
    }

    return aList[index];
}

// EVERYTHING RUNS AND PASSES
// HAVE NOT DONE EXTRA TEST CASES
// PRETTY SURE I'M NOT SUPPOSED TO HAVE COPIED ALL THE ELEMENTS BUT IDK