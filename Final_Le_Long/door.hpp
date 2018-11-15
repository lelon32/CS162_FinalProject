/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents a door space. It is looked
 * unless the player has a key. 
 * *********************************************************************/
#ifndef DOOR_HPP 
#define DOOR_HPP 

#include "space.hpp"

class Door : public Space
{
    private:

    public:
    Door();
    virtual ~Door();
  
    virtual void interact() override;
};

#endif
