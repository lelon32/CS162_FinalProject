/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents a water space. It has a 1/5
 * chance of containing a medicinal herb which heals the player when
 * used.
 * *********************************************************************/
#ifndef WATER_HPP 
#define WATER_HPP 

#include "space.hpp"

class Water : public Space
{
    private:

    public:
    Water();
    virtual ~Water();

    virtual void interact() override;
};

#endif
