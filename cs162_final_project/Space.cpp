/*****************************************************************************
 ** Program Filename: Space.cpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class implmenetation file for Space
 *****************************************************************************/

#include "Space.hpp"

/******************************************************************************
 * Function: Space
 * Description: Constructor for Space. Sets all location pointers to NULL and
        the number of visits is initialized to zero. 
 ******************************************************************************/
Space::Space()
{
    north = NULL;
    east = NULL;
    south = NULL;
    west = NULL;
    
    numVisits = 0; 
}

/******************************************************************************
 * Function: setPtrs
 * Description: This function is used to set the location pointers for each
        Space object.
 ******************************************************************************/
void Space::setPtrs(Space* n, Space* e, Space* s, Space* w)
{
    north = n;
    east = e;
    south = s;
    west = w;
}

/******************************************************************************
 * Function: northPtr
 * Description: Returns the current Space's north pointer.
 ******************************************************************************/
Space* Space::northPtr()
{
    return north;
}

/******************************************************************************
 * Function: eastPtr
 * Description: Returns the current Space's east pointer.
 ******************************************************************************/
Space* Space::eastPtr()
{
    return east;
}

/******************************************************************************
 * Function: southPtr
 * Description: Returns the current Space's south pointer.
 ******************************************************************************/
Space* Space::southPtr()
{
    return south;
}

/******************************************************************************
 * Function: westPtr()
 * Description: Returns the current Space's west pointer.
 ******************************************************************************/
Space* Space::westPtr()
{
    return west;
}

/******************************************************************************
 * Function: getNumVisits()
 * Description: Returns the number of visits the player makes to the Space.
 ******************************************************************************/
int Space::getNumVisits()
{
    return numVisits;
}

