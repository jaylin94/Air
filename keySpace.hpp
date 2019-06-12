#ifndef KEYSPACE_HPP
#define KEYSPACE_HPP
#include <iostream>
#include "itemSpace.hpp"
#include "key.hpp"

//Key space to hold special item Key that the user can pick up so that the user can escape on a lockedSpace
class KeySpace : public ItemSpace
{
public:
    KeySpace();

    //Key item for pItem to point to
    Key keyItem1;

    //No action, update, chance for keySpace
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

    ~KeySpace()
    {
    }
};

#endif