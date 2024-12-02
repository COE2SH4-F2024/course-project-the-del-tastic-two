#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"
 
class objPosArrayList
{
    private:
        objPos* aList; // pointer to the start of the array itself that is holding the array list
        int listSize;       //sizeList (from demo)
        int arrayCapacity;  //sizeArray

    public:
        objPosArrayList();  // Default constructor
        ~objPosArrayList(); // Destructor

        //bad idea to copy entire array list, pass by ref instead i think 
        //if we do here:
        objPosArrayList(const objPosArrayList &sList);            // copy constructor
        objPosArrayList& operator=(const objPosArrayList &sList); // copy assignment operator

        //refer to the demo intArrayList
        //should be VERY throughough and 100 right, or will cause a lot of problems
        //do your own test cases
        //then copy them back into the main file

        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        //return by value here (returns a value of type objPos)
        //if the copy assignment operator of the objPos class is right
            //you can just return the value and it'll copy it there
        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;
};

#endif