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
    srand(time(0));
    Game game1;
    Game *pGame = &game1;

    Menu menu1;

    menu1.runMenu(pGame);

    return 0;
}