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
#include "leakSpace.hpp"
using std::cin;
using std::cout;
using std::endl;

LeakSpace::LeakSpace()
{
    //Sets default values for LeakSpaces
    setSpaceType(leakSpace);
    setTraversal(false);
    setInspection(false);
    setBoolItem(false);
    setBoolLeak(false);
    setBoolPlayerspace(false);
    setBoolValid(true);
    setDescrip("There's a crack in the wall. A little bit of water is coming through.");
    setClues("This room might be a problem for me soon.");
}

//Updates space description and clue for when the player inspects the room in Game.cpp, inspectRoom()
void LeakSpace::updateSpace()
{
    if (getBoolLeak() == true)
    {
        setDescrip("The source of a leak, it's here.");
        setClues("If I have a plug, I should use it here to stop the leak.");
    }
    else if (getBoolLeak() == false)
    {
        setDescrip("There's a crack in the wall. A little bit of water is coming through.");
        setClues("This room might be a problem for me soon.");
    }
}