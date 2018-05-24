/*****************************************************************************
 ** Program Filename: House.cpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class implmenetation file for House
 *****************************************************************************/

#include "House.hpp"

/******************************************************************************
 * Function: entryMsg
 * Description: Overrides the Space entryMsg method. Displays the House's
        entry message. The message is different depending on the number of
        of visits the player has made.
 ******************************************************************************/
void House::entryMsg()
{
    if (numVisits == 0)
    {
        std::cout
        << "\nYou are now in front of the house. You try the front door, and it seems \n"
        << "to be unlocked. However, through the window, you can see a dog sleeping.\n"
        << "You contemplate whether or not you should enter the house.\n\n";
        numVisits++;
    }
    else
    {
        std::cout
        << "\nYou are now back at the house. \n\n";
        numVisits++;
    }
}
/******************************************************************************
 * Function: House
 * Description: Constructor for a House object. Initializes all the location
        pointers to NULL and the variable for number of visits to zero.
 ******************************************************************************/
House::House()
{
    north = NULL;
    east = NULL;
    south = NULL;
    west = NULL;
    
    numVisits = 0;
}

/******************************************************************************
 * Function: move
 * Description: Displays the appropriate menu options for the specific Space
        subclass. Prompts the user for a menu choice and returns the
        appropriate char which will then be used in Game::play() to perform
        the corresponding game move.
 ******************************************************************************/
char House::move()
{
    std::cout
    <<"----AT THE HOUSE----\n"
    << "What would you like to do?\n"
    << "1. Search the House. \n"
    << "2. Go somewhere else from here. \n"
    << "3. Check your backpack. \n"
    << "4. Give up. \n";
    
    int choice = getInRange(1, 4);
    
    switch (choice)
    {
        case 1: return 'L';
            break;
        case 2: return 'H';
            break;
        case 3: return 'B';
            break;
        case 4: return 'X';
            break;
        default: return 0;
    }
}

/******************************************************************************
 * Function: getNumVisits
 * Description: Returns the number of visits the player makes to the House.
 ******************************************************************************/
int House::getNumVisits()
{
    return numVisits;
}

