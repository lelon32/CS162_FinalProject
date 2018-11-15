/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class is an abstract base class for the player, 
 * any npcs that the player will interact with, and any mobs that the
 * player will be fighting.
 * *********************************************************************/
#ifndef CHARACTER_HPP 
#define CHARACTER_HPP 

#include "space.hpp"
#include "item.hpp"
#include "menu.hpp"

#include <climits>

#include <fstream>
using std::ifstream;

#include <string>
using std::string;
using std::to_string;

enum MobType {GOBLIN, ORC, OGRE, BANDIT, BANDIT_KING, PRINCESS, NONE};

/***********************************************************************
 * ** Description: This structure represents the coordinates of an object
 * instance in the game.
 * *********************************************************************/
struct Coordinates
{
    unsigned row,
             column;

    /***********************************************************************
     * ** Description: This default constructor initializes the row and 
     * column coordinates when the structure is created.
     * *********************************************************************/
    Coordinates()
    {
        row = 0;
        column = 0;
    }
};

class Character 
{
    protected:
    //Battle specifications for characters.
    int attackDiceMax,
        attackDiceNumber,
        defenseDiceMax,
        defenseDiceNumber,
        armor,
        hitPoints,
        maxHP;

    Menu characterMenu;

    unsigned moveNumber;
    MobType mobType;
    string identity;
    Coordinates characterCoordinates;
    bool dead;
    
    //Each character has a backpack container of size 6.
    Item** backpack;
    unsigned backpackSize;

    public:
    Character();
    Character(unsigned, unsigned);
    virtual ~Character() = 0;

    //Virtual functions.
    virtual int attack() const;
    virtual void defend(int);
    virtual Item* loot();
    virtual void getStats();

    void moveCharacter(Directions);

    //Getters.
    bool getDeadStatus() const;
    unsigned getMoveNumber() const;
    Coordinates getCoordinates() const;
    MobType getMobType() const;
    int getArmor() const;
    int getHitPoints() const;
    string getIdentity() const;
    int getMaxHP() const;
    void getEnding(const string &);

    void setHitPoints(int);
    void setCoordinates(int, int);
    void setDeadStatus(bool);
    void setItemNullLoot();

    void recoverHitPoints(int);
    void giveItem(ItemType);

    void grabLoot(Character*); 
    void grabLoot(Space*);

    //Backpack related.
    Item** backpackContents();
    unsigned getBackpackSize() const;

    bool checkForTravelCloak();
    bool checkForKey();

    bool interact();
};

#endif
