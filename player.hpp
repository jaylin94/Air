#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <vector>
#include "item.hpp"
#include "firstAid.hpp"
#include "space.hpp"

//Player class to store player health, item container, item count
class Player
{
private:
    int health;
    int itemCount;

public:
    //Vector of item pointers to store items, iterator to adjust vector accordingly when items are used
    std::vector<Item *> backpack;
    std::vector<Item *>::iterator it;

    Player()
    {
        //Sets default values for Player class
        initBackpack();
        setHealth(100);
        setItemCount(0);
        //Sets iterator to first object in the backpack
        it = backpack.begin();
    }

    //Initializes backpack to have 3 nullptrs
    void initBackpack();
    //Adds items to the backpack
    void addItem(Item *pItem);

    //Getters
    std::vector<Item *>::iterator getIt()
    {
        return it;
    }
    int getItemCount()
    {
        return itemCount;
    }
    int getHealth()
    {
        return health;
    }

    //Setters
    void setItemCount(int itemCount)
    {
        this->itemCount = itemCount;
    }
    void setHealth(int health)
    {
        this->health = health;
    }

    ~Player()
    {
    }
};

#endif