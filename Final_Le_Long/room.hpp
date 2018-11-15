/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents a room within the game. It 
 * contains a 2D array of pointers to spaces which is used as a playing 
 * field that characters can interact with. This class is essentially
 * the brains of the game. It sets up the playing field, presents an
 * in-game menu, and controls all of the characters.
 * *********************************************************************/
#ifndef ROOM_HPP
#define ROOM_HPP

#include "menu.hpp"
#include "space.hpp"
#include "ground.hpp"
#include "tree.hpp"
#include "water.hpp"
#include "rock.hpp"
#include "door.hpp"
#include "character.hpp"
#include "player.hpp"
#include "goblin.hpp"
#include "orc.hpp"
#include "ogre.hpp"
#include "bandit.hpp"
#include "billy.hpp"
#include "dead.hpp"
#include "princess.hpp"
#include "item.hpp"
#include "campfire.hpp"

//This is included for the timing function, usleep.
#include <unistd.h>

#include <iomanip>
using std::setw;
using std::right;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <string>
using std::string;
using std::to_string;

#include <cstdlib>
using std::abs;

enum RoomType {BEGIN, BEFORE_INTERSECTION, INTERSECTION, DEAD_END, HIDEOUT, DUNGEON, NO_TRANSITION}; 

class Room 
{
    private:
    Menu gameMenu;

    //Used to connect to different rooms.
    Room* north;
    Room* south;
    Room* east;
    Room* west;

    //These variables are losing condition controls. 
    //cold - if drops to zero you die from hypothermia.
    //princessCountDown - if drops to zero the bandits escape with the princess.
    static int cold;
    static int princessCountDown;

    //The playing field.
    Space*** stage;

    //The character the user is assuming.
    Character* Player;
    char playerGraphics;

    //The direction of the player in the current room.
    Directions playerDirection;

    //The direction the player is facing
    //when she transitions to a different room.
    Directions movingDirection;

    //Menu control variables.
    string controlChoice; 
    string controlPlayerMenu; 
    string controlBackpack;

    //Enemies within the playing field.
    Character** mob;
    unsigned mobNumber; 

    //Filenames where the object creation 
    //instructions are located. 
    string treesInput;
    string rocksInput;
    string waterInput;
    string mobsInput;

    //Type of room this object is.
    RoomType roomType;

    //Which room the player is moving to.
    RoomType moveToRoom;

    //Size of 2D array room.
    unsigned rows,
             columns;

    //Battle flow control variables.
    bool endPlayerTurn;
    bool endMobTurn;

    //Controls whether or not a battle
    //is occuring.
    bool inBattle;

    //Controls whether or not a game
    //has ended.
    bool endGame;

    //Used to retrieve the count of mobs in the .txt config file.
    ifstream countMobFile;

    //Creates the 2D array of pointer to Space.
    void createRoom();
    
    //This function fills the room with spaces and objects.
    void fillRoom();
    
    //This function connects the spaces in the room
    //via four directional pointers.
    void connectSpaces();

    //Get the char representation of the space type.
    char getGraphics(SpaceType);

    //Control placing of spaces.
    void placeSpace(const string &, SpaceType);
    void placeSpecialSpace(int, int, SpaceType);

    //Places or unplaces characters in the room.
    void placeCharacter(Character*);
    void unPlaceCharacter(Character*);

    void setPlayerGraphics(Directions);
    
    //This function prints out the the graphics
    //of the room to console.
    void printRoom();
    void printRoom(Character*);
    void printRoom(unsigned, Character*);

    //Player control menu.
    void controlMenu(unsigned);

    //Controls player locations and movements.
    void moveCharacter(Character*);
    void moveDirection(Directions, Space*);
    void mobMove(Directions, Space*, Character*, int);

    //Allows characters to interact with the environment.
    void interactEnvironment(Character*);
    void interactDirection(Directions, Space*, unsigned, unsigned);

    //Some mob related functions.
    unsigned countMob();
    void createMobs();
    Character* generateMob(const string &, unsigned, unsigned);
    void placeMobs();    
    char getMobGraphics(MobType);
    void mobTurn(Character*);
    void mobAttacksPlayer(unsigned, unsigned, Character* mob);

    //The heads up display that appears above the room print.
    //It contains instructions for the user to control the
    //player.
    string hud() const;
    string hudPlayerMenu() const;

    //Used to print out the hud() function above.
    void printHud();


    public:
    Room();
    Room(bool, Character*, RoomType, unsigned, unsigned, 
         const string &, const string &, 
         const string &, const string &);
    ~Room();

    //These functions are used to connect the rooms from main.
    void setNorth(Room*);
    void setSouth(Room*);
    void setEast(Room*);
    void setWest(Room*);

    Directions getMovingDirection() const;
    RoomType getRoomType() const;
    RoomType getMoveToRoom() const;
    void resetMoveToRoom();
    bool getEndGame() const;

    void initiate();
};

#endif
