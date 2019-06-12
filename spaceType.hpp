#ifndef SPACETYPE_HPP
#define SPACETYPE_HPP

//Enum values for type of space
enum spaceType
{
    //normal spaces
    empty = 1,
    itemSpace,
    actionSpace,
    //item spaces
    firstAid,
    plug,
    key,
    junk,
    //special spaces
    leakSpace,
    locked,
    unlocked,
    //action spaces
    hatch,
    tunnel,
    door

};

#endif