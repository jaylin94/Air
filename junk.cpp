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
#include "junk.hpp"
using std::cin;
using std::cout;
using std::endl;

Junk::Junk()
{
    setDescrip("Completely useless.");
    setName("Junk (I should toss this.)");
}

//Returns enum itemType junkItem
itemType Junk::action()
{
    return junkItem;
}