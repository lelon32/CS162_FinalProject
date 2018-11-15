/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the orc mob that the player
 * will fight. The class just contains the enemy specifications for
 * battle. This class is derived from the Character class.
 * *********************************************************************/
#include "orc.hpp"

unsigned Orc::orcCount = 0;

/***********************************************************************
 * ** Description: This default constructor is empty. It is good
 * practice to have a default constructor.
 * *********************************************************************/
Orc::Orc()
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
Orc::Orc(unsigned row, unsigned column) : Character(row, column)
{
    attackDiceMax = 6,
    attackDiceNumber = 2,
    defenseDiceMax = 4,
    defenseDiceNumber = 2,
    armor = 0,
    hitPoints = 8;
    mobType = ORC;

    moveNumber = 3;
    identity = "Orc " + to_string(++orcCount);
}

/***********************************************************************
 * ** Description: This destructor is empty. This is good practice to
 * create a virtual destructor for polymorphic behavior.
 * *********************************************************************/
Orc::~Orc()
{
    //empty.
}
