/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents a rock space. The player can
 * interact with this space to see a description. This space is 
 * primarily used as decor and as a wall.
 * *********************************************************************/
#include "rock.hpp"

/***********************************************************************
 * ** Description: This constructor initializes the member variables of
 * the class.
 * *********************************************************************/
Rock::Rock()
{
    type = ROCK;       
    spaceName = "Rock";
    item = nullptr;
}

/***********************************************************************
 * ** Description: This destructor is empty. This is good practice to
 * create a virtual destructor for polymorphic behavior.
 * *********************************************************************/
Rock::~Rock()
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
void Rock::interact()
{
    cout << "\nSome rather large rocks.";
}
