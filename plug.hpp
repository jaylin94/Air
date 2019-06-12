#ifndef PLUG_HPP
#define PLUG_HPP
#include <iostream>
#include <string>
#include "item.hpp"

//Plug derived item class for user to use on leakSpaces to stop leaks
class Plug : public Item
{
public:
    Plug();

    //Returns enum itemtype plug
    itemType action();

    ~Plug()
    {
    }
};

#endif