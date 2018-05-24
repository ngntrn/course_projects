/*****************************************************************************
 ** Program Filename: House.hpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class declaration file for House
 *****************************************************************************/

#ifndef HOUSE_HPP
#define HOUSE_HPP

#include "Space.hpp"

class House : public Space
{
private:
    int numVisits;
    
public:
    House();
    void entryMsg();
    char move();
    int getNumVisits();
};

#endif
