/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class is an abstract base class for the player, 
 * any npcs that the player will interact with, and any mobs that the
 * player will be fighting.
 * *********************************************************************/
#include "character.hpp"

/***********************************************************************
 * ** Description: This default constructor is empty. It is good
 * practice to have a default constructor.
 * *********************************************************************/
Character::Character()
{
    //empty.
}

/***********************************************************************
 * ** Description: This constructor initializes member variables of the
 * class.
 *
 * Parameter: unsigned row & column - the coordinates of the character.
 * *********************************************************************/
Character::Character(unsigned row, unsigned column)
{
    dead = false;
    characterCoordinates.row = row;
    characterCoordinates.column = column;

    //Initiates the character backpack.
    backpackSize = 6;
    backpack = new Item*[backpackSize];
    for(unsigned i = 0; i < backpackSize; i++)
    {
        backpack[i] = nullptr;
    }
}

/***********************************************************************
 * ** Description: This destructor cleans up the heap memory made with
 * new.
 * *********************************************************************/
Character::~Character()
{
    for(unsigned i = 0; i < backpackSize; i++)
    {
        if(backpack[i] != nullptr)
        {
            delete backpack[i];
        }
    }

    delete [] backpack;

    backpack = nullptr;
}

/***********************************************************************
 * ** Description: This function allows a character to attack another
 * character.
 *
 * Parameter: none. 
 *
 * Return: int - the attack damage of the character.
 * *********************************************************************/
int Character::attack() const
{
    int attackRoll;
    int attack = 0;

    cout << '\n' << identity << " attacks!!" << endl;

    //Roll attack dice.
    for(int i = 0; i < attackDiceNumber; i++)
    {
        attackRoll = rand() % attackDiceMax + 1; 
        attack += attackRoll;
        cout << "\nAttack Roll: " << attackRoll << ' ';
    }

    cout << "\n\nAttack Total: " << attack << endl;
    
    if(attack == (attackDiceMax * attackDiceNumber))
    {
        cout << '\n' << identity << " succeeds with a critical strike!!" << endl;
    }

    return attack;
}

/***********************************************************************
 * ** Description: This function allows a character to defend from 
 * another character's attack.
 *
 * Parameter: int - represents the attack damage from the other character. 
 *
 * Return: void. 
 * *********************************************************************/
void Character::defend(int attack)
{
    int defend = 0,
        defenseRoll,
        damage;

    cout << '\n' << identity << " defense maneuver!" << endl;

    //Roll defense dice.
    for(int i = 0; i < defenseDiceNumber; i++)
    {
        defenseRoll = rand() % defenseDiceMax + 1;
        defend += defenseRoll; 
        cout << "\nDefense Roll: " << defenseRoll << ' ';
    }
    
    cout << "\nArmor: " << armor;
    cout << "\n\nDefense Total: " << defend + armor << endl;

    //Damage calculations.
    damage = attack - defend - armor;

    if(damage <= 0)
    {
        cout << '\n' << identity << " performs a perfect defense maneuver!!" << endl;
    }

    cout << "\nDamage: " << attack << " - " 
         << defend + armor << " = " << damage;

    if(damage <= 0)
    {
        cout << " = 0";
        
        damage = 0;
    }

    cout << endl;

    //Subtract damage from character hit points.
    hitPoints -= damage;   

    //Checks to see if character has died.
    if(hitPoints <= 0)
    {
        dead = true; 

        if(identity == "Isa")
        {
            cout << '\n' << identity << " has been killed..." << endl;
        }

        else
        {
            cout << '\n' << identity << " has been slain." << endl;
        }
    }
}

/***********************************************************************
 * ** Description: This function allows a character to change coordinates. 
 *
 * Parameter: Directions - An enumerated data type that represents the 
 * direction the character is facing.
 *
 * Return: void. 
 * *********************************************************************/
void Character::moveCharacter(Directions move)
{
    switch(move)   
    {
        case UP:
            characterCoordinates.row--;
            break;

        case DOWN:
            characterCoordinates.row++;
            break;

        case LEFT:
            characterCoordinates.column--;
            break;

        case RIGHT:
            characterCoordinates.column++;
            break;
    }
}

