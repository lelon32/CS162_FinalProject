/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents a water space. It has a 1/5
 * chance of containing a medicinal herb which heals the player when
 * used.
 * *********************************************************************/
#include "water.hpp"

/***********************************************************************
 * ** Description: This constructor initializes the member variables of
 * the class.
 *
 * Parameters: None.
 * *********************************************************************/
Water::Water()
{
    type = WATER;       
    spaceName = "Water";

    // 1/5 chance of containing a medicinal herb.
    if(((rand() % 5) + 1) == 1)
    {
        item = new Item(HERB); 
    }

    else
    {
        item = nullptr;
    }
}

/***********************************************************************
 * ** Description: This destructor is empty. This is good practice to
 * create a virtual destructor for polymorphic behavior.
 * *********************************************************************/
Water::~Water()
{
    //empty.
}

/***********************************************************************
 * ** Description: This function allows the player to interact with the
 * space.
 *
 * Parameters: None.
 *
 * Return: void.
 * *********************************************************************/
void Water::interact()
{
    cout << "\nClean, beautiful, glistening water.";
}
