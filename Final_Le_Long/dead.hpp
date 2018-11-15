/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the a dead character npc that 
 * the player can interact with. The class just contains dummy 
 * specifications. This class is derived from the Character class.
 * *********************************************************************/
#ifndef DEAD_HPP 
#define DEAD_HPP 

#include "character.hpp"

class DeadGuy: public Character
{
    private:

    public:
    DeadGuy();
    DeadGuy(unsigned, unsigned);
    virtual ~DeadGuy();
};

#endif