bool Character::getDeadStatus() const
{
    return dead;
}

void Character::setCoordinates(int row, int column)
{
    characterCoordinates.row = row;
    characterCoordinates.column = column;
}

Coordinates Character::getCoordinates() const
{
    return characterCoordinates;
}

MobType Character::getMobType() const
{
    return mobType;
}

unsigned Character::getMoveNumber() const
{
    return moveNumber;
}

int Character::getArmor() const
{
    return armor;
}

int Character::getHitPoints() const
{
    return hitPoints;
}

string Character::getIdentity() const
{
    return identity;
}

/***********************************************************************
 * ** Description: This function recovers a character's hit points. 
 *
 * Parameter: int - number of hit points to recover. 
 *
 * Return: void. 
 * *********************************************************************/
void Character::recoverHitPoints(int recover)
{
    int tempHP = hitPoints;
    int recoveredHP = 0;

    if(hitPoints < maxHP)
    {
        hitPoints += recover;

        //Hit points max out at the original max value.
        if(hitPoints > maxHP)
        {
            //For display printing purposes.
            recoveredHP = maxHP - tempHP; 

            hitPoints = maxHP;
        }

        if(recoveredHP > 0)
        {
            cout << "\nYou recovered " << recoveredHP << " hit points!!" << endl;
        }

        else
        {
            cout << "\nYou recovered " << recover << " hit points!!" << endl;
        }
    }
}
    
//This getter function is empty in case
//there is another character object with 
//different stats to display. 
void Character::getStats() 
{
    //empty;
}

//Returns items from dead characters.
Item* Character::loot()
{
    return backpack[0];
}

void Character::setItemNullLoot()
{
    backpack[0] = nullptr; 
}

/***********************************************************************
 * ** Description: This function adds items to a character's backpack
 * from another character (that is dead). 
 *
 * Parameter: Character* - represents a dead character to loot from. 
 *
 * Return: void. 
 * *********************************************************************/
void Character::grabLoot(Character* dead)
{
    //Check if loot exists.
    if(dead->loot() != nullptr) 
    {
        bool foundSlot = false;

        //Iterate through each slot in the player's backpack
        //and searches for an open slot.
        for(unsigned i = 0; i < backpackSize && !foundSlot; i++)
        {
            if(backpack[i] == nullptr)
            {
                //Adds the item to the character and nulls 
                //the item in the dead character.
                backpack[i] = dead->loot();
                dead->setItemNullLoot();
                foundSlot = true;
                cout << "\nFound " << backpack[i]->getItemName() << '!' << endl;

                //Extra print statements.
                if(backpack[i]->getItemName() == "travel cloak")
                {
                    cout << "\nYour body starts to warm up!" << endl;
                }

                else if(backpack[i]->getItemName() == "hideout key")
                {
                    cout << "\nI wonder what door this opens..." << endl;
                }

                else if(backpack[i]->getItemName() == "dungeon key")
                {
                    cout << "\nTime to rescue the princess!" << endl;
                }
            }
        }

        if(foundSlot == false)
        {
                cout << "\nThere is no more room in the backpack!!" << endl;
        }
    }

    else
    {
        cout << '\n' << identity << " searches dead body but finds nothing..." << endl;
    }
}

/***********************************************************************
 * ** Description: This function adds items to a character's backpack. 
 * from a space.
 *
 * Parameter: Space* - represents a space to loot from. 
 *
 * Return: void. 
 * *********************************************************************/
void Character::grabLoot(Space* object)
{
    if(object->loot() != nullptr) 
    {
        bool foundSlot = false;

        //Iterate through each slot in the player's backpack
        //and searches for an open slot.
        for(unsigned i = 0; i < backpackSize && !foundSlot; i++)
        {
            if(backpack[i] == nullptr)
            {
                //Adds the item to the character and nulls 
                //the item in the dead character.
                backpack[i] = object->loot();
                object->setItemNullLoot();
                foundSlot = true;
                cout << "\nFound " << backpack[i]->getItemName() << '!' << endl;
            }
        }

        if(foundSlot == false)
        {
                cout << "\nThere is no more room in the backpack!!" << endl;
        }
    }

    else
    {
        cout << '\n' << identity << " searches the " << object->getSpaceName() << " but finds nothing..." << endl;
    }
}

