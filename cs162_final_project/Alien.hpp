/*****************************************************************************
 ** Program Filename: Alien.hpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class declaration file for Alien
 *****************************************************************************/

#ifndef ALIEN_HPP
#define ALIEN_HPP

#include <iostream>
#include <vector> //vector container 
#include <string>
#include "utilities.hpp"

using std::string;

class Alien
{
private:
    std::vector <string> backpack;  //vector container
    int position;                   //position in vector
    int count;                      //number of items in vector
    
public:
    Alien();
    ~Alien();
    void addItem(string);
    bool searchItem(string);
    void print();
    void removeItem();
    void removeStr(string);
};

#endif 
