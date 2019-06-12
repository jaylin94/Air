#ifndef ITEM_HPP
#define ITEM_HPP
#include <iostream>
#include <string>
#include "itemType.hpp"

//Item base class for all item types
class Item
{
private:
    //Name and description for items
    std::string description;
    std::string name;

public:
    Item()
    {
    }

    //Pure virtual function for item actions
    virtual itemType action() = 0;

    //Getters
    virtual std::string getDescrip()
    {
        return description;
    }
    virtual std::string getName()
    {
        return name;
    }

    //Setters
    virtual void setDescrip(std::string description)
    {
        this->description = description;
    }
    virtual void setName(std::string name)
    {
        this->name = name;
    }

    virtual ~Item()
    {
    }
};

#endif