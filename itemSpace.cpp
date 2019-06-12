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
#include "itemSpace.hpp"
using std::cin;
using std::cout;
using std::endl;

ItemSpace::ItemSpace()
{
    //Sets space type default until initSpace is called to generate specific item object/type
    setSpaceType(itemSpace);
    //Initializes specific item object and type
    initSpace();

    //Sets default bool values to track item spaces
    setTraversal(false);
    setInspection(false);
    setBoolItem(true);
    setBoolLeak(false);
    setBoolPlayerspace(false);
    setBoolValid(true);
    setDescrip("There's something here.");
}

//Initializes spaces according to randomly generated item type/object.
//Sets space type, item object, clues
void ItemSpace::initSpace()
{
    int itemType;
    //Generates random value to determine object type
    itemType = (rand() % 3) + 1;
    if (itemType == 1)
    {
        setSpaceType(firstAid);
        setItem(&firstAid1);
        setClues("There's a lukewarm thermos of coffee. You take a sip.");
    }
    else if (itemType == 2)
    {
        setSpaceType(plug);
        setItem(&plugItem1);
        setClues("It's a plastic package. The label says: \"QUICKPLUG: Hydraulic Cement\".");
    }
    else if (itemType == 3)
    {
        //Rerolls last item type so that more plugs are generated for the user to use.
        itemType = (rand() % 2) + 1;
        if (itemType == 1)
        {
            setSpaceType(junk);
            setItem(&junkItem1);
            setClues("Just some trash. Wet trash.");
        }
        else if (itemType == 2)
        {
            setSpaceType(plug);
            setItem(&plugItem1);
            setClues("It's a plastic package. The label says: \"QUICKPLUG: Hydraulic Cement\".");
        }
    }
}
