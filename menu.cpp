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
#include <string>
#include "menu.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;

//Displays menu for the game, prompts user to start or quit. Provides a
//quick description of the game. Displays menu to rerun as well.
void Menu::displayMenu()
{
    //Times run checks if this is the first time running.
    //The welcome message will only be displayed if timesRun is 0.
    if (timesRun == 0)
    {
        //gameName is set by getProgramName() in the constructor.
        cout << "Welcome to " << getProgramName() << "." << endl;

        cout << "Please enter 's' to start, or 'q' to quit. " << endl;
    }
    //Displays rerun prompt if timesRun is > 0.
    else if (timesRun > 0)
    {
        cout << "Restart " << getProgramName() << "? "
             << "Enter 's' to start, 'q' to quit." << endl;
    }
    setTimesRun(getTimesRun() + 1);
}

//Displays function options menu
void Menu::displayMenu2()
{
    cout << "Please choose from the following options: " << endl;
    cout << "1. Play" << endl;
    cout << "2. Exit " << endl;
}

//Runs all menu options for the program, including the main functions. Takes a Game pointer as a parameter
void Menu::runMenu(Game *pGame)
{
    //Display first menu to start or quit
    displayMenu();
    validateStartChoice();

    while (startCheck())
    {
        //Runs main game
        pGame->play();

        //Display re-run menu and get choice
        displayMenu();
        validateStartChoice();
    }
}

//Gets the user choice for the second menu, runs main functions. Takes a Game pointer as a parameter
bool Menu::menuChoice(Game *pGame)
{
    bool run = true;
    int userChoice;
    int rounds;
    int addChance;
    int removeChance;
    string userString;

    //Gets and validates user integer input for menu options 1 and 2.
    do
    {
        displayMenu2();
        int userChoice = validateInt(1);

        switch (userChoice)
        {
        case 1:
            pGame->play();
            break;

        case 2:
            run = false;
            return run;
        }
    } while (userChoice != 2);
    return run;
}

//Validates user integer input for a variety of functions in Menu. Takes an integer parameter to
//determine the range of acceptable inputs from the user. Returns an integer as a choice for
//corresponding menu functions.
int Menu::validateInt(int key)
{
    //Float validation adapted from: https://www.quora.com/How-do-I-check-if-a-number-is-float-on-C++
    double choice = 0.0;
    int floatTest = 0;

    int upperLim = 0;
    int lowerLim = 0;
    string message;

    //Range for main menu choice, 1 - 5
    if (key == 1)
    {
        message = "Please enter a valid integer 1 or 2.";
        upperLim = 2;
        lowerLim = 1;
    }
    //Range for steps, rows and columns, 1 - 32767
    else if (key == 2)
    {
        message = "Please enter a valid integer > 1, < 32767. ";
        upperLim = 32767;
        lowerLim = 1;
    }
    else if (key == 3)
    {
        message = "Please enter a valid integer 1-100. ";
        upperLim = 100;
        lowerLim = 1;
    }

    while (true)
    {
        //Detects invalid string/char input and reprompts user
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << message << endl;
        }
        //Detects float input, out of range input
        floatTest = choice * 100000000.0;
        if (((floatTest % 100000000) > 0) || choice < lowerLim || choice > upperLim)
        {
            //Clears extraction failure flag
            cin.clear();
            //Ignores next 10000 inputs in the buffer until \n
            cin.ignore(10000, '\n');
            cout << message << endl;
        }
        //Valid input, returns integer
        else
        {
            cin.ignore(10000, '\n');
            return choice;
        }
    }
}

//Validates menu input choice to start the program or quit.
//Ensures that input is a character of 's' to start or
//'q' to quit. Returns a character of 's' or 'q'.
char Menu::validateStartChoice()
{
    string choice;
    while (true)
    {
        cin >> (choice);
        //Character array to validate user input for a character, other inputs are
        //invalid.
        char newChoice[1];
        newChoice[0] = choice[0];
        cin.ignore(10000, '\n');
        if (choice.length() > 1)
        {
            cout << "Please enter 's' to start or 'q' to quit." << endl;
        }
        else if (newChoice[0] == 's' || newChoice[0] == 'q')
        {
            setStartChoice(newChoice[0]);
            return newChoice[0];
        }
        else
        {
            cout << "Please enter 's' to start or 'q' to quit." << endl;
        }
    }
}

//Prompts user for menu input to start or quit, using
//getMenuChoice(). Quits if user input is 'q'. Returns a bool of true (s) or false (q).
bool Menu::startCheck()
{
    if (getStartChoice() == 'q')
    {
        return false;
    }
    else
    {
        return true;
    }
}

//Displays a line of '~' characters, 90 characters long.
void Menu::displayLine()
{
    for (int i = 0; i < 90; i++)
    {
        cout << '~';
    }
    cout << endl;
}

//Asks user to press any key and/or ENTER/RETURN to continue.
void Menu::displayContinue()
{
    std::string anyKey;
    cout << "Press any key and/or ENTER/RETURN to continue. " << endl;
    getline(cin, anyKey);
}
