/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the goblin mob that the player
 * will fight. The class just contains the enemy specifications for
 * battle. This class is derived from the Character class.
 * *********************************************************************/
#include "goblin.hpp"

unsigned Goblin::goblinCount = 0;

/***********************************************************************
 * ** Description: This default constructor is empty. It is good
 * practice to have a default constructor.
 * *********************************************************************/
Goblin::Goblin()
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
Goblin::Goblin(unsigned row, unsigned column) : Character(row, column)
{
    attackDiceMax = 4,
    attackDiceNumber = 2,
    defenseDiceMax = 3,
    defenseDiceNumber = 2,
    armor = 0,
    hitPoints = 6;
    mobType = GOBLIN;

    moveNumber = 4;
    identity = "Goblin " + to_string(++goblinCount);
}

/***********************************************************************
 * ** Description: This destructor is empty. This is good practice to
 * create a virtual destructor for polymorphic behavior.
 * *********************************************************************/
Goblin::~Goblin()
{
    //empty.
}
