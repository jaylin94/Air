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
#include <cstdlib>
#include <ctime>
#include "menu.hpp"
#include "game.hpp"
using std::cin;
using std::cout;
using std::endl;

int main()
{
    //Seed rand() to generate random values correctly
    srand(time(0));

    //Game object and pointer to pass into the menu
    Game game1;
    Game *pGame = &game1;

    Menu menu1;

    //Runs main menu and main game
    menu1.runMenu(pGame);

    return 0;
}