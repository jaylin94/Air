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
#include <unistd.h>
#include <vector>
#include <iterator>
#include "game.hpp"
using std::advance;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

//Displays main menu for user actions while playing
void Game::displayPlayMenu()
{
    //Displays choices, stores user choice in menuChoice
    int menuChoice;
    cout << "Enter 1 to move." << endl;
    cout << "Enter 2 to inspect the room." << endl;
    cout << "Enter 3 to see your items." << endl;
    cout << "Enter 4 to use an item." << endl;
    menuChoice = validateInt(10);

    //Menu functionality to run appropriate functions for user choice
    switch (menuChoice)
    {
    //Moves Player, adds leaks if necessary, adjusts health
    case 1:
        move();
        addLeaks();
        adjustHealth();
        break;
    //Prints map, inspects room, adds leaks if necessary
    case 2:
        printMap();
        inspectRoom();
        addLeaks();
        break;
    //Displays items in Players backpack vector
    case 3:
        displayItems();
        break;
    //Displays item menu to use item, adds leaks if necessary
    case 4:
        itemMenu();
        addLeaks();
        break;
    };
}

//Allocates map, sets all derived spaces on the map for player to interact with
void Game::allocMap()
{
    //Allocates space pointers for 2D array of Space pointers
    int index = 0;
    map = new Space **[getNumRows()];
    for (int r = 0; r < getNumRows(); r++)
    {
        map[r] = new Space *[getNumCols()];
    }
    for (int r = 0; r < getNumRows(); r++)
    {
        for (int c = 0; c < getNumCols(); c++)
        {
            map[r][c] = &getEmptySpace()[index]; //set all elements to empty
            index++;
        }
    }

    //Set key spaces
    map[0][0] = &getKeySpace()[0];
    map[0][3] = &getKeySpace()[1];
    map[4][3] = &getKeySpace()[2];

    //Set item spaces
    map[1][2] = &getItemSpace()[0];
    map[2][3] = &getItemSpace()[1];
    map[4][1] = &getItemSpace()[2];
    map[3][0] = &getItemSpace()[3];
    map[0][1] = &getItemSpace()[4];
    map[1][1] = &getItemSpace()[5];
    map[1][3] = &getItemSpace()[6];
    map[3][3] = &getItemSpace()[7];
    map[2][4] = &getItemSpace()[8];

    //Set leak spaces
    map[0][2] = &getLeakSpace()[0]; //initial leak
    map[0][2]->action();
    map[0][2]->updateSpace();
    //Remaining leak spaces to effect player after moves
    map[3][2] = &getLeakSpace()[1];
    map[2][1] = &getLeakSpace()[2];
    map[3][4] = &getLeakSpace()[3];

    //Set Exit spaces
    map[2][0] = &getLockedSpace()[0];
    map[0][4] = &getLockedSpace()[1];
    map[4][4] = &getLockedSpace()[2];

    //Set Action spaces
    map[4][0] = &getActionSpace()[0];
    getActionSpace()[0].initSpace(1);
    map[4][2] = &getActionSpace()[1];
    getActionSpace()[1].initSpace(2);
    map[1][4] = &getActionSpace()[2];
    getActionSpace()[2].initSpace(3);

    //Set borders of nullptrs so that Player cannot go off map
    for (int r = 0; r < getNumRows(); r++)
    {
        for (int c = 0; c < getNumCols(); c++)
        {
            if (r == 0)
            {
                map[r][c]->setUp(nullptr);
            }
            if (r == 4)
            {
                map[r][c]->setDown(nullptr);
            }
            if (c == 0)
            {
                map[r][c]->setLeft(nullptr);
            }
            if (c == 4)
            {
                map[r][c]->setRight(nullptr);
            }

            //Links all space pointers
            if (r != 4)
            {
                map[r][c]->setDown(map[r + 1][c]);
            }
            if (r != 0)
            {
                map[r][c]->setUp(map[r - 1][c]);
            }
            if (c != 0)
            {
                map[r][c]->setLeft(map[r][c - 1]);
            }
            if (c != 4)
            {
                map[r][c]->setRight(map[r][c + 1]);
            }
        }
    }
}

//Reallocates memory for derived spaces upon game restart
void Game::reallocSpaces()
{
    pPlayer = new Player;
    pEmptySpace = new EmptySpace[25];
    pActionSpace = new ActionSpace[3];
    pItemSpace = new ItemSpace[25];
    pKeySpace = new KeySpace[25];
    pLeakSpace = new LeakSpace[25];
    pLockedSpace = new LockedSpace[25];
}

