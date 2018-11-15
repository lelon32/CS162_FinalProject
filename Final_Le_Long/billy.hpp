/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the bandit king, "Billy the
 * Bandit" mob that will fight the player. The class just contains the 
 * enemy specifications for battle.
 * *********************************************************************/
#ifndef BILLY_HPP 
#define BILLY_HPP 

#include "character.hpp"

class Billy: public Character
{
    private:

    public:
    Billy();
    Billy(unsigned, unsigned);
    virtual ~Billy();
};

#endif
