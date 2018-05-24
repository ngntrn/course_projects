/*****************************************************************************
 ** Program Filename: Road.hpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class declaration file for Road
 *****************************************************************************/

#ifndef ROAD_HPP
#define ROAD_HPP

#include "Space.hpp"

class Road : public Space
{

public:
    Road() : Space() {};
    void entryMsg();
    char move();
  
};

#endif