//Deallocates all dynamically allocated objects
void Game::deallocAll()
{
    //Set all pointers to null before deleting
    for (int r = 0; r < getNumRows(); r++)
    {
        for (int c = 0; c < getNumCols(); c++)
        {
            if (map[r][c])
            {
                map[r][c] = nullptr;
                delete map[r][c];
                map[r][c] = nullptr;
            }
        }
    }
    //Deallocate array in each row
    for (int r = 0; r < getNumRows(); r++)
    {
        delete[] map[r];
    }
    //Deallocate rows
    delete[] map;

    //Delete Player and Spaces
    delete getPlayer();
    delete[] getEmptySpace();
    delete[] getActionSpace();
    delete[] getItemSpace();
    delete[] getKeySpace();
    delete[] getLeakSpace();
    delete[] getLockedSpace();
}

//Prints entire map according to bool values in each space object
void Game::printMap()
{
    //Prints top border
    for (int c = 0; c < getNumCols() + 2; c++)
    {
        cout << "=";
    }
    cout << endl;

    //Prints specific spaces based on bool values and space types
    for (int r = 0; r < getNumRows(); r++)
    {
        cout << '|'; //Prints left border

        for (int c = 0; c < getNumCols(); c++)
        {
            if (map[r][c] != nullptr)
            {
                if (map[r][c]->getBoolPlayerSpace() == true)
                {
                    cout << 'X';
                }
                else if (map[r][c]->getBoolLeak() == true && map[r][c]->getTraversal() == true && map[r][c]->getInspection() == true)
                {
                    cout << '!';
                }
                else if (map[r][c]->getSpaceType() == locked && map[r][c]->getTraversal() == true && map[r][c]->getInspection() == true)
                {
                    cout << 'E';
                }
                else if (map[r][c]->getSpaceType() == tunnel && map[r][c]->getTraversal() == true)
                {
                    cout << 'T';
                }
                else if (map[r][c]->getSpaceType() == hatch && map[r][c]->getTraversal() == true)
                {
                    cout << 'H';
                }
                else if (map[r][c]->getSpaceType() == door && map[r][c]->getTraversal() == true)
                {
                    cout << 'D';
                }
                else if (map[r][c]->getSpaceType() == unlocked && map[r][c]->getTraversal() == true)
                {
                    cout << 'O';
                }
                else if (map[r][c]->getSpaceType() == firstAid && map[r][c]->getTraversal() == true && map[r][c]->getInspection() == true)
                {
                    cout << '+';
                }
                else if (map[r][c]->getSpaceType() == plug && map[r][c]->getTraversal() == true && map[r][c]->getInspection() == true)
                {
                    cout << 'p';
                }
                else if (map[r][c]->getSpaceType() == key && map[r][c]->getTraversal() == true && map[r][c]->getInspection() == true)
                {
                    cout << 'k';
                }
                else if (map[r][c]->getTraversal() == false)
                {
                    cout << ' ';
                }
                else if (map[r][c]->getTraversal() == true)
                {
                    cout << '.';
                }
            }
            else
            {
                cout << ' ';
            }
        }

        cout << '|'; //Prints right border
        cout << endl;
    }

    //Prints bottom border
    for (int c = 0; c < getNumCols() + 2; c++)
    {
        cout << "=";
    }
    cout << endl;
}

//Main play function that runs the main game, displays menu, prints map
void Game::play()
{
    //Displays intro
    displayChapter0();
    //Prints initial map
    printMap();

    //Runs game while player is not dead and player has not escaped
    while (getPlayer()->getHealth() > 0 && getEscape() == false)
    {
        displayPlayMenu();
        printMap();
    }

    //Runs ending player earned, resets map
    ending();
}

//Displays introduction of the game
void Game::displayChapter0()
{
    cout << "I wake up." << endl;
    sleep2Sec();
    cout << "It's dark in here." << endl;
    sleep2Sec();
    cout << "Where am I?" << endl;
    sleep2Sec();

    cout << "*drip*..." << endl;
    sleep1Sec();
    cout << "*drip*..." << endl;
    sleep1Sec();
    cout << "*drip*..." << endl;
    sleep2Sec();

    cout << "There’s something leaking from one of the walls." << endl;
    sleep2Sec();
    cout << "I’ve got a bad feeling about that leak. I need to get out of here." << endl;
    sleep2Sec();

    //Goal for the player displayed
    cout << "There must be a way to stop the leak or escape. Maybe there's a key? Something I can use to plug the leak?" << endl;
    sleep2Sec();

    cout << "What should I do?" << endl;
    sleep2Sec();
}

