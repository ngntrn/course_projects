/*****************************************************************************
 ** Program Filename: Barn.cpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class implmenetation file for Barn
 *****************************************************************************/

#include "Barn.hpp"

/******************************************************************************
 * Function: entryMsg
 * Description: Overrides the Space entryMsg method. Displays the Barn's
        entry message. The message is different depending on the number of
        of visits the player has made.
 ******************************************************************************/
void Barn::entryMsg()
{
    if (numVisits == 0)
    {
        std::cout
        << "\nYou walk inside the barn and begin to look around.\n"
        << "You see a chicken coop, horse stall, and pile of hay\n\n";
        numVisits++;
    }
    else
    {
        std::cout
        << "\nYou are now back inside the barn\n\n";
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
char Barn::move()
{
    std::cout
    <<"----IN THE BARN----\n"
    << "What would you like to do?\n"
    << "1. Search the Barn. \n"
    << "2. Go back to the Road. \n"
    << "3. Take the wheelbarrow\n"
    << "4. Check your backpack. \n"
    << "5. Give up. \n";
    
    int choice = getInRange(1, 5);
    
    switch (choice)
    {
        case 1: return 'L';
            break;
        case 2: return 'N';
            break;
        case 3: return 'F';
            break;
        case 4: return 'B';
            break;
        case 5: return 'X';
            break;
        default: return 0;
    }
}



