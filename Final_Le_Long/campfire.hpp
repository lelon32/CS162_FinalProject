/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents a campfire space. It warms up 
 * the player when interacted with. This works in conjunction with the
 * program's hypothermia (death) simulater.
 * *********************************************************************/
#ifndef CAMPFIRE_HPP 
#define CAMPFIRE_HPP 

#include "space.hpp"

class Campfire : public Space
{
    private:

    public:
    Campfire();
    virtual ~Campfire();

    virtual void interact() override;
};

#endif
