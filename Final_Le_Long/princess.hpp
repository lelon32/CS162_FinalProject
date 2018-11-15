/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the Princess npc that the 
 * player can interact with. You win the game by rescuing the princess
 * and interacting with her. The class just contains dummy 
 * specifications. This class is derived from the Character class.
 * *********************************************************************/
#ifndef PRINCESS_HPP 
#define PRINCESS_HPP 

#include "character.hpp"

class Princess: public Character
{
    private:

    public:
    Princess();
    Princess(unsigned, unsigned);
    virtual ~Princess();
};

#endif
