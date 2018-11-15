/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the bandit mob that the player
 * will fight. The class just contains the enemy specifications for
 * battle. This class is derived from the Character class.
 * *********************************************************************/
#include "bandit.hpp"

unsigned Bandit::banditCount = 0;

/***********************************************************************
 * ** Description: This default constructor is empty. It is good
 * practice to have a default constructor.
 * *********************************************************************/
Bandit::Bandit()
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
Bandit::Bandit(unsigned row, unsigned column) : Character(row, column)
{
    attackDiceMax = 6,
    attackDiceNumber = 2,
    defenseDiceMax = 4,
    defenseDiceNumber = 2,
    armor = 2,
    hitPoints = 6;
    mobType = BANDIT;

    moveNumber = 4;
    identity = "Bandit " + to_string(++banditCount);
}

/***********************************************************************
 * ** Description: This destructor is empty. This is good practice to
 * create a virtual destructor for polymorphic behavior.
 * *********************************************************************/
Bandit::~Bandit()
{
    //empty.
}
