#include "objPosArrayList.h"

//Constructor
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

    //allocate memory
    aList = new objPos[ARRAY_MAX_CAP];

    //Deep copy
    for (int i=0; i<listSize; i++)
    {
        aList[i] = sList.aList[i]; //copy each element from source
    }
}

// Copy Assignment Operator (3/4)
objPosArrayList& objPosArrayList::operator=(const objPosArrayList &sList)
{
    if(this != &sList)  // Avoid self assignment
    {
        this->listSize = sList.listSize;
        this->arrayCapacity = sList.arrayCapacity;

        //allocate memory
        aList = new objPos[arrayCapacity];

        // Do deep copy    
        for(int i = 0; i < this->listSize; i++)
        {
            this->aList[i] = sList.aList[i]; //copy element from the source
        }

    }
    return *this; //return updated list
}

// Destructor
objPosArrayList::~objPosArrayList()
{
    delete[] aList;     // Deallocating Heap space
    aList = nullptr;
}

//Returns size of the list
int objPosArrayList::getSize() const
{
    return listSize;
}

// Insert new element at the head of list
void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize < arrayCapacity)
    {
        listSize++;

        //shift elements right to make space
        for(int i = listSize -1 ; i > 0; i --)
        {
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos; //insert
    }
}

//Insert new element at tail of the list
void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize < arrayCapacity)
    {
        aList[listSize] = thisPos; //insert element
        listSize++; //insert list size
    }
}

//insert element at tail
void objPosArrayList::insertTails(int num)
{
    if(listSize < arrayCapacity) //check space for new element
    {
        listSize = listSize + num;//increase list size
    }
}

//Remove element from head of list
void objPosArrayList::removeHead()
{
    if(listSize >= 1) //Ensure there are elements in the list
    {
        //Shift elements left
        for(int i =0; i < listSize -1; i++)
        {
            aList[i] = aList[i + 1];
        }
        listSize--; ///decrease list size
    }
}

//Remove element at the tail
void objPosArrayList::removeTail()
{
    //Ensure there are elements in the list
    if(listSize >= 1)
    {
        aList[listSize - 1] = objPos();
        listSize--;
    }
}

//Get element at the head of list
objPos objPosArrayList::getHeadElement() const
{
    return aList[0]; //return first element
}

//get tail element
objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

//get element at the tail
objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}

//get element at specific index
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
