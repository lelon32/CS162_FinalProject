/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the a dead character npc that 
 * the player can interact with. The class just contains dummy 
 * specifications. This class is derived from the Character class.
 * *********************************************************************/
#include "dead.hpp"

/***********************************************************************
 * ** Description: This default constructor is empty. It is good
 * practice to have a default constructor.
 * *********************************************************************/
DeadGuy::DeadGuy()
{
    //empty.
}

/***********************************************************************
 * ** Description: This constructor initializes member variables of the
 * class.
 *
 * Parameter: unsigned row & column - represents the coordinates of the
 * player.
 * *********************************************************************/
DeadGuy::DeadGuy(unsigned row, unsigned column) : Character(row, column)
{
    attackDiceMax = 0,
    attackDiceNumber = 0,
    defenseDiceMax = 0,
    defenseDiceNumber = 0,
    armor = 0,
    hitPoints = 0;
    mobType = NONE;
    dead = true;

    moveNumber = 0;
    identity = "a person"; 
}

/***********************************************************************
 * ** Description: This destructor is empty. This is good practice to
 * create a virtual destructor for polymorphic behavior.
 * *********************************************************************/
DeadGuy::~DeadGuy()
{
    //empty.
}
