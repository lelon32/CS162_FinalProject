/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents an item that a space or
 * character can contain. The different types of items are used for
 * different purposes by the player. 
 * *********************************************************************/
#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
using std::string;

enum ItemType {HERB, APPLE, CLOAK, KEY_HIDEOUT, KEY_DUNGEON, EMPTY};

class Item
{
    private:
    ItemType item;
    string itemName;

    void determineName();

    public:
    Item();
    Item(ItemType);
    ItemType getItemType() const;
    string getItemName() const;
};

#endif
