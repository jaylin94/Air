#ifndef LOCKEDSPACE_HPP
#define LOCKEDSPACE_HPP
#include <iostream>
#include "space.hpp"
#include "item.hpp"

//LockedSpace type to hold exits, user can use a key object to interact and escape to win the game.
class LockedSpace : public Space
{
public:
    LockedSpace();

    //Action swaps locked and unlocked type for lockedSpaces
    void action()
    {
        if (getSpaceType() == locked)
        {
            setSpaceType(unlocked);
        }
        else if (getSpaceType() == unlocked)
        {
            setSpaceType(locked);
        }
    }

    //No update or chances for lockedSpaces
    void updateSpace()
    {
    }
    chances getChance()
    {
        return success;
    }

    ~LockedSpace()
    {
    }
};

#endif