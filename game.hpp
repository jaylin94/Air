#ifndef GAME_HPP
#define GAME_HPP
#include <string>
#include "space.hpp"
#include "emptySpace.hpp"
#include "actionSpace.hpp"
#include "itemSpace.hpp"
#include "keySpace.hpp"
#include "leakSpace.hpp"
#include "lockedSpace.hpp"
#include "player.hpp"
#include "firstAid.hpp"

//Game class to run main game, player, space, item interactions
class Game
{
private:
    //Space pointer to hold 2D array of linked space pointers
    Space ***map;

    //Pointers for Space and Player objects
    Space *currentSpace;
    Player *pPlayer;
    EmptySpace *pEmptySpace;
    ActionSpace *pActionSpace;
    ItemSpace *pItemSpace;
    KeySpace *pKeySpace;
    LeakSpace *pLeakSpace;
    LockedSpace *pLockedSpace;

    //Bool to keep track of player escaping (winning the game)
    bool escape;

    //String for health messages
    std::string health;

    //Int values for moves, leaks, row + col count
    int moves;
    int leaks;
    int numRows;
    int numCols;

public:
    Game()
    {
        //Sets default values for counts
        setNumRows(5);
        setNumCols(5);
        setMoves(0);
        setLeaks(1);

        //Allocates memory for each derived space, player
        pPlayer = new Player;
        pEmptySpace = new EmptySpace[25];
        pActionSpace = new ActionSpace[3];
        pItemSpace = new ItemSpace[25];
        pKeySpace = new KeySpace[25];
        pLeakSpace = new LeakSpace[25];
        pLockedSpace = new LockedSpace[25];

        //Allocate map with spaces
        allocMap();

        //Set's initial space
        setCurrentSpace(map[2][2]); //start space for player

        //Set default escape value
        setEscape(false);
    }

    //Display main play menu
    void displayPlayMenu();

    //Allocate functions for space objects that compose the map
    void allocMap();
    void reallocSpaces();
    void deallocAll();
    void printMap();

    //Main play function, intro display, ending
    void play();
    void displayChapter0();
    void ending();

    //Adds leaks as game progresses
    void addLeaks();

    //Allows player to inspect room and interact, pickup items, sets new bool values to update printMap()
    void inspectRoom();

    //Runs actions for actionSpaces
    void runActions();
    void actionMenu();
    void actionResult();
    void actionSuccess(chances currentChance);

    //Results and intros of actionSpace types
    void hatchIntro();
    void tunnelIntro();
    void doorIntro();
    void hatchSuccess();
    void hatchFailure();
    void tunnelSuccess();
    void tunnelFailure();
    void doorSuccess();
    void doorFailure();

    //Item functions
    void itemMenu();
    void displayItems();
    void pickupItem();
    int validateItemChoice();
    void useItem(int key);
    void updateItems(int key);

    //Health functions
    void adjustHealth();
    void determineHealth();

    //Sleep functions
    void sleep1Sec();
    void sleep2Sec();

    //Move functions to move Player around map
    void move();
    void displayMoveChoices();
    int validateMoveKey();

    //Validates integer inputs
    int validateInt(int key);

    //Getters
    Space *getCurrentSpace()
    {
        return currentSpace;
    }
    EmptySpace *getEmptySpace()
    {
        return pEmptySpace;
    }
    ActionSpace *getActionSpace()
    {
        return pActionSpace;
    }
    ItemSpace *getItemSpace()
    {
        return pItemSpace;
    }
    KeySpace *getKeySpace()
    {
        return pKeySpace;
    }
    LeakSpace *getLeakSpace()
    {
        return pLeakSpace;
    }
    LockedSpace *getLockedSpace()
    {
        return pLockedSpace;
    }
    Player *getPlayer()
    {
        return pPlayer;
    }
    std::string getHealth()
    {
        return health;
    }
    bool getEscape()
    {
        return escape;
    }
    int getMoves()
    {
        return moves;
    }
    int getLeaks()
    {
        return leaks;
    }
    int getNumRows()
    {
        return numRows;
    }
    int getNumCols()
    {
        return numCols;
    }

    //Setters
    void setCurrentSpace(Space *currentSpace)
    {
        currentSpace->setBoolPlayerspace(true);
        this->currentSpace = currentSpace;
    }
    void setHealth(std::string health)
    {
        this->health = health;
    }
    void setEscape(bool escape)
    {
        this->escape = escape;
    }
    void setMoves(int moves)
    {
        this->moves = moves;
    }
    void setLeaks(int leaks)
    {
        this->leaks = leaks;
    }
    void setNumRows(int numRows)
    {
        this->numRows = numRows;
    }
    void setNumCols(int numCols)
    {
        this->numCols = numCols;
    }

    ~Game()
    {
        deallocAll();
    }
};

#endif
