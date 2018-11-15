/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents a campfire space. It warms up 
 * the player when interacted with. This works in conjunction with the
 * program's hypothermia (death) simulater.
 * *********************************************************************/
#include "campfire.hpp"

/***********************************************************************
 * ** Description: This constructor initializes the member variables of
 * the class.
 * *********************************************************************/
Campfire::Campfire()
{
    type = CAMPFIRE;       
    spaceName = "Campfire";
    item = nullptr;
}

/***********************************************************************
 * ** Description: This destructor is empty. This is good practice to
 * create a virtual destructor for polymorphic behavior.
 * *********************************************************************/
Campfire::~Campfire()
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
void Campfire::interact()
{
    cout << "\nThe fire starts to warm you up."; 
}