/***********************************************************************
 * ** Description: This function adds items to a character's backpack. 
 *
 * Parameter: ItemType - represents the type of item to give the
 * character. 
 *
 * Return: void. 
 * *********************************************************************/
void Character::giveItem(ItemType item)
{
    bool foundSlot = false;

    //Iterate through each slot in the player's backpack
    //and searches for an open slot.
    for(unsigned i = 0; i < backpackSize && !foundSlot; i++)
    {
        if(backpack[i] == nullptr)
        {
            backpack[i] = new Item(item);
            foundSlot = true;
        }
    }

    if(foundSlot == false)
    {
            cout << "\nThere is no more room in the backpack!!" << endl;
    }
}

/***********************************************************************
 * ** Description: This function represents an interaction with a
 * character. There is an end game print display if the character that
 * is interacted with is the princess. 
 *
 * Parameter: none. 
 *
 * Return: void. 
 * *********************************************************************/
bool Character::interact()
{
    bool temp = false;

    if(identity == "Princess")
    {
        cout << "\033[2J\033[1;1H";
        getEnding("princess.txt");
        getEnding("ending.txt");
        cin.ignore(INT_MAX, '\n');
        temp = true;;
    }

    return temp;
}


Item** Character::backpackContents()
{
    return backpack;
}

unsigned Character::getBackpackSize() const
{
    return backpackSize;
}

/***********************************************************************
 * ** Description: This function looks in a character's backpack for a
 * travel cloak.
 *
 * Parameter: none. 
 *
 * Return: bool - returns true if a travel cloak is found. 
 * *********************************************************************/
bool Character::checkForTravelCloak() 
{
    bool foundCloak = false;

    for(unsigned i = 0; i < backpackSize && !foundCloak; i++)
    {
        if(backpack[i] != nullptr)
        {
            if(backpack[i]->getItemType() == CLOAK)
            {
                foundCloak = true;
            }
        }
    }

    return foundCloak;
}

/***********************************************************************
 * ** Description: This function looks in a character's backpack for a
 * key.
 *
 * Parameter: none. 
 *
 * Return: bool - returns true if a key is found.. 
 * *********************************************************************/
bool Character::checkForKey() 
{
    bool foundKey = false;

    for(unsigned i = 0; i < backpackSize && !foundKey; i++)
    {
        if(backpack[i] != nullptr)
        {
            //Any type of key and open any type of door.
            if(backpack[i]->getItemType() == KEY_HIDEOUT
               || backpack[i]->getItemType() == KEY_DUNGEON)
            {
                //Deletes the key to free up the
                //backpack slot after it is used
                //to open a door.
                delete backpack[i];
                backpack[i] = nullptr;
                foundKey = true;
            }
        }
    }

    if(foundKey)
    {
        cout << "\nYou unlocked the door!" << endl;
        cin.ignore(INT_MAX, '\n'); 
    }

    else
    {
        cout << "\nThe door seems to be locked." << endl;
        cin.ignore(INT_MAX, '\n'); 
    }

    return foundKey;
}

int Character::getMaxHP() const
{
    return maxHP;
}

void Character::setHitPoints(int hitPoints)
{
    this->hitPoints = hitPoints;
}

/***********************************************************************
 * ** Description: This function is used to print out the contents of a
 * text file.
 *
 * Parameter: const string& - this represents the file name to read from. 
 *
 * Return: void. 
 * *********************************************************************/
void Character::getEnding(const string &fileName) 
{
    char temp;
    string print = "";
    ifstream inputFile;
    
    inputFile.open(fileName);

    if(!inputFile)
    {
        cout << "\nThe " << fileName << " could not open!!";
        cin.ignore(INT_MAX, '\n');
    }

    else
    {
        while(inputFile >> std::noskipws >> temp)
        {
            print += temp;
        }

        cout << print;
    }

    inputFile.close();
}

void Character::setDeadStatus(bool dead)
{
    this->dead = dead;
}
