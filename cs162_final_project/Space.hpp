/*****************************************************************************
 ** Program Filename: Space.hpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class declaration file for Space
 *****************************************************************************/


#include "utilities.hpp" 
#include "Alien.hpp"

#ifndef SPACE_HPP
#define SPACE_HPP

#include <iostream>
#include <string>


class Space
{
protected:
    Space *north;
    Space *east;
    Space *south;
    Space *west;

    int numVisits;
    
public:
    Space();
    virtual ~Space() {};
    
    virtual void entryMsg() =0;
    virtual char move() = 0;
    
    virtual void setPtrs(Space*, Space*, Space*, Space*);
    
    virtual Space* northPtr();
    virtual Space* eastPtr();
    virtual Space* southPtr();
    virtual Space* westPtr();
    
    virtual int getNumVisits();
    
};


#endif