//Ending function to display ending player earned, resets map for next game if played
void Game::ending()
{
    //Display survival/escape ending
    if (getEscape() == true)
    {
        sleep1Sec();
        cout << "You gasp and your lungs fill with fresh air." << endl;
        sleep2Sec();
        cout << "You turn around and see a sinking ship labeled: \"1    6    2\"." << endl;
        sleep2Sec();
        cout << "You escaped." << endl;
        sleep1Sec();

        //Display special message for players who complete all objectives
        if (getLeaks() == 0)
        {
            sleep1Sec();
            cout << "(One statement to sum up the quarter: Kudos for plugging all of those leaks!)" << endl;
            sleep1Sec();
        }

        cout << "Thank you for playing!" << endl;
        sleep1Sec();
    }
    //Display death/bad ending
    else if (getPlayer()->getHealth() <= 0)
    {
        sleep2Sec();
        cout << "It's dark." << endl;
        sleep2Sec();
        cout << "You didn't make it." << endl;
        sleep1Sec();
    }

    //Reset moves and leaks
    setMoves(0);
    setLeaks(1);

    //Reset map, spaces, objects
    getCurrentSpace()->setBoolPlayerspace(false);
    printMap();
    getPlayer()->setHealth(100);
    deallocAll();
    reallocSpaces();
    allocMap();
    setCurrentSpace(map[2][2]);
    setEscape(false);
}

//Adds leaks that adjust player health, adjusts map
void Game::addLeaks()
{
    //Adds new leak at 3, 2 on map, displays message
    if (getMoves() == 7)
    {
        map[3][2]->action();
        map[3][2]->updateSpace();
        setLeaks(getLeaks() + 1);
        sleep2Sec();
        cout << "*PSSSHHSTTT*" << endl;
        sleep2Sec();
        cout << "That sounds like another leak. I need to hurry." << endl;
        sleep1Sec();
    }
    //Adds new leak at 2, 1 on map, displays message
    if (moves == 14)
    {
        map[2][1]->action();
        map[2][1]->updateSpace();
        setLeaks(getLeaks() + 1);
        sleep2Sec();
        cout << "*PSSSHHSTTT*" << endl;
        sleep2Sec();
        cout << "Another leak. I'm not safe yet." << endl;
        sleep1Sec();
    }
    //Adds new leak at 3, 4 on map, displays message
    if (moves == 21)
    {
        map[3][4]->action();
        map[3][4]->updateSpace();
        setLeaks(getLeaks() + 1);
        sleep2Sec();
        cout << "*PSSSHHSTTT*" << endl;
        sleep2Sec();
        cout << "Yet another. I need to get out of here." << endl;
        sleep1Sec();
    }
}

//Allows user to inspect room to update map, pickup items, take chances on actionSpaces
void Game::inspectRoom()
{
    //Inspected already, item picked up
    if (getCurrentSpace()->getInspection() == true)
    {
        sleep1Sec();
        cout << "I've already inspected this room. I should move on. " << endl;
        sleep2Sec();
    }
    else
    {
        //Displays space description and clues
        cout << getCurrentSpace()->getDescrip() << endl;
        sleep1Sec();
        cout << getCurrentSpace()->getClues() << endl;
        sleep1Sec();

        //For special spaces that are not item spaces, set inspection and moves accordingly
        if (getCurrentSpace()->getSpaceType() == empty ||
            getCurrentSpace()->getSpaceType() == leakSpace ||
            getCurrentSpace()->getSpaceType() == locked)
        {
            setMoves(getMoves() + 1);
            getCurrentSpace()->setInspection(true);
        }

        //For item or action spaces, run functions to determine inspection and moves
        if (getMoves() > 0)
        {
            pickupItem();
            runActions();
        }
    }
}

//Runs actions for actionSpaces based on space type set by initSpace() in ActionSpace class
void Game::runActions()
{
    if (getCurrentSpace()->getSpaceType() == hatch ||
        getCurrentSpace()->getSpaceType() == tunnel ||
        getCurrentSpace()->getSpaceType() == door)
    {
        //Runs menu
        sleep1Sec();
        actionMenu();
    }
}

//Action menu for ActionSpaces, allows user to interact
void Game::actionMenu()
{
    int menuChoice;
    cout << "Take your chances? " << endl;
    cout << "Enter 1 for yes, 2 for no." << endl;
    //Validate user choice to proceed or back out of interacting
    menuChoice = validateInt(9);

    //Gets results if interacting
    if (menuChoice == 1)
    {
        actionResult();
    }
    //Displays exit message if not interacting
    else if (menuChoice == 2)
    {
        sleep1Sec();
        cout << "I'd rather not. There must be another way out. Clock's ticking." << endl;
        sleep2Sec();
    }
}

//Rolls 50/50 chance for success, gets appropriate actionSpace results
void Game::actionResult()
{
    //Gets 50/50 chance
    chances currentChance = getCurrentSpace()->getChance();

    //Returns action success or failure
    actionSuccess(currentChance);

    //Updates moves and inspection of space
    setMoves(getMoves() + 1);
    getCurrentSpace()->setInspection(true);
}

