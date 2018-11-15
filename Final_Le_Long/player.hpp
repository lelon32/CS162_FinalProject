/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the player that the user wil be
 * controlling. The class initiates and stores the player values to be
 * used in battle. If the player dies the game will end. This class is 
 * derived from the Character class.
 * *********************************************************************/
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

class Player : public Character
{
    private:
    ifstream inputFile;

    public:
    Player();
    Player(unsigned, unsigned);
    virtual ~Player();
    virtual void getStats() override;
};

#endif
