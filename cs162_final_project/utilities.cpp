/*****************************************************************************
 ** Program Filename: utilities.cpp
 ** Author: Ngan Tran
 ** Date: 2/12/2017
 ** Description: This file contains the utility functions implementations.
 *****************************************************************************/

#include "utilities.hpp"

/******************************************************************************
 * Function: menu
 * Description: Displays the main menu options
 ******************************************************************************/

void menu()
{
    std::cout
    << "\n------MAIN MENU------\n"
    << "1. Play Game\n"
    << "2. Read game hints\n"
    << "3. Exit program\n\n";
}

/******************************************************************************
 * Function: getNum
 * Description: Used to validate integer input
 ******************************************************************************/
int getNum()
{
    int number;
    while (!(std::cin>>number))
    {
        std::cout << "Invalid input. Please enter an integer: ";
        std::cin.clear();
        std::cin.ignore(100, '\n');
    }
    std::cin.ignore(100, '\n');
    return number;
}

/******************************************************************************
 * Function: getInRange
 * Description: Used to validate integer input is in range
 ******************************************************************************/

int getInRange(int start, int end)
{
    int number = getNum();
    
    while (number < start || number > end)
    {
        std::cout
        << "Invalid input. " << number << " is "
        << "out of range " << "[" << start << "-" << end << "]."
        << "\nTry again: ";
        number = getNum();
    }
    return number;
}