//Determines result of action depending on spaceType. Takes a enum chances as a parameter to determine success
//or failure.
void Game::actionSuccess(chances currentChance)
{
    //Runs success results for each space type
    if (currentChance == success)
    {
        if (getCurrentSpace()->getSpaceType() == hatch)
        {
            hatchSuccess();
        }
        else if (getCurrentSpace()->getSpaceType() == tunnel)
        {
            tunnelSuccess();
        }
        else if (getCurrentSpace()->getSpaceType() == door)
        {
            doorSuccess();
        }
    }
    //Runs failure result for each space type
    else if (currentChance == failure)
    {
        if (getCurrentSpace()->getSpaceType() == hatch)
        {
            hatchFailure();
        }
        else if (getCurrentSpace()->getSpaceType() == tunnel)
        {
            tunnelFailure();
        }
        else if (getCurrentSpace()->getSpaceType() == door)
        {
            doorFailure();
        }
    }
}

//Displays hatch actionSpace intro
void Game::hatchIntro()
{
    sleep1Sec();
    cout << "You feel around and find a stool nearby. " << endl;
    sleep2Sec();
    cout << "You set it directly underneatch the hatch in the ceiling. " << endl;
    sleep2Sec();
    cout << "You step on the stool and reach for the hatch." << endl;
    sleep2Sec();
    cout << "You can reach the hatch with your fingertips now." << endl;
    sleep2Sec();
    cout << "The stool wobbles with every slight movement you make." << endl;
    sleep2Sec();
    cout << "You begin to crank. Once. Twice. Three times. " << endl;
    sleep2Sec();
}

//Displays tunnel actionSpace intro
void Game::tunnelIntro()
{
    sleep1Sec();
    cout << "You peer into the darkness, straining your eyes to see. " << endl;
    sleep2Sec();
    cout << "You feel around the edges of the tunnel. It gets narrower as you reach deeper. " << endl;
    sleep2Sec();
    cout << "You take a step in. Then another. And another." << endl;
    sleep2Sec();
    cout << "Step after step you creep along the edge of the tunnel. Step after step, the tunnel gets narrower." << endl;
    sleep2Sec();
    cout << "You continue inching your way down the tunnel. " << endl;
    sleep2Sec();
    cout << "It continues narrowing until the other wall is barely an inch from your face. " << endl;
    sleep2Sec();
    cout << "Step by step you inch towards the other side. " << endl;
    sleep2Sec();
    cout << "It feels like you can't breathe. " << endl;
    sleep2Sec();
    cout << "You're enveloped in water from the leaks, and walls on all sides. " << endl;
    sleep2Sec();
}

//Displays door actionSpace intro
void Game::doorIntro()
{
    sleep1Sec();
    cout << "The door is heavier than you thought. You wrap your hand around the cold, wet metal." << endl;
    sleep2Sec();
    cout << "You pull. Nothing." << endl;
    sleep2Sec();
    cout << "You try again. Harder this time." << endl;
    sleep2Sec();
    cout << "The door starts to open, a half-inch for now." << endl;
    sleep2Sec();
    cout << "You pull back on the handle as hard as you can. " << endl;
    sleep2Sec();
    cout << "*BANG* " << endl;
    sleep2Sec();
    cout << "It opens, all at once, flinging you backwards. " << endl;
    sleep1Sec();
}

//Displays hatch actionSpace success, player adds item if backpack is not full
void Game::hatchSuccess()
{
    hatchIntro();
    cout << "*EERRRRSCK* ..." << endl;
    sleep2Sec();
    cout << "The hatch is open!" << endl;
    sleep2Sec();
    cout << "Peering into the darkness you strain your eyes. ...The path beyond the hatch doesn't lead anywhere. " << endl;
    sleep2Sec();
    cout << "You see a sign inside that's labeled \"STORAGE\"." << endl;
    sleep1Sec();
    cout << "There's something on the ground." << endl;
    sleep1Sec();

    //Gets item if player has inventory space
    if (getPlayer()->getItemCount() <= 3)
    {
        cout << "You pickup a thermos of coffee and head back out of the hatch. " << endl;
        sleep2Sec();
        getPlayer()->addItem(getCurrentSpace()->getItem());
    }
    //Else, player does not add anything to their inventory
    else
    {
        cout << "It's an old thermos of coffee. " << endl;
        sleep2Sec();
        cout << "..Was, an old thermos of coffee. Looks like it's been spilled." << endl;
        sleep2Sec();
    }
}

//Displays hatch actionSpace failure, player falls and loses 10 health
void Game::hatchFailure()
{
    hatchIntro();
    cout << "*EERRRRSCK* ..." << endl;
    sleep2Sec();
    cout << "The hatch is open!" << endl;
    sleep2Sec();
    cout << "--as it opens, the stool wobbles and tips over." << endl;
    sleep2Sec();
    cout << "You fall over with a crash as your fingers slip from the hatch." << endl;
    sleep2Sec();
    cout << "*SHHCHSSCH*" << endl;
    sleep2Sec();
    cout << "Luckily, thanks to the leaks, your fall is mitigated by the water. " << endl;
    sleep2Sec();
    cout << "Unluckily, you hit your head and pass out for a few moments." << endl;
    sleep2Sec();

    //Player loses health for failure
    getPlayer()->setHealth(getPlayer()->getHealth() - 10);
}

//Displays tunnel actionSpace success, player escapes and wins the game
void Game::tunnelSuccess()
{
    tunnelIntro();
    cout << "All of a sudden, your right leg finds free space. Then your right arm." << endl;
    sleep2Sec();
    cout << "You exit into an open room. You see a beam of light." << endl;
    sleep2Sec();
    cout << "You rush through the rising water towards the light." << endl;

    //Player escapes and wins upon success roll
    setEscape(true);
}

//Displays tunnel actionSpace failure, player dies and loses the game
void Game::tunnelFailure()
{
    tunnelIntro();
    cout << "You keep inching your way toward the opposite side." << endl;
    sleep2Sec();
    cout << "You keep inching, or you think you are. It's difficult to tell from the water." << endl;
    sleep2Sec();
    cout << "You reach with your right foot and your right hand, but you're no longer moving." << endl;
    sleep2Sec();
    cout << "... You're stuck. " << endl;
    sleep2Sec();
    cout << "You try to go back, but it's no use." << endl;
    sleep2Sec();
    cout << "Your arms strain to the left. To the right. No luck. " << endl;
    sleep2Sec();
    cout << "The water continues rising, until you're struggling to keep your mouth above water. " << endl;
    sleep2Sec();

    //Player loses and dies upon failure roll
    getPlayer()->setHealth(0);
}

//Displays door actionSpace success, player goes back to map 2,2 the starting position
void Game::doorSuccess()
{
    doorIntro();
    cout << "You squint your eyes. Darkness." << endl;
    sleep2Sec();
    cout << "You walk through some hallways for a seemingly long time." << endl;
    sleep2Sec();
    cout << "You finally exit into an open room. It feels strangely familiar, even in near-total darkness." << endl;
    sleep2Sec();

    //Transports player back to starting position, sets current space appropriately
    getCurrentSpace()->setBoolPlayerspace(false);
    setCurrentSpace(map[2][2]);
}

//Displays door actionSpace failure, adds a leak that player cannot stop
void Game::doorFailure()
{
    doorIntro();
    cout << "Water begins rushing in. The door is now stuck open from the water pressure." << endl;
    sleep2Sec();
    cout << "I don't think I can plug this leak... I need to hurry. I've made a mistake." << endl;
    sleep2Sec();

    //Adds a leak that player cannot stop
    setLeaks(getLeaks() + 1);
}

//Displays item menu for player to use item
void Game::itemMenu()
{
    int menuChoice;

    //If player has items, use item selected
    if (getPlayer()->getItemCount() > 0)
    {
        displayItems();
        cout << "Please enter the corresponding number of the item you wish to use. " << endl;
        menuChoice = validateInt(validateItemChoice());
        useItem(menuChoice - 1);
    }
    //Empty backpack, player has no items. Display message
    else
    {
        sleep1Sec();
        cout << "Empty. I should look around." << endl;
        sleep1Sec();
    }
}

//Displays items in players backpack vector
void Game::displayItems()
{
    //Shows capacity of Player backpack
    cout << "Current Capacty: " << getPlayer()->getItemCount() << "/3" << endl;
    cout << "Items: ";

    //If player has items, display all items in backpack vector
    if (getPlayer()->getItemCount() > 0)
    {
        for (int i = 0; i < getPlayer()->getItemCount(); i++)
        {
            if (getPlayer()->backpack.at(i) != nullptr)
            {
                cout << "(" << i + 1 << ") " << getPlayer()->backpack.at(i)->getName() << "   ";
            }
        }
        cout << endl;
    }
    //Output empty message if player has no items
    else if (getPlayer()->getItemCount() == 0)
    {
        cout << "Empty." << endl;
    }
}

//Picks up item based on space type that Player is currently on
void Game::pickupItem()
{
    if (getCurrentSpace()->getSpaceType() == firstAid ||
        getCurrentSpace()->getSpaceType() == plug ||
        getCurrentSpace()->getSpaceType() == junk ||
        getCurrentSpace()->getSpaceType() == key)
    {
        //Displays item description
        sleep1Sec();
        cout << getCurrentSpace()->getItem()->getDescrip() << endl;
        sleep2Sec();
        
        //Adds item to players backpack vector if not at capacity.
        if (getPlayer()->getItemCount() < 3)
        {
            cout << "You add the item to your backpack." << endl;
            getPlayer()->addItem(getCurrentSpace()->getItem());
            
            //Adds move to counter and set space to inspected
            setMoves(getMoves() + 1);
            getCurrentSpace()->setInspection(true);
        }
        else
        {
            //Outputs full backpack message, player can still pickup item if an item is used and space is inspected again
            sleep1Sec();
            cout << "My backpack is full. I should use something before picking this up. " << endl;
            sleep1Sec();
            return;
        }
    }
}

