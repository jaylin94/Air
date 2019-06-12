/*********************************************************************
** Program name: Air
** Author: Jay Lin
** Date: 06/07/2019
** Description: This is a game where the player wakes up in a dark room.
** Something is wrong, and it is up to the user to figure a way out of 
** their current, unfortunate circumstance. The user can use items, 
** interact with each space, take their chances with special events. 
** To start, extract all files. Type "make" to compile the program.
** Then type "./air" to run the program.
*********************************************************************/
#include <iostream>
#include "actionSpace.hpp"
using std::cin;
using std::cout;
using std::endl;

ActionSpace::ActionSpace()
{
    //Sets default values for actionSpaces. initSpace() must be called in Game.cpp, allocMap() when map is allocated to set
    //each actionSpace correctly.
    setSpaceType(actionSpace);
    setTraversal(false);
    setInspection(false);
    setBoolItem(true);
    setBoolLeak(false);
    setBoolPlayerspace(false);
    setBoolValid(true);
    setDescrip("There's something here.");
}

//Initializes actionSpace to specific space type. Takes an integer as a parameter.
//1 selects hatch, 2 tunnel, 3 door.
void ActionSpace::initSpace(int choice)
{
    if (choice == 1)
    {
        setSpaceType(hatch);
        setItem(&firstAid1);
        setClues("There's hatch on the ceiling. I can't quite reach it. ");
    }
    else if (choice == 2)
    {
        setSpaceType(tunnel);
        setClues("There seems to be narrow tunnel here. It's too dark to see where it leads. ");
    }
    else if (choice == 3)
    {
        setSpaceType(door);
        setClues("There's a door here. It's jammed but with enough force I might be able to open it.");
    }
}

//Returns random chance of success or failure for each specific actionSpace type. Return value is enum chances
chances ActionSpace::getChance()
{
    //50/50 chance of success or failure
    int chance = (rand() % 2) + 1;

    if (chance == 1)
    {
        return success;
    }
    else if (chance == 2)
    {
        return failure;
    }
}
