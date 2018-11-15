/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the bandit mob that the player
 * will fight. The class just contains the enemy specifications for
 * battle. This class is derived from the Character class.
 * *********************************************************************/
#ifndef BANDIT_HPP 
#define BANDIT_HPP 

#include "character.hpp"

class Bandit: public Character
{
    private:
    static unsigned banditCount;

    public:
    Bandit();
    Bandit(unsigned, unsigned);
    virtual ~Bandit();
};

#endif
