#ifndef FIRSTAID_HPP
#define FIRSTAID_HPP
#include <iostream>
#include <string>
#include "item.hpp"

//Firstaid derived item class to heal player with each use
class FirstAid : public Item
{
public:
    FirstAid();

    //Returns enum itemType heal
    itemType action();

    ~FirstAid()
    {
    }
};

#endif