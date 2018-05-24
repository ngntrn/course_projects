/*****************************************************************************
 ** Program Filename: Garden.hpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class declaration file for Garden
 *****************************************************************************/

#ifndef GARDEN_HPP
#define GARDEN_HPP

#include "Space.hpp"

class Garden : public Space
{
public:
    Garden() : Space() { };
    void entryMsg();
    char move();
    
};

#endif
