/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents a tree space. It has a 1/5
 * chance of containing an apple which heals the player when used. 
 * *********************************************************************/
#include "tree.hpp"

/***********************************************************************
 * ** Description: This constructor initializes the member variables of
 * the class.
 * *********************************************************************/
Tree::Tree()
{
    type = TREE;       
    spaceName = "Tree";

    // 1/5 chance of containing an apple.
    if(((rand() % 4) + 1) == 1)
    {
        item = new Item(APPLE); 
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
Tree::~Tree()
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
void Tree::interact()
{
    cout << "\nA tall apple tree.";
}
