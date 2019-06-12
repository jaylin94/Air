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
#include "player.hpp"
using std::cin;
using std::cout;
using std::endl;

//Initializes backpack to hold 3 nullptrs
void Player::initBackpack()
{
    for (int i = 0; i < 3; i++)
    {
        backpack.reserve(3);
        backpack.push_back(nullptr);
        backpack.push_back(nullptr);
        backpack.push_back(nullptr);
    }
}

//Adds item to the player's vector backpack. Takes an Item pointer as a parameter to add.
void Player::addItem(Item *pItem)
{
    //While backpack holds less than 3, add item, else output at capacity message
    if (getItemCount() <= 3)
    {
        backpack.at(getItemCount()) = pItem;
        setItemCount(getItemCount() + 1);
    }
    else
    {
        cout << "My backpack is full. I can't pick it up." << endl;
    }
}
