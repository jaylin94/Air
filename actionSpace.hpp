#ifndef ActionSpace_HPP
#define ActionSpace_HPP
#include <iostream>
#include "space.hpp"
#include "firstAid.hpp"

//ActionSpaces for user to interact with special situations: hatch, tunnel, door
class ActionSpace : public Space
{
public:
    ActionSpace();

    //FirstAid object for successful interaction with the hatch type of actionSpace
    FirstAid firstAid1;

    //Initializes space to selected space type (hatch, tunnel, door)
    void initSpace(int choice);

    //No action or update for ActionSpaces
    void action()
    {
    }
    void updateSpace()
    {
    }

    virtual chances getChance();

    ~ActionSpace()
    {
    }
};

#endif