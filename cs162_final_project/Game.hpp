/*****************************************************************************
 ** Program Filename: Game.hpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class declaration file for Game
 *****************************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include "Space.hpp"
#include "Road.hpp"
#include "House.hpp"
#include "Barn.hpp"
#include "Lake.hpp"
#include "Treehouse.hpp"
#include "Boat.hpp"
#include "Garden.hpp"
#include "Alien.hpp"

#include <vector>
#include <iostream>
#include <string>
using std::string;

const int NUM_TRIES = 40;

class Game
{
public:
    Game();
    ~Game();
    
    void linkSpaces();
    void setCurrent(Space*);
    void intro();
    void play();
    void results();
    
    void searchBarn();
    void searchHouse();
    void searchBoat();
    void searchTreehouse();
    void searchGarden();
    
    void spBoat();
    void spLake();
    void spBarn();
    void spTreehouse();
    
private:
    Alien* player;
    
    Space* road;
    Space* house;
    Space* barn;
    Space* lake;
    Space* treehouse;
    Space* boat;
    Space* garden;
    Space* currentSp;
    
    int numTries;
    
    //objects obtained
    bool part1Obt;
    bool part2Obt;
    bool boneObt;
    bool boatKeyObt;
    bool ropeObt;
    bool hookObt;
    bool flightObt;
    bool floatiesObt;
    bool blanketObt;
    bool dogToyObt;
    bool snacksObt;
    bool dogDistracted;
    
    //game status
    bool won;
    bool gameOver;
};

#endif
