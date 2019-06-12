#ifndef KEY_HPP
#define KEY_HPP
#include <iostream>
#include <string>
#include "item.hpp"

//Key derived item class for user to interact with lockedSpaces
class Key : public Item
{
public:
    Key();

    //Returns enum itemType keyItem
    itemType action();

    ~Key()
    {
    }
};

#endif