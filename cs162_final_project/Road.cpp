/*****************************************************************************
 ** Program Filename: Road.cpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class implmenetation file for Road
 *****************************************************************************/

#include "Road.hpp"

/******************************************************************************
 * Function: entryMsg
 * Description: Overrides the Space entryMsg method. Displays the Road's 
        entry message. The message is different depending on the number of 
        of visits the player has made.
 ******************************************************************************/
void Road::entryMsg()
{
    if (numVisits == 0)
    {
        std::cout
        << "You are now standing on a gravel road. You spot the two pieces of\n"
        << "your ship in two different places. One is on top of a tree house\n"
        << "and the other is floating on top of the lake behind the house.\n"
        << "In order to get to both of these places, you must go through the\n"
        << "house. Right behind you, to the south, is a barn. \n\n";
        numVisits ++;
    }
    
    else
    {
        std::cout
        << "\nYou are now back on the gravel road.\n\n";
        numVisits++;
    }
        
}

/******************************************************************************
 * Function: move
 * Description: Displays the appropriate menu options for the specific Space
        subclass. Prompts the user for a menu choice and returns the 
        appropriate char which will then be used in Game::play() to perform 
        the corresponding game move.
 ******************************************************************************/
char Road::move()
{
    
    std::cout
    << "----ON THE ROAD----\n"
    << "What would you like to do?\n"
    << "1. Go to the house. \n"
    << "2. Enter the barn. \n"
    << "3. Check your backpack. \n"
    << "4. Give up. \n";
    
    int choice = getInRange(1, 4);
    
    switch (choice)
    {
        case 1: return 'N';
            break;
        case 2: return 'S';
            break;
        case 3: return 'B';
            break;
        case 4: return 'X';
            break; 
        default: return 0;
    }
    
}



