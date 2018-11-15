/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the goblin mob that the player
 * will fight. The class just contains the enemy specifications for
 * battle. This class is derived from the Character class.
 * *********************************************************************/
#ifndef GOBLIN_HPP 
#define GOBLIN_HPP 

#include "character.hpp"

class Goblin: public Character
{
    private:
    static unsigned goblinCount;

    public:
    Goblin();
    Goblin(unsigned, unsigned);
    virtual ~Goblin();
};

#endif
