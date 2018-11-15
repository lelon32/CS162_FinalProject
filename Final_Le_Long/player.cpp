/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents the player that the user wil be
 * controlling. The class initiates and stores the player values to be
 * used in battle. If the player dies the game will end. This class is 
 * derived from the Character class.
 * *********************************************************************/
#include "player.hpp"

/***********************************************************************
 * ** Description: This default constructor is empty. It is good
 * practice to have a default constructor.
 * *********************************************************************/
Player::Player()
{
    //empty.
}

/***********************************************************************
 * ** Description: This constructor initializes member variables of the
 * class.
 *
 * Parameter: unsigned row & column - represents the coordinates of the
 * player.
 * *********************************************************************/
Player::Player(unsigned row, unsigned column) : Character(row, column)
{
    attackDiceMax = 8,
    attackDiceNumber = 2,
    defenseDiceMax = 6,
    defenseDiceNumber = 2,
    armor = 2,
    maxHP = 12;
    hitPoints = 12; 
    mobType = NONE;

    moveNumber = 5;
    identity = "Isa";
}

/***********************************************************************
 * ** Description: This destructor is empty. This is good practice to
 * create a virtual destructor for polymorphic behavior.
 * *********************************************************************/
Player::~Player()
{
    //empty.
}

/***********************************************************************
 * ** Description: This function retrieves the words contained in a
 * file named player.txt. This file shows the initial stats of the
 * player.
 *
 * Parameter: none. 
 *
 * Return: void.
 * *********************************************************************/
void Player::getStats() 
{
    char temp;
    string stats = "";
    
    inputFile.open("player.txt");

    if(!inputFile)
    {
        cout << "\nThe player.txt file could not open!!";
        cin.ignore(INT_MAX, '\n');
    }

    else
    {
        //Retrieve every character without skipping.
        while(inputFile >> std::noskipws >> temp)
        {
            stats += temp;
        }

        cout << stats;

        cin.ignore(INT_MAX, '\n');
    }

    inputFile.close();
}
