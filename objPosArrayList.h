#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200 //max capacity of array

#include "objPos.h"
 
class objPosArrayList
{
    private:
        objPos* aList; //pointer to dynamic array of objPos elements
        int listSize;  //current number of elements in list
        int arrayCapacity;  //max capcity of the list

    public:
        objPosArrayList();  // Default constructor
        ~objPosArrayList(); // Destructor

        objPosArrayList(const objPosArrayList &sList);            // copy constructor
        objPosArrayList& operator=(const objPosArrayList &sList); // copy assignment operator

        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void insertTails(int num);
        void removeHead();
        void removeTail();

        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;
        void removeElement(int index);
};

#endif