/*****************************************************************************
 ** Program Filename: Barn.hpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class declaration file for Barn
 *****************************************************************************/

#ifndef BARN_HPP
#define BARN_HPP

#include "Space.hpp"
#include "Alien.hpp"

class Barn : public Space
{
public:
    Barn() : Space() {};
    void entryMsg();
    char move();
};

#endif 
