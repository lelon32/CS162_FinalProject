/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class is an abstract base class for the types of
 * spaces that exists in the game. Each space allows the player to
 * interact with it differently. The Tree and Water spaces have a 1/5
 * chance of containing an item to loot. The Ground spaces can be walked 
 * on. The Rock spaces serve to be a wall. The Campfire space warms the
 * player up.
 * *********************************************************************/
#include "space.hpp"

/***********************************************************************
 * ** Description: This default constructor initializes member variables 
 * of the class.
 * *********************************************************************/
Space::Space()
{
    occupied = false;
    up = nullptr;
    down = nullptr;
    left = nullptr;
    right = nullptr;

}

/***********************************************************************
 * ** Description: This destructor cleans up memory made in heap before 
 * the item object is destroyed.
 * *********************************************************************/
Space::~Space()
{
    //Checks to see if the space contains an item.
    //If so, then delete that item.
    if(item != nullptr)
    {
        delete item;
        item = nullptr;
    }
}

/***********************************************************************
 * ** Description: This function is used to connect the spaces together.
 *
 * Parameters: 
 * 1. Directions - an enumerated data type that represents the
 * direction that the space will connect with.
 * 2. Space* - The space that the space pointer will connect to.
 *
 * Return: void.
 * *********************************************************************/
void Space::connectSpaces(Directions direction, Space* connect)
{
    switch(direction) 
    {
        case UP:
            up = connect;
            break;

        case DOWN:
            down = connect;
            break;

        case LEFT:
            left = connect;
            break;

        case RIGHT:
            right = connect;
            break;
    }
}

/***********************************************************************
 * ** Description: This function allows Space pointers to traverse the
 * room. 
 *
 * Parameters: Directions - an enumerated data type that represents the
 * direction that the Space pointer needs to traverse. 
 *
 * Return: Space* - returns the pointer which represents the direction the
 * Space pointer will assume.
 * *********************************************************************/
Space* Space::traverse(Directions move)
{
    Space* tempDirection;

    switch(move)
    {
        case UP:
            tempDirection = up;
            break;

        case DOWN:
            tempDirection = down;
            break;

        case LEFT:
            tempDirection = left;
            break;

        case RIGHT:
            tempDirection = right;
            break;
    }
    
    return tempDirection;
}

Item* Space::loot()
{
    return item;
}

void Space::setItemNullLoot()
{
    item = nullptr; 
}

void Space::setOccupied(bool occupied)
{
    this->occupied = occupied; 
}

bool Space::getOccupied()
{
    return occupied;
}

SpaceType Space::getSpaceType()
{
    return type;
}

string Space::getSpaceName() const
{
    return spaceName;
}
