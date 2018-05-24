/*****************************************************************************
 ** Program Filename: Treehouse.cpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class implmenetation file for Treehouse
 *****************************************************************************/

#include "Treehouse.hpp"

/******************************************************************************
 * Function: entryMsg
 * Description: Overrides the Space entryMsg method. Displays the Treehouse's
        entry message. The message is different depending on the number of
        of visits the player has made.
 ******************************************************************************/
void Treehouse::entryMsg()
{
    if (numVisits == 0)
    {
        std::cout
        << "\nYou are now at the tree house. The ship part is still on top of\n"
        << "the tree. Maybe you can find something to help get it down from \n"
        << "up there. You use the ladder to climb up to the tree house.\n\n";
        numVisits++;
    }
    
    else
    {
        std::cout
        << "\nYou are now back at the tree house. You climb the ladder again\n"
        << "to get to the top. The tree house feels a lot less stable this time.\n\n";
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
char Treehouse::move()
{
    std::cout
    <<"----AT THE TREE HOUSE----\n"
    << "What would you like to do? \n"
    << "1. Try to get the ship part \n"
    << "2. Search the Tree House\n"
    << "3. Go back to the house \n"
    << "4. Check your backpack \n"
    << "5. Give up \n";
    
    int choice = getInRange(1, 5);
    
    switch (choice)
    {
        case 1: return 'F';
            break;
        case 2: return 'L';
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

