/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the Princess npc that the 
 * player can interact with. You win the game by rescuing the princess
 * and interacting with her. The class just contains dummy 
 * specifications. This class is derived from the Character class.
 * *********************************************************************/
#include "princess.hpp"

/***********************************************************************
 * ** Description: This default constructor is empty. It is good
 * practice to have a default constructor.
 * *********************************************************************/
Princess::Princess()
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
Princess::Princess(unsigned row, unsigned column) : Character(row, column)
{
    attackDiceMax = 1,
    attackDiceNumber = 1,
    defenseDiceMax = 1,
    defenseDiceNumber = 1,
    armor = 0,
    hitPoints = 4;
    mobType = PRINCESS;

    moveNumber = 0;
    identity = "Princess"; 
}

/***********************************************************************
 * ** Description: This destructor is empty. This is good practice to
 * create a virtual destructor for polymorphic behavior.
 * *********************************************************************/
Princess::~Princess()
{
    //empty.
}
