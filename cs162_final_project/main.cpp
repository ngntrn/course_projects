/*****************************************************************************
 ** Program Filename: CS162 Final Project main.cpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Main method for the "Alien On The Farm" game. This is a 
        text-based game. The player goes through spaces on a farm to try to 
        collect two missing pieces of their ship. The player must collect
        other appropriate items that will aid them in the task. This must 
        be completed before the sun rises, or the Alien will be caught.
 *****************************************************************************/

#include <iostream>
#include "Game.hpp"

int main()
{
    int gameChoice;
    do
    {
        menu();
        gameChoice = getInRange(1, 3);
        
        if (gameChoice==1)
        {
                //create game object
                Game g;
                //play game
                g.play();
        }
        
        else if (gameChoice == 2)
        {
            std::cout
            << "-----------------------------GAME HINTS-----------------------------\n"
            << "\nHOW TO WIN:\n"
            << "◍ Start by searching the barn for the DOG BONE, ROPE, FLASH LIGHT\n"
            << "  ::if you delete bone, search the garden, get the DOG TOY::\n"
            << "◍ With BONE or TOY, go to the house and search for BOAT KEYS\n"
            << "◍ Go to the lake, then to the boat. Search the boat for HOOK\n"
            << "◍ Collect the ship part from the lake\n"
            << "  ::if you delete the keys, find the FLOATIES and swim to the part::\n"
            << "◍ Go to the tree house. Collect other ship part\n"
            << "  ::(easy way: visit the tree house 3 times, it will fall)::\n"
            << "◍ Go back to barn, grab the wheelbarrow -- WIN THE GAME!\n\n"
            
            << "OTHER HINTS:\n"
            << "-Do not search the house without a way to distract the dog,\n"
            << "    the humans will wake up after 3 visits = game over.\n"
            << "-If you visit the garden 3 times, you risk getting knocked out\n"
            << "    by the poisonous tomato plants. This wastes your time!\n"
            << "-You only have 40 tries to win, make your decisions wisely!\n\n"
    
            << "IMPORTANT ITEMS: (items that help complete the task)\n"
            << " -Dog Bone OR Dog Toy  \n -Rope \n -Boat Keys OR Floaties\n -Flash Light \n -Hook\n\n"
            << "UNCESSARY ITEMS: (okay to delete) \n"
            << " -Chicken Eggs \n -Blanket\n -Snacks\n\n"
             <<"--------------------------------------------------------------------\n\n";
        }
    }while (gameChoice !=3);
    
    return 0;
}
    
