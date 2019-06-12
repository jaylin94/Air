#ifndef JUNK_HPP
#define JUNK_HPP
#include <iostream>
#include <string>
#include "item.hpp"

//Junk derived item class for junk objects
class Junk : public Item
{
public:
    Junk();

    //Returns enum itemType junkItem
    itemType action();

    ~Junk()
    {
    }
};

#endif