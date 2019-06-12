#ifndef ITEMSPACE_HPP
#define ITEMSPACE_HPP
#include <iostream>
#include "space.hpp"
#include "item.hpp"
#include "firstAid.hpp"
#include "plug.hpp"
#include "junk.hpp"

//Item space for generic items that the user can inspect and store in backpack vector in Player class
class ItemSpace : public Space
{
public:
    ItemSpace();

    //3 item objects for item pointers to point to
    FirstAid firstAid1;
    Plug plugItem1;
    Junk junkItem1;

    //No action, update, or chances for itemSpaces
    void action()
    {
    }
    void updateSpace()
    {
    }
    virtual chances getChance()
    {
        return success;
    }

    //Initializes space with randomly selected item object
    void initSpace();

    ~ItemSpace()
    {
    }
};

#endif