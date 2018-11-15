/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Date:
 * ** Description: This class is derived from the Space class. It
 * represents the ground and can be walked on by the player, NPCs, or
 * mobs. 
 * *********************************************************************/
#include "ground.hpp"

/***********************************************************************
 * ** Description: This constructor initializes the member variables of
 * the class.
 * *********************************************************************/
Ground::Ground()
{
    type = GROUND;
    spaceName = "Ground";
    item = nullptr;
}

/***********************************************************************
 * ** Description: This destructor is empty. This is good practice to
 * create a virtual destructor for polymorphic behavior.
 * *********************************************************************/
Ground::~Ground()
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
void Ground::interact()
{
    cout << "\nYou searched the ground but found nothing..."; 
}
