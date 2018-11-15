/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class is an abstract base class for the types of
 * spaces that exists in the game. Each space allows the player to
 * interact with it differently. The Tree and Water spaces have a 1/5
 * chance of containing an item to loot. The Ground spaces can be walked 
 * on. The Rock spaces serve to be a wall. The Campfire space warms the
 * player up.
 * *********************************************************************/
#ifndef SPACE_HPP
#define SPACE_HPP

#include "item.hpp"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

enum SpaceType {GROUND, ROCK, TREE, WATER, DOOR, CAMPFIRE};
enum Directions {UP = 1, DOWN, LEFT, RIGHT};

class Space
{
    protected:
    SpaceType type;
    bool occupied;
    string spaceName;

    Item* item;

    //Pointer connectors in the game which
    //to connect the spaces.
    Space* up; 
    Space* down;
    Space* left;
    Space* right;

    public:
    Space();
    virtual ~Space();

    virtual void interact() = 0;

    void connectSpaces(Directions, Space*);

    Space* traverse(Directions);

    Item* loot();
    void setItemNullLoot();

    void setOccupied(bool);
    bool getOccupied();

    SpaceType getSpaceType(); 
    string getSpaceName() const;
}; 

#endif
