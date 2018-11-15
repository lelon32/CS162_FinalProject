/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents an item that a space or
 * character can contain. The different types of items are used for
 * different purposes by the player. 
 * *********************************************************************/
#include "item.hpp"

/***********************************************************************
 * ** Description: This default constructor is empty. It is good
 * practice to have a default constructor.
 * *********************************************************************/
Item::Item()
{
    //empty.
}

/***********************************************************************
 * ** Description: This constructor initializes the member variables of
 * the class.
 *
 * Parameters: ItemType - represents the type of item to be created.
 * *********************************************************************/
Item::Item(ItemType item)
{
    this->item = item;    
    determineName();
}

/***********************************************************************
 * ** Description: This function determines the string name of the item
 * based off of its item type.
 *
 * Parameters: none. 
 *
 * Return: void.
 * *********************************************************************/
void Item::determineName()
{
    switch(item)
    {
        case HERB:
            itemName = "medicinal herb";
            break;

        case APPLE:
            itemName = "apple";
            break;
        
        case CLOAK:
            itemName = "travel cloak";
            break;
        
        case KEY_HIDEOUT:
            itemName = "hideout key";
            break;
            
        case KEY_DUNGEON:
            itemName = "dungeon key";
            break;

        case EMPTY:
            break;
    }
}


ItemType Item::getItemType() const
{
    return item;
}

string Item::getItemName() const
{
    return itemName;
}
