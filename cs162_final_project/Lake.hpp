/*****************************************************************************
 ** Program Filename: Lake.hpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class declaration file for Lake
 *****************************************************************************/

#ifndef LAKE_HPP
#define LAKE_HPP

#include <iostream>
#include "Space.hpp"

class Lake : public Space
{
public:
    Lake() : Space() {};
    void entryMsg();
    char move();
};


#endif 
