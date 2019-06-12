#ifndef SPACE_HPP
#define SPACE_HPP
#include <string>
#include "item.hpp"
#include "spaceType.hpp"
#include "chances.hpp"

class Space
{
private:
    //Space pointers to link all spaces
    Space *up;
    Space *down;
    Space *left;
    Space *right;

    //Item pointer to store item for itemSpaces
    Item *pItem;

    //Descriptions of each space
    std::string description;
    std::string clues;

    //Bool values to track player interactions
    bool valid;
    bool item;
    bool leak;
    bool traversed;
    bool playerSpace;
    bool inspected;

    //Stores type of space
    spaceType type;

public:
    Space()
    {
    }

    //Pure virtual functions for action, chance, update
    virtual void action() = 0;
    virtual chances getChance() = 0;
    virtual void updateSpace() = 0;

    //Getters for pointers
    virtual Space *getUp()
    {
        return up;
    }
    virtual Space *getDown()
    {
        return down;
    }
    virtual Space *getLeft()
    {
        return left;
    }
    virtual Space *getRight()
    {
        return right;
    }
    virtual Item *getItem()
    {
        return pItem;
    }

    //Setters for pointers
    virtual void setItem(Item *pItem)
    {
        this->pItem = pItem;
    }
    virtual void setUp(Space *up)
    {
        this->up = up;
    }
    virtual void setDown(Space *down)
    {
        this->down = down;
    }
    virtual void setLeft(Space *left)
    {
        this->left = left;
    }
    virtual void setRight(Space *right)
    {
        this->right = right;
    }

    //Getters for other variables
    virtual std::string getDescrip()
    {
        return description;
    }
    virtual std::string getClues()
    {
        return clues;
    }
    virtual bool getBoolValid()
    {
        return valid;
    }
    virtual bool getBoolItem()
    {
        return item;
    }
    virtual bool getBoolLeak()
    {
        return leak;
    }
    virtual bool getBoolPlayerSpace()
    {
        return playerSpace;
    }
    virtual bool getTraversal()
    {
        return traversed;
    }
    virtual bool getInspection()
    {
        return inspected;
    }
    virtual spaceType getSpaceType()
    {
        return type;
    }

    //Setters for other variables
    virtual void setDescrip(std::string description)
    {
        this->description = description;
    }
    virtual void setClues(std::string clues)
    {
        this->clues = clues;
    }
    virtual void setBoolValid(bool valid)
    {
        this->valid = valid;
    }
    virtual void setBoolItem(bool item)
    {
        this->item = item;
    }
    virtual void setBoolLeak(bool leak)
    {
        this->leak = leak;
    }
    virtual void setBoolPlayerspace(bool playerSpace)
    {
        this->playerSpace = playerSpace;
    }
    virtual void setTraversal(bool traversed)
    {
        this->traversed = traversed;
    }
    virtual void setInspection(bool inspected)
    {
        this->inspected = inspected;
    }
    virtual void setSpaceType(spaceType type)
    {
        this->type = type;
    }

    virtual ~Space()
    {
    }
};

#endif