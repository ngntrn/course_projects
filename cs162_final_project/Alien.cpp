/*****************************************************************************
 ** Program Filename: Alien.cpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class implmenetation file for Alien
 *****************************************************************************/

#include "Alien.hpp"
#include <algorithm> //remove 

/******************************************************************************
 * Function: Alien
 * Description: Constructor for Alien object. Initializes the variable count
        for the number of items in the backpack to 1.
 ******************************************************************************/
Alien::Alien()
{
    count = 1;
}

/******************************************************************************
 * Function: ~Alien
 * Description: Destructor used to clear all the items in the backpack vector.
 ******************************************************************************/
Alien::~Alien()
{
    backpack.clear();
}

/******************************************************************************
 * Function: addItem
 * Description: Takes in a string item name argument. If there are 5 items
        in the vector backpack is 5, the item does not get added. Otherwise, the
        item will be added to the vector and count will be incremented.
 ******************************************************************************/
void Alien::addItem(string str)
{
    if (backpack.size() >=5)
    {
        std::cout<< "\nYour backpack is full! You cannot add \""<<str<<"\".\n\n";
    }
    else if (backpack.size() < 5)
    {
        backpack.push_back(str);
        count++;
        std:: cout <<"\""<< str <<"\" has been added to your backpack.\n\n";
    }
   
    else
    {
        std::cout<< "\nAn error occurred. Could not add item.\n\n";
    }
}

/******************************************************************************
 * Function: searchItem
 * Description: Takes in a string item name argument. Searches through the 
        vector for the item. Returns true of the item is found in the backpack.
 ******************************************************************************/
bool Alien::searchItem(string str)
{
    bool found = false;
    for (size_t i = 0; i <backpack.size(); i++)
    {
        if (backpack.at(i) == str)
        {
            return true;
        }
    }
    return found;
}

/******************************************************************************
 * Function: print
 * Description: Displays the contents of the vector backpack.
 ******************************************************************************/
void Alien::print()
{
    std::cout << "\nItems in your backpack: \n";
    
    for (int i =0; i <  signed(backpack.size()); i++)
    {
        std::cout << i + 1 << ". " << backpack[i] <<'\n';
    }
}

/******************************************************************************
 * Function: removeItem
 * Description: Prompts the user for the item number to remove and removes the
        item in the vector at the given position.
 ******************************************************************************/
void Alien::removeItem()
{
    if (backpack.empty())
    {
        std::cout << "\nYou backpack is empty!\n\n";
    }
    
    else
    {
        std::cout << "\nWhich item would you like to remove? \n";
        
        print();
        
        //option not to remove anything from the backpack 
        std::cout << count  <<". Don't Remove Anything\n";
        
        std::cout << "\nEnter the item number to remove: ";
        int position = getInRange(1, count);
        
        if (position < count)
        {
            if (position == 1)
            {
                backpack.erase(backpack.begin());
                count--;
            }
            else if (position !=1)
            {
                backpack.erase(backpack.begin() + (position-1));
                count--;
            }
        }
    }
}

/******************************************************************************
 * Function: removeStr
 * Description: Takes in a string item name as its argument. The vector::remove
        function is called, followed by erase, to delete an item from the
        vector backpack. The parameters of the remove function are: first & last
        - (the range of elements to process), and the string to remove.
        Once an item is removed and erased, the variable count is decremented.
 ******************************************************************************/
void Alien::removeStr(string str)
{
    //process from first to last element int vector
    //erase the element that is removed from the backpack
    //erase-remove idiom
    backpack.erase(std::remove(backpack.begin(), backpack.end(), str));
    count--;
}
