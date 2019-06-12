#ifndef MENU_HPP
#define MENU_HPP
#include <string>
#include "game.hpp"

class Menu
{
private:
    int timesRun;
    char startChoice;
    std::string programName;

public:
    Menu()
    {
        timesRun = 0;
        startChoice = 's';
        programName = "Air";
    }

    //Menu functions to display and check to start or quit
    void displayMenu();
    void displayMenu2();
    bool menuChoice(Game *pGame);
    void runMenu(Game *pGame);

    //Misc. display functions
    void displayLine();
    void displayContinue();

    //Menu functions to get choice and validate input
    bool startCheck();

    //Validates user start choice and integer input
    char validateStartChoice();
    int validateInt(int key);
    void validateQueueOptions(int &, int &, int &);

    //Get functions for variables
    int getTimesRun()
    {
        return timesRun;
    }
    char getStartChoice()
    {
        return startChoice;
    }
    std::string getProgramName()
    {
        return programName;
    }

    //Set functions for variables
    void setTimesRun(int timesRun)
    {
        this->timesRun = timesRun;
    }
    void setStartChoice(char startChoice)
    {
        this->startChoice = startChoice;
    }
    void setProgramName(std::string programName)
    {
        this->programName = programName;
    }
};

#endif