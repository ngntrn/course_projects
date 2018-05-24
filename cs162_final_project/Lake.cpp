/*****************************************************************************
 ** Program Filename: Lake.cpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class implmenetation file for Lake
 *****************************************************************************/

#include "Lake.hpp"

/******************************************************************************
 * Function: entryMsg
 * Description: Overrides the Space entryMsg method. Displays the Lake's
        entry message. The message is different depending on the number of
        of visits the player has made.
 ******************************************************************************/
void Lake::entryMsg()
{
    if (numVisits == 0)
    {
        std::cout
        << "\nYou are now standing at the lake. You can see your ship part is  \n"
        "still floating in the middle of the lake. Too bad you don't know how to swim!\n\n";
        numVisits++;
    }
    else
    {
        std::cout
        << "\n You are now back at the lake.\n\n";
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
char Lake::move()
{
    std::cout
    <<"----AT THE LAKE----\n"
    << "What would you like to do? \n"
    << "1. Go back to the House. \n"
    << "2. Go for a swim. \n"
    << "3. Walk to the boat. \n"
    << "4. Check your backpack \n"
    << "5. Give up \n";
    
    int choice = getInRange(1, 5);
    
    switch (choice)
    {
        case 1: return 'S';
            break;
        case 2: return 'F';
            break;
        case 3: return 'W';
            break;
        case 4: return 'B';
            break;
        case 5: return 'X';
            break;
        default: return 0;
    }
}