//Validates item choice of the user, sets key for validateInt() function for appropriate range of menu values
int Game::validateItemChoice()
{
    int menuChoice2;
    int localKey;
    if (getPlayer()->getItemCount() == 1)
    {
        localKey = 12;
    }
    if (getPlayer()->getItemCount() == 2)
    {
        localKey = 13;
    }
    if (getPlayer()->getItemCount() == 3)
    {
        localKey = 14;
    }
    return localKey;
}

//Uses item depending on item type and gets results. Takes an integer parameter to determine which item in 
//the backpack vector is used.
int Game::useItem(int keyInt)
{
    itemType itemValue;

    //Sets item to be used at backpack location selected
    itemValue = getPlayer()->backpack.at(keyInt)->action();

    //Heal value for player health restore for using firstaid
    int healVal = 10;

    //Determines outcome if player has an item to use
    if (getPlayer()->getItemCount() > 0)
    {
        //Uses first aid, restores 10 health
        if (itemValue == heal)
        {
            sleep1Sec();
            cout << "You consume the cup of coffee. You feel slightly better." << endl;
            sleep1Sec();

            //Restores health
            getPlayer()->setHealth(getPlayer()->getHealth() + healVal);
            
            //Remove item used and update vector
            updateItems(keyInt);
        }
        //Uses plug, dependent on bool leak value, decrements int leak on success
        else if (itemValue == plugItem)
        {
            sleep2Sec();
            cout << "You use the plug in the room you're currently in. " << endl;

            //If there is no leak, use item, no values are changed
            if (getCurrentSpace()->getBoolLeak() == false)
            {
                sleep2Sec();
                cout << "It is not really effective. There was no fixable leak in this room. " << endl;
                sleep1Sec();
                
                //Remove item used and update vector
                updateItems(keyInt);
            }
            //If there is a leak, plug, reduce leak count by 1
            else if (getCurrentSpace()->getBoolLeak() == true)
            {
                //Set space leak to false
                getCurrentSpace()->setBoolLeak(false);

                //Decrease leaks by 1
                setLeaks(getLeaks() - 1);

                sleep2Sec();
                cout << "You plug the leak. One less thing to worry about. " << endl;
                sleep1Sec();

                //Remove item used and update vector
                updateItems(keyInt);

                //If there are no leaks after plugging, display message
                if (getLeaks() == 0)
                {
                    sleep2Sec();
                    cout << "I think that was the last of them. It should be safe to move without worry now." << endl;
                    sleep2Sec();
                    cout << "I should find a way out. " << endl;
                    sleep1Sec();
                }
            }
        }
        //If junk item is used, update backpack vector
        else if (itemValue == junkItem)
        {
            sleep1Sec();
            cout << "You toss the trash away." << endl;
            sleep1Sec();
            cout << "It splashes somewhere in the distance, echoing in the hall." << endl;
            sleep2Sec();

            //Remove item used and update vector
            updateItems(keyInt);
        }
        //If key item is used, determine escape based on space type, update backpack vector
        else if (itemValue == keyItem)
        {
            sleep1Sec();
            cout << "You use the key in the room you're currently in. " << endl;
            sleep1Sec();

            //If space type is correct, user escapes
            if (getCurrentSpace()->getSpaceType() == locked)
            {
                //Swaps locked spacetype to unlocked
                getCurrentSpace()->action();

                cout << "There's an old door with a copper crank and a rusted lock. " << endl;
                sleep2Sec();
                cout << "You struggle to fit the key into the lock, jamming it forcefully until it scratches its way in." << endl;
                sleep2Sec();
                cout << "You turn the key with a lot of pressure to the right. Then to the left. " << endl;
                sleep2Sec();
                cout << "The key strains, bending slightly." << endl;
                sleep2Sec();
                cout << "*click*" << endl;
                sleep2Sec();
                cout << "The door unlocks." << endl;
                sleep2Sec();

                //Remove item used and update vector
                updateItems(keyInt);

                //User wins the game
                setEscape(true);
            }
            //If the space is not able to use a key, player loses key
            else
            {
                cout << "The key slips out of your hands. " << endl;
                sleep2Sec();
                cout << "You splash your hands in the muck while the the water level continues to rise. " << endl;
                sleep2Sec();
                cout << "You can't find it. " << endl;
                sleep1Sec();

                //Remove item used and update vector
                updateItems(keyInt);
            }
        }
    }
    //Update move count after using item
    setMoves(getMoves() + 1);
}

