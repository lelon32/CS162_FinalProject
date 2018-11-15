/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents a tree space. It has a 1/5
 * chance of containing an apple which heals the player when used.
 * *********************************************************************/
#ifndef TREE_HPP
#define TREE_HPP

#include "space.hpp"

class Tree : public Space
{
    private:

    public:
    Tree();
    virtual ~Tree();
  
    virtual void interact() override;
};

#endif
