/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents a rock space. The player can
 * interact with this space to see a description. This space is 
 * primarily used as decor and as a wall.
 * *********************************************************************/
#ifndef ROCK_HPP 
#define ROCK_HPP 

#include "space.hpp"

class Rock : public Space
{
    private:

    public:
    Rock();
    virtual ~Rock();
  
    virtual void interact() override;
};

#endif
