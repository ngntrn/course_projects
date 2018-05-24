/*****************************************************************************
 ** Program Filename: Treehouse.hpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class declaration file for Treehouse
 *****************************************************************************/


#ifndef TREEHOUSE_HPP
#define TREEHOUSE_HPP

#include <iostream>
#include "Space.hpp"

class Treehouse : public Space
{

public:
    void entryMsg();
    char move();
  
};

#endif 
