/*****************************************************************************
 ** Program Filename: Boat.cpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class implmenetation file for Boat
 *****************************************************************************/

#include "Boat.hpp"

/******************************************************************************
 * Function: entryMsg
 * Description: Overrides the Space entryMsg method. Displays the Boat's
 entry message. The message is different depending on the number of
 of visits the player has made.
 ******************************************************************************/
void Boat::entryMsg()
{
    if (numVisits == 0)
    {
        std::cout
        << "\nYou are now at the boat. Although it is small, you are still able to \n"
        << "fit inside. You wonder if you can use it to pick up the ship part.\n\n";
        numVisits++;
    }
    else
    {
        std::cout
        << "\nYou have made it back to the boat.\n\n";
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
char Boat::move()
{
    std::cout
    <<"----AT THE BOAT----\n"
    << "What would you like to do?\n"
    << "1. Start the boat. \n"
    << "2. Search the boat.\n"
    << "3. Walk back to the Lake. \n"
    << "4. Go to the Garden\n"
    << "5. Check your backpack. \n"
    << "6. Give up. \n";
    
    int choice = getInRange(1, 6);
    
    switch (choice)
    {
        case 1: return 'F';
            break;
        case 2: return 'L';
            break; 
        case 3: return 'E';
            break;
        case 4: return 'S';
            break;
        case 5: return 'B';
            break;
        case 6: return 'X';
            break;
        default: return 0;
    }
}
