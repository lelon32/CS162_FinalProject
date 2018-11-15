/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents a door space. It is looked
 * unless the player has a key. 
 * *********************************************************************/
#include "door.hpp"

/***********************************************************************
 * ** Description: This constructor initializes the member variables of
 * the class.
 * *********************************************************************/
Door::Door()
{
    type = DOOR;       
    spaceName = "Door";
    item = nullptr;
}

/***********************************************************************
 * ** Description: This destructor is empty. This is good practice to
 * create a virtual destructor for polymorphic behavior.
 * *********************************************************************/
Door::~Door()
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
void Door::interact()
{
    cout << "\nA old door.";
}
