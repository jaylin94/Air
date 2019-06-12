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
#include "firstAid.hpp"
using std::cin;
using std::cout;
using std::endl;

FirstAid::FirstAid()
{
    setDescrip("Comforting, but it won't help with the leaks.");
    setName("Coffee (I could drink this for my own health. Needs some sugar.)");
}

//Returns enum itemType heal
itemType FirstAid::action()
{
    return heal;
}