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
#include "keySpace.hpp"
using std::cin;
using std::cout;
using std::endl;

KeySpace::KeySpace()
{
    //Sets default values for KeySpaces
    setSpaceType(key);
    setItem(&keyItem1);
    setTraversal(false);
    setInspection(false);
    setBoolItem(true);
    setBoolLeak(false);
    setBoolPlayerspace(false);
    setBoolValid(true);
    setDescrip("There's something shiny here.");
    setClues("It's a key. This should be useful.");
}
