/*****************************************************************************
 ** Program Filename: Boat.hpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class declaration file for Boat
 *****************************************************************************/

#ifndef BOAT_HPP
#define BOAT_HPP

#include "Space.hpp"

class Boat : public Space
{
public:
    Boat() : Space() {};
    void entryMsg();
    char move();
};

#endif 
