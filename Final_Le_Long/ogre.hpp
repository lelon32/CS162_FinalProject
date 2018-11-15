/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the ogre mob that the player
 * will fight. The class just contains the enemy specifications for
 * battle. This class is derived from the Character class.
 * *********************************************************************/
#ifndef OGRE_HPP 
#define OGRE_HPP 

#include "character.hpp"

class Ogre: public Character
{
    private:
    static unsigned ogreCount;

    public:
    Ogre();
    Ogre(unsigned, unsigned);
    virtual ~Ogre();
};

#endif
