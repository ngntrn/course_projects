/*****************************************************************************
 ** Program Filename: Garden.cpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class implmenetation file for Garden
 *****************************************************************************/

#include "Garden.hpp"
#include <iomanip>

/******************************************************************************
 * Function: entryMsg
 * Description: Overrides the Space entryMsg method. Displays the Garden's
        entry message. The message is different depending on the number of
        of visits the player has made.
 ******************************************************************************/
void Garden::entryMsg()
{
    if (numVisits == 0)
    {
        std::cout
        <<"\nYou're now standing in the garden next to the house. You're careful\n"
        <<"not to touch anything since some Earth plants are deadly to Zenosyne-lings\n\n";
        numVisits++;
    }
    else if (numVisits == 3)
    {
        std::cout
        << "\nYou're back at the garden, and although you were careful, you\n"
        << "accidentally touch the deadliest Earth plant to Zenosynelings,\n"
        << "the tomato plant! Your body goes into shock and you pass out...\n\n";
        
        std::string space;
        std::cout<<std::setw(45)<< "PRESS ENTER TO GET UP\n\n";
        getline(std::cin, space);
        
        std::cout
        << "You wake up groggy, but are able to pick yourself back up. You're \n"
        << "not sure how long you were out, but the sky is getting brighter.\n"
        << "Hurry and finish your task before the sun comes up!\n\n";
    }
    else
    {
        std::cout
        <<"\nYou're are back at the garden again. Careful not to touch the plants!\n\n";
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
char Garden::move()
{
    std::cout
    << "----AT THE GARDEN----\n"
    << "What would you like to do?\n"
    << "1. Search the Garden. \n"
    << "2. Go to the house. \n"
    << "3. Go to the Boat.\n"
    << "4. Check your backpack. \n"
    << "5. Give up. \n";
    
    int choice = getInRange(1, 5);
    
    switch (choice)
    {
        case 1: return 'L';
            break;
        case 2: return 'E';
            break;
        case 3: return 'N';
            break;
        case 4: return 'B';
            break;
        case 5: return 'X';
            break;
        default: return 0;
    }

}
