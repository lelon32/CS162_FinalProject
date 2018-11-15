/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Date:
 * ** Description: This class is derived from the Space class. It
 * represents the ground and can be walked on by the player, NPCs, or
 * mobs. 
 * *********************************************************************/
#ifndef GROUND_HPP
#define GROUND_HPP

#include "space.hpp"

class Ground : public Space
{
    private:

    public:
    Ground();
    virtual ~Ground();

    virtual void interact() override;
};

#endif
