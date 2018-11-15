/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the ogre mob that the player
 * will fight. The class just contains the enemy specifications for
 * battle. This class is derived from the Character class.
 * *********************************************************************/
#include "ogre.hpp"

unsigned Ogre::ogreCount = 0;

/***********************************************************************
 * ** Description: This default constructor is empty. It is good
 * practice to have a default constructor.
 * *********************************************************************/
Ogre::Ogre()
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
Ogre::Ogre(unsigned row, unsigned column) : Character(row, column)
{
    attackDiceMax = 6,
    attackDiceNumber = 2,
    defenseDiceMax = 4,
    defenseDiceNumber = 2,
    armor = 2,
    hitPoints = 7;
    mobType = OGRE;

    moveNumber = 2;
    identity = "Ogre " + to_string(++ogreCount);
}

/***********************************************************************
 * ** Description: This destructor is empty. This is good practice to
 * create a virtual destructor for polymorphic behavior.
 * *********************************************************************/
Ogre::~Ogre()
{
    //empty.
}
