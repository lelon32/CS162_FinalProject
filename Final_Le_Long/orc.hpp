/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the orc mob that the player
 * will fight. The class just contains the enemy specifications for
 * battle. This class is derived from the Character class.
 * *********************************************************************/
#ifndef ORC_HPP 
#define ORC_HPP 

#include "character.hpp"

class Orc: public Character
{
    private:
    static unsigned orcCount;

    public:
    Orc();
    Orc(unsigned, unsigned);
    virtual ~Orc();
};

#endif