//Updates backpack vector after player uses item. Takes an integer value to determine which item should be erased from the 
//vector.
void Game::updateItems(int keyInt)
{
    //If 3 items and item 1 is used, erase it
    if (keyInt == 0 && getPlayer()->getItemCount() > 2)
    {
        getPlayer()->backpack.erase(getPlayer()->getIt());
    }
    //If 3 items and item 2 is used, increment iterator and erase it
    else if (keyInt == 1 && getPlayer()->getItemCount() > 2)
    {
        
        advance(getPlayer()->it, 1);    //Increments iterator to item 2
        getPlayer()->backpack.erase(getPlayer()->getIt());
    }
    //If 3 items and item 3 is used, increment iterator and erase it
    else if (keyInt == 2 && getPlayer()->getItemCount() > 2)
    {
        advance(getPlayer()->it, 2);    //Increments iterator to item 3
        getPlayer()->backpack.erase(getPlayer()->getIt());
    }
    //If two items and item 1 is used, erase it
    else if (keyInt == 0 && getPlayer()->getItemCount() > 1)
    {
        getPlayer()->backpack.erase(getPlayer()->getIt());
    }
    //If two items and item 2 is used, increment iterator and erase it
    else if (keyInt == 1 && getPlayer()->getItemCount() > 1)
    {
        advance(getPlayer()->it, 1);    //Increments iterator to item 2
        getPlayer()->backpack.erase(getPlayer()->getIt());
    }
    //If 1 item and it is used, erase it
    else if (keyInt == 0 && getPlayer()->getItemCount() == 1)
    {
        getPlayer()->backpack.erase(getPlayer()->getIt());
    }

    //Reset position of iterator in Player class
    getPlayer()->it = getPlayer()->backpack.begin();

    //Decrement item count after use
    getPlayer()->setItemCount(getPlayer()->getItemCount() - 1);
}

//Adjusts player health depending on the number of leaks present
void Game::adjustHealth()
{
    //Decrement health based on number of leaks
    getPlayer()->setHealth(getPlayer()->getHealth() - (5 * getLeaks()));

    //Determines and sets health message
    determineHealth();

    //Displays health message
    sleep1Sec();
    cout << getHealth() << endl;
    sleep1Sec();
}

//Determines health message to be set
void Game::determineHealth()
{
    if (getPlayer()->getHealth() <= 10)
    {
        setHealth("Please.. someone-- *gasp* .. *grlppbpl*");
    }
    else if (getPlayer()->getHealth() <= 20)
    {
        setHealth("It's up to my neck.");
    }
    else if (getPlayer()->getHealth() <= 40)
    {
        setHealth("It's up to my chest.");
    }
    else if (getPlayer()->getHealth() <= 60)
    {
        setHealth("It's at my knees.");
    }
    else if (getPlayer()->getHealth() <= 80)
    {
        setHealth("It's at my ankles.");
    }
    else if (getPlayer()->getHealth() <= 100)
    {
        setHealth("The water's only by my feet. For now.");
    }
    else if (getPlayer()->getHealth() >= 100)
    {
        setHealth("I'm feeling well.");
    }
}

//Sleeps for 1 sec
void Game::sleep1Sec()
{
    usleep(1000000);
}

//Sleeps for 2 secs
void Game::sleep2Sec()
{
    usleep(2000000);
}

//Moves player on map accordingly, sets bool values to update printMap()
void Game::move()
{
    int moveChoice = 0;
    //Display move choices for user
    displayMoveChoices();

    //Validates move key so that appropriate choice values can be validated
    moveChoice = validateInt(validateMoveKey());

    //Moves player up
    if (moveChoice == 1)
    {
        getCurrentSpace()->setBoolPlayerspace(false);
        getCurrentSpace()->setTraversal(true);
        setCurrentSpace(getCurrentSpace()->getUp());
        getCurrentSpace()->setBoolPlayerspace(true);
    }
    //Moves player down
    else if (moveChoice == 2)
    {
        getCurrentSpace()->setBoolPlayerspace(false);
        getCurrentSpace()->setTraversal(true);
        setCurrentSpace(getCurrentSpace()->getDown());
        getCurrentSpace()->setBoolPlayerspace(true);
    }
    //Moves player left
    else if (moveChoice == 3)
    {
        getCurrentSpace()->setBoolPlayerspace(false);
        getCurrentSpace()->setTraversal(true);

        setCurrentSpace(getCurrentSpace()->getLeft());
        getCurrentSpace()->setBoolPlayerspace(true);
    }
    //Moves player right
    else if (moveChoice == 4)
    {
        getCurrentSpace()->setBoolPlayerspace(false);
        getCurrentSpace()->setTraversal(true);
        setCurrentSpace(getCurrentSpace()->getRight());
        getCurrentSpace()->setBoolPlayerspace(true);
    }

    //Increments move count
    setMoves(getMoves() + 1);
}

