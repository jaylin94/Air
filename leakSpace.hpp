#ifndef LEAKSPACE_HPP
#define LEAKSPACE_HPP
#include <iostream>
#include "space.hpp"

//LeakSpace contains leaks that the user can interact with and stop using plug item objects.
//Stopping each leak reduces int leak in the Game class by 1. Stopping all leaks is the best
//ending and results in a special message if the user escapes successfully.
class LeakSpace : public Space
{
public:
    LeakSpace();

    //Sets leak to be on or off
    void action()
    {
        if (getBoolLeak() == true)
        {
            setBoolLeak(false);
        }
        else if (getBoolLeak() == false)
        {
            setBoolLeak(true);
        }
    }

    //Updates space description and clues, for each bool leak value
    void updateSpace();

    //No chances for leakSpaces
    chances getChance()
    {
        return success;
    }

    ~LeakSpace()
    {
    }
};

#endif