/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the bandit king, "Billy the
 * Bandit" mob that will fight the player. The class just contains the 
 * enemy specifications for battle.
 * *********************************************************************/
#include "billy.hpp"

/***********************************************************************
 * ** Description: This default constructor is empty. It is good
 * practice to have a default constructor.
 * *********************************************************************/
Billy::Billy()
{
    //empty.
}

/***********************************************************************
 * ** Description: This constructor initializes the mob's battle
 * specifications.
 *
 * Parameter: unsigned row & column - represents the coordinates of the
 * mob.
 * *********************************************************************/
Billy::Billy(unsigned row, unsigned column) : Character(row, column)
{
    attackDiceMax = 3,
    attackDiceNumber = 2,
    defenseDiceMax = 3,
    defenseDiceNumber = 2,
    armor = 0,
    hitPoints = 8;
    mobType = BANDIT_KING;

    moveNumber = 5;
    identity = "Billy the Bandit"; 
}

/***********************************************************************
 * ** Description: This destructor is empty. This is good practice to
 * create a virtual destructor for polymorphic behavior.
 * *********************************************************************/
Billy::~Billy()
{
    //empty.
}