//Displays move choices based on nullptr values around current space
void Game::displayMoveChoices()
{
    if (getCurrentSpace()->getUp() != nullptr)
    {
        cout << "Enter 1 to move up." << endl;
    }
    if (getCurrentSpace()->getDown() != nullptr)
    {
        cout << "Enter 2 to move down." << endl;
    }
    if (getCurrentSpace()->getLeft() != nullptr)
    {
        cout << "Enter 3 to move left." << endl;
    }
    if (getCurrentSpace()->getRight() != nullptr)
    {
        cout << "Enter 4 to move right." << endl;
    }
}

//Determines key to be used in validateInt based on nullptrs around current space, returns an integer value
int Game::validateMoveKey()
{
    int localKey = 0;
    
    //Player is in upper left corner
    if (getCurrentSpace()->getUp() == nullptr && getCurrentSpace()->getLeft() == nullptr)
    {
        localKey = 1;
    }
    //Player is in upper right corner
    else if (getCurrentSpace()->getUp() == nullptr && getCurrentSpace()->getRight() == nullptr)
    {
        localKey = 2;
    }
    //Player is in bottom right corner
    else if (getCurrentSpace()->getDown() == nullptr && getCurrentSpace()->getLeft() == nullptr)
    {
        localKey = 3;
    }
    //Player is in bottom left corner
    else if (getCurrentSpace()->getDown() == nullptr && getCurrentSpace()->getRight() == nullptr)
    {
        localKey = 4;
    }
    //Player is on the top edge, but not a corner
    else if (getCurrentSpace()->getUp() == nullptr)
    {
        localKey = 5;
    }
    //Player is on the bottom edge, but not a corner
    else if (getCurrentSpace()->getDown() == nullptr)
    {
        localKey = 6;
    }
    //Player is on the left edge, but not a corner
    else if (getCurrentSpace()->getLeft() == nullptr)
    {
        localKey = 7;
    }
    //Player is on the right edge, but not a corner
    else if (getCurrentSpace()->getRight() == nullptr)
    {
        localKey = 8;
    }
    return localKey;
}

//Validates user integer input for a variety of functinos in Game. Takes an integer parameter to
//determine the range of acceptable inputs from the user. Returns an integer as a choice for
//corresponding functions.
int Game::validateInt(int keyInt)
{
    //Float validation adapted from: https://www.quora.com/How-do-I-check-if-a-number-is-float-on-C++
    double choice = 0.0;
    int floatTest = 0;

    string message;
    message = "I can't do that. Let's try again.";

    int upperLim = 4;
    int lowerLim = 1;
    int lim1 = 0;
    int lim2 = 0;
    int lim3 = 0;

    //For upper left corner in move() function
    if (keyInt == 1)
    {
        lim1 = 1;
        lim2 = 3;
        lim3 = 0;
    }
    //For upper right corner in move()function
    else if (keyInt == 2)
    {
        lim1 = 1;
        lim2 = 4;
        lim3 = 0;
    }
    //For lower left corner in move()function
    else if (keyInt == 3)
    {
        lim1 = 2;
        lim2 = 3;
    }
    //For lower right corner in move()function
    else if (keyInt == 4)
    {
        lim1 = 2;
        lim2 = 4;
    }
    //For top edge in move() function
    else if (keyInt == 5)
    {
        lim1 = 1;
    }
    //For bottom edge in move() function
    else if (keyInt == 6)
    {
        lim1 = 2;
    }
    //For left edge in move() function
    else if (keyInt == 7)
    {
        lim1 = 3;
    }
    //For right edge in move() function
    else if (keyInt == 8)
    {
        lim1 = 4;
    }
    //For menu options 1 and 2, yes and no
    else if (keyInt == 9)
    {
        lim1 = 3;
        lim2 = 4;
    }
    //For range of menu options 1 - 4
    else if (keyInt == 10)
    {
        upperLim = 4;
        lowerLim = 1;
    }
    //For range of menu options, 1 - 5
    else if (keyInt == 11)
    {
        upperLim = 5;
        lowerLim = 1;
    }
    //For choice 1 only
    else if (keyInt == 12)
    {
        upperLim = 1;
        lowerLim = 1;
    }
    //For choice 1 and 2
    else if (keyInt == 13)
    {
        upperLim = 2;
        lowerLim = 1;
    }
    //For choice 1 - 3
    else if (keyInt == 14)
    {
        upperLim = 3;
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
        if (((floatTest % 100000000) > 0) || choice == lim3 || choice == lim2 || choice == lim1 || choice < lowerLim || choice > upperLim)
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
