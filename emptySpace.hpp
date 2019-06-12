#ifndef EMPTYSPACE_HPP
#define EMPTYSPACE_HPP
#include <iostream>
#include "space.hpp"

//Empty space on the map, nothing the player inspect here
class EmptySpace : public Space
{
public:
    EmptySpace()
    {
        //Sets values to track empty spaces and print out the correct map
        setSpaceType(empty);
        setTraversal(false);
        setInspection(false);
        setBoolItem(false);
        setBoolLeak(false);
        setBoolPlayerspace(false);
        setBoolValid(true);
        setDescrip("There's nothing here. I should keep moving.");
        setClues("Let's get out of this spot.");
    }

    //No action, update, or chance for empty spaces
    void action()
    {
        std::cout << "There's nothing to do here." << std::endl;
    }
    void updateSpace()
    {
    }
    virtual chances getChance()
    {
        return success;
    }

    ~EmptySpace()
    {
    }
};

#endif