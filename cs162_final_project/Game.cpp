/*****************************************************************************
 ** Program Filename: Game.cpp
 ** Author: Ngan Tran
 ** Date: 03/08/2017
 ** Description: Class implementation file for Game
 *****************************************************************************/


#include "Game.hpp"
#include <cstdlib>
#include <iomanip>

/******************************************************************************
 * Function: Game
 * Description: Constructor for Game object. Allocates memory for new Spaces,
        new player, initialize the variable for number of tries to equal
        the const NUM_TRIES, sets the current space to road, calls the
        linkSpaces() function, and initializes all boolean values to false.
 ******************************************************************************/
Game::Game()
{
    //allocate memory for spaces and player
    road = new Road;
    house = new House;
    barn = new Barn;
    lake = new Lake;
    treehouse = new Treehouse;
    boat = new Boat;
    garden = new Garden;
    player = new Alien;
    
    //initialize number of tries
    numTries = NUM_TRIES;
    
    //set current (starting) space to road
    currentSp = road;
    
    //call function to link the spaces
    linkSpaces();
    
    //initializes boolean values
    won = false;
    gameOver = false;
    part1Obt = false;
    part2Obt = false;
    boneObt = false;
    boatKeyObt = false;
    ropeObt = false;
    hookObt = false;
    dogDistracted = false;
    floatiesObt = false;
    blanketObt = false;
    flightObt = false;
    dogToyObt = false;
    snacksObt = false;
}

/******************************************************************************
 * Function: ~Game
 * Description: Destructor for Game. Deallocates memory to prevent leaks.
 ******************************************************************************/
Game::~Game()
{
    delete road;
    delete house;
    delete barn;
    delete lake;
    delete boat;
    delete treehouse;
    delete garden;
    delete player;
}

/******************************************************************************
 * Function: intro
 * Description: Displays the intro message for the game.
 ******************************************************************************/
void Game::intro()
{
    std::cout
    <<"               ----WELCOME TO ALIEN ON THE FARM----\n\n"
    <<"                              _____           \n"
    <<"                          .-|       |-.       \n"
    <<"                         /  ◌       ◌  \\      \n"
    <<"                        /    \\    /     \\     \n"
    <<"                       /      )-┉-(      \\    \n"
    <<"                      /      ( @ @ )      \\   \n"
    <<"                     /        \\ ◞ /        \\\n"
    <<"                    /          ) (          \\\n"
    <<"                   /   ●    .--'-'--.    ●   \\\n"
    <<"                ▁ /    ╆   /         \\   ┿    \\ ▁\n"
    <<"               ▞▀▀▚    (_╣-/\\       /\\-╠_)    ▞▀▀▚\n"
    <<"              ( %  \\.___╳\\/╾╾\\_____/╾╾\\/╳___./  % )\n"
    <<"               \\                                 /\n"
    <<"                 *-._    ◍ ◍ ◍ ◍ ◍ ◍ ◍      _.-*\n"
    <<"                   ╵--▬--┋┉┉┉┉┉┉┉┉┉┉┉┋--▬--╵\n"
    <<"                      |==┋___┊_ _┊___┋==|\n"
    <<"                      ╰╘╘┋___________┋╛╛╯\n"
    <<"                             /    \\\n"
    <<"                            /──────\\\n"
    <<"                             ▒    ▒\n"
    <<"                              ▒  ▒\n"
    <<"                               ░░\n\n"
    <<"--------------------------------------------------------------------\n\n"
    <<"You are a rebellious teenage alien from planet Zenosyne. One night,\n"
    <<"you decide to take your parent's new ship out for a spin. You travel\n"
    <<"through several galaxies before making an approach towards the Milky\n"
    <<"Way. You've learned a lot about planet Earth in school, but Zensyne's\n"
    <<"strict laws prohibits anyone from visiting. You decide to just take \n"
    <<"a quick look anyways, what's the harm? No one will ever know.\n\n"
   
    <<"Entering Earth's atmosphere, you hit a large storm cloud and begin \n"
    <<"losing control of the ship. \"This is it\", you think. The ship begins\n"
    <<"to tumble quickly down. As you near the ground, you're able to regain\n"
    <<"control of the ship to make a landing, although it is far from a \n"
    <<"smooth one You make a crash landing in the middle of a grassy plain.\n\n"
    
    <<"Forunately for you, it is nightime on Earth and you land in an\n"
    <<"uninhabited area. You cannot risk being spotted by any humans. You \n"
    <<"decide to go outside for a quick look before heading back home. As \n"
    <<"you exit the ship, you notice two pieces of the saucer had fallen \n"
    <<"off during the the rough landing. Uhhh ohhh. You search around\n"
    <<"in the grass, but cannot find anything. In the distance, you see \n"
    <<"something glimmering. It must be a part of the ship! You grab your\n"
    <<"backpack and start heading that way.\n\n"
    <<"--------------------------------------------------------------------\n\n";

}

/******************************************************************************
 * Function: linkSpaces
 * Description: This function links all the Space subtypes together by 
        calling each location's setPtrs function.
 ******************************************************************************/
void Game::linkSpaces()
{
    road->setPtrs(house, NULL, barn, NULL);
    house->setPtrs(lake, treehouse, road, garden);
    barn->setPtrs(road, NULL, NULL, NULL);
    lake->setPtrs(NULL, NULL, house, boat);
    treehouse->setPtrs(NULL, NULL, NULL, house);
    boat->setPtrs(NULL, lake, garden, NULL);
    garden->setPtrs(boat, house, NULL, NULL);
}

/******************************************************************************
 * Function: setCurrent
 * Description: Sets the current Space location the player is at in the game.
 ******************************************************************************/
void Game::setCurrent(Space* sp)
{
    currentSp = sp;
}

/******************************************************************************
 * Function: play
 * Description: Allows the user to play a game. Loops until the player chooses
        to quit, the boolean won is true, or the boolean gameOver is true.
        During each loop, the player is prompted to select a menu option move()
        depending on the current Space location they are in. The menu option 
        char is then returned to this function and the following actions occur:
            N : move to the space north of currentSp
            E : move to the space east of currentSp
            S : move to the space south of currentSp
            W : move to the space west of currentSp
            L : run the space's search function
            F : run the space's special function
            B : look in backpack, remove items if necessary
        Each time the play function loops, the numTries variable is decremented.
        The user gets warnings when numTries equals 20, 10, 5 and 1. The 
        boolean gameOver is set if numTries is equal to 0.
 ******************************************************************************/
void Game::play()
{
    intro();
    
    //pause, wait for user to press enter to begin the game
    std::string space;
    std::cout<<std::setw(45)<< "PRESS ENTER TO BEGIN\n\n";
    getline(std::cin, space);
    
    //display the game goals
    std::cout
    <<"-----------------------------GAME GOALS-----------------------------\n"
    <<"        ◍ Collect both ship parts\n"
    <<"        ◍ Get back to the crash site before sunrise\n"
    <<"        ◍ Do not get spotted by humans\n"
    <<"        ◍ Distract the dog so it stops barking\n"
    <<"        ◍ Add necessary items to backpack to help complete the task\n\n"
    <<"AN IMPORTANT NOTE: Your backpack has a capacity of only 5 items. \n"
    <<"Because everything on Earth is new and interesting to you, you add\n"
    <<"everything you find. Some items are not necessary to complete\n"
    <<"your tasks, so you must decide what to delete when you run out of\n"
    <<"space. Once you delete an item, it is gone forever! Choose wisely.\n"
    <<"--------------------------------------------------------------------\n\n";
    
    
    std::cout<<std::setw(50)<< "PRESS ENTER TO START GAME\n\n";
    getline(std::cin, space);
    
    currentSp->entryMsg();
    
    char moveChoice;
    do
    {
        moveChoice = currentSp->move();
        switch (moveChoice)
        {
            case 'N':
                currentSp = currentSp->northPtr();
                currentSp->entryMsg();
                break;
        
            case'E':
                currentSp = currentSp->eastPtr();
                currentSp->entryMsg();
                break;
            case 'S':
                currentSp = currentSp->southPtr();
                currentSp->entryMsg();
                break;
            case 'W':
                currentSp = currentSp->westPtr();
                currentSp->entryMsg();
                break;
            case 'L':
            {
                if (currentSp == house)
                    searchHouse();
                if (currentSp == boat)
                    searchBoat();
                if (currentSp == barn)
                    searchBarn();
                if (currentSp == treehouse)
                    searchTreehouse();
                if (currentSp == garden)
                    searchGarden();
            }
                break;
            case 'F':
            {
                if (currentSp == boat)
                    spBoat();
                if (currentSp == lake)
                    spLake();
                if (currentSp == barn)
                    spBarn();
                if (currentSp == treehouse)
                    spTreehouse();
            }
                break;
        
            case 'B':
            {
                player->removeItem();
                
                //for debugging purposes
                //player->print();
            }
                break;
            case 'H':
            {
                std::cout
                << "\nWhere would you like to go?\n"
                << "1. Back to the Road.\n"
                << "2. To the Tree House on the east.\n"
                << "3. To the Lake behind the House.\n"
                << "4. To the Garden on the west.\n"
                << "5. Stay at the house.\n";
                
                int next = getInRange(1, 5);
                if (next == 1)
                {
                    setCurrent(road);
                    road->entryMsg();
                }
                else if (next == 2)
                {
                    if (treehouse->getNumVisits() >= 3)
                    {
                        std::cout << "\nYou can't go there. The Tree House is broken!\n\n";
                        setCurrent(house);
                        house->entryMsg();
                    }
                    else
                    {
                        setCurrent(treehouse);
                        treehouse->entryMsg();
                    }
                }
                else if (next == 3)
                {
                    setCurrent(lake);
                    lake->entryMsg();
                }
                else if (next == 4)
                {
                    setCurrent(garden);
                    garden->entryMsg();
                }
                else if (next == 5)
                {
                    setCurrent(house);
                    house->entryMsg();
                }
            }
                break;
            default:
                std::cout <<"Ending Game.\n";
        }
        
        //decrement number of tries left after each menu selection
        numTries--;
        
        //print warnings for user - time limit
        if (numTries == 20 && !gameOver && !won)
        {
            std::cout
            <<"\n:::::::::::::::::::::Reminder:::::::::::::::::::::\n"
            <<" You must get back to the ship before sunrise!\n"
            <<"(you have 20 tries left to finish the game)\n"
            <<"::::::::::::::::::::::::::::::::::::::::::::::::::\n\n";
        }
        if (numTries == 10 && !gameOver && !won)
        {
            std::cout
            <<"\n:::::::::::::::::::::WARNING:::::::::::::::::::::\n"
            <<"Dawn is approaching quickly. Hurry!\n"
            <<"(you only have 10 tries left to finish the game)\n"
            <<":::::::::::::::::::::::::::::::::::::::::::::::::\n\n";
        }
        
        if (numTries == 5 && !gameOver && !won)
        {
            std::cout
            <<"\n:::::::::::::::::::::WARNING:::::::::::::::::::::\n"
            <<"The sun is now starting to rise. Hurry!!\n"
            <<"(you only have 5 tries left to finish the game)\n"
            <<":::::::::::::::::::::::::::::::::::::::::::::::::\n\n";
        }
        
        if (numTries == 1 && !gameOver && !won)
        {
            std::cout
            <<"\n:::::::::::::::::::::WARNING:::::::::::::::::::::\n"
            <<"The sun has risen above the horizon; it's morning.\n"
            <<"You are now at risk of being spotted by the humans.\n"
            <<"(you only have 1 try left to finish the game)\n"
            <<":::::::::::::::::::::::::::::::::::::::::::::::::\n\n";
        }
        
        //game ends when user runs out of tries 
        if (numTries == 0)
        {
            gameOver = true;
            won = false;
            results();
        }
        
    }while (moveChoice!='X' && !gameOver && !won);

}

/******************************************************************************
 * Function: searchBarn
 * Description: Search function for the Barn. Prompts the user to select the 
        area of the barn to search. Each item the player finds is added to 
        their backpack container. When an item is added to the backpack, its
        corresponding boolean is set to true. This prevents the user from 
        adding multiples of the same item when they search the same area again.
        The necessary items in the barn are: FLASH LIGHT, DOG BONE, ROPE
 ******************************************************************************/
void Game::searchBarn()
{
    //prompt user for area to search
    std::cout
    <<"\nWhere would you like to look? \n"
    <<"1. In the chicken coop\n"
    <<"2. In the horse's stall\n"
    <<"3. Check the pile of hay\n"
    <<"4. Check the wooden tool box\n";
    
    int choice = getInRange(1, 4);
    
    switch (choice)
    {
        case 1:
        {
            //if chicken eggs are not in the backpack
            if (player->searchItem("Chicken Eggs") == false)
            {
                std::cout
                <<"\nYou found some chicken eggs in the chicken coop.\n\n";
                player->addItem("Chicken Eggs");
            }
            
            //if eggs are already in the backpack
            else
            {
                std::cout <<"\nYou have already searched here\n\n";
            }
        }
            break;
        case 2:
        {
            if (!ropeObt)
            {
                std::cout
                <<"\nYou see a rope next to the horse.\n"
                <<"You quickly grab it, careful not to wake the horse.\n\n";
                player->addItem("Rope");
                
                //set boolean to true if rope is added
                if (player->searchItem("Rope"))
                    ropeObt = true;
            }
            else
            {
                std::cout <<"\nYou have already searched here\n\n";
            }
        }
            break;
        case 3:
        {
            if (!boneObt)
            {
                std::cout
                << "\nYou found a dog bone in the pile of hay\n\n";
                player->addItem("Dog Bone");
                
                //set boolean to true if dog gets added
                if (player->searchItem("Dog Bone"))
                    boneObt = true;
            }
            else
                std::cout <<"\nYou have already searched here.\n\n";
        }
            break;
        case 4:
        {
            if (!flightObt)
            {
                std::cout
                <<"\nYou found a flash light in the tool box.\n\n";
                player->addItem("Flash Light");
                
                //set boolean to true if flash light is added
                if (player->searchItem("Flash Light"))
                    flightObt = true;
            }
            else if (flightObt)
            {
                std::cout
                <<"\nYou have already searched the here.\n\n";
            }
        }
            break;
        default:
            break;
    }
}

/******************************************************************************
 * Function: searchHouse
 * Description: Search function for the House. In order to search the house,
        the player must have either the DOG TOY or DOG BONE in their backpack
        for use to distract the barking dog. If the player tries to search the
        house 3 times without distacting the dog, the humans will wake up and 
        the player will lose the game. 
        If the user has either TOY or BONE in their backpack, they will be 
        prompted to select the area of the house to search. Every item the 
        player finds will be added to their backpack container. When an item is
        added to the backpack, its boolean will be set to true so the player
        will not be able to add the same item again.
        Necessary item in the house: BOAT KEYS
 ******************************************************************************/
void Game::searchHouse()
{
    if ((!dogToyObt) && (!boneObt))
    {
        if (house->getNumVisits() == 1)
        {
                std::cout
                <<"\nAlthough you are careful to make little noise when entering the house,\n"
                <<"you have woken up the dog! The dog begins growling and barking. \n"
                <<"You run back to the road to prevent the dog from waking up the humans.\n"
                <<"You must find something to distract the dog!\n\n";
            
            //player goes back to road
            setCurrent(road);
        }
        else if (house->getNumVisits() == 2)
        {
            std::cout
            << "\nYou still don't have anything to distact the dog with.\n"
            << "The dog continues to bark very loudly. You run outside.\n\n";
            
            //player goes back to road
            setCurrent(road);
        }
        else if (house->getNumVisits() == 3)
        {
            std::cout
            <<"\nYou still don't have anything to distract the dog with.\n"
            <<"This time, the dog barks even louder and wakes up the humans.\n\n";
            
            //game over, player losese
            gameOver = true;
            results();
        }
    }
    else if ((dogToyObt) || (boneObt))
    {
        if (!dogDistracted)
        {
            if (player->searchItem("Dog Bone"))
            {
                std::cout
                <<"\nYou take the dog bone from your backpack and give it to the dog\n"
                <<"This works great to distract it while you search the house\n\n";
                dogDistracted = true;
                
                //dog bone was used, so remove from backpack
                player->removeStr("Dog Bone");
            }
            
            else if (player->searchItem("Dog Toy"))
            {
                std::cout
                <<"\nYou take the dog toy from your backpack and give it to the dog\n"
                <<"This works great to distract it while you search the house\n\n";
                dogDistracted = true;
                
                //dog toy was used, so remove from backpack
                player->removeStr("Dog Toy");
            }
   
        else if (dogDistracted)
        {
            std::cout << "\nThe dog is distracted, you can search the house.\n\n";
        }
    }
        //prompt user for area to search
        std::cout
        <<"\nWhere would you like to search?\n"
        <<"1. The garage\n"
        <<"2. The main room\n"
        <<"3. The kitchen\n";
    
        int choice = getInRange(1, 3);
        switch (choice)
        {
            case 1:
            {
                if (!floatiesObt)
                {
                    std::cout
                    <<"\nYou found some floaties in the garage.\n\n";
                    player->addItem("Floaties");
                    if (player->searchItem("Floaties"))
                        floatiesObt = true;
                }
                else if(floatiesObt)
                {
                    std::cout <<"\nYou have already searched the garage.\n\n";
                }
            }
                break;
            case 2:
            {
                if (!boatKeyObt)
                {
                    std::cout
                    <<"\nYou found the boat keys in the main room.\n\n";
                    player->addItem("Boat Keys");
                    if (player->searchItem("Boat Keys"))
                        boatKeyObt = true;
                }
                else if (boatKeyObt)
                {
                    std::cout <<"\nYou have already searched the main room.\n\n";
                }
            }
                break;
            case 3:
            {
                if (!snacksObt)
                {
                    std::cout
                    <<"\nYou find some interesting snacks in the kitchen.\n\n";
                    player->addItem("Snacks");
                    if (player->searchItem("Snacks"))
                        snacksObt = true;
                }
                else
                {
                    std::cout
                    <<"\nYou have already searched the kitchen.\n\n";
                }
            }
                break;
            default:
                std::cout << "Invalid input.\n";
                break;
        }
    }
}

/******************************************************************************
 * Function: searchBoat
 * Description: Search function for the Boat. The necessary item to find in 
        the Boat is the HOOK. Once this item is added to the player's backpack,
        its boolean will be set to true so the player won't be able to search 
        the boat again.
 ******************************************************************************/
void Game::searchBoat()
{
    if (hookObt == false)
    {
        std::cout
        <<"\nLooking around the boat, you find a large hook that could come in handy later.\n\n";
        player->addItem("Hook");
        
        //set boolean to true if hook is added to backpack
        if (player->searchItem("Hook"))
            hookObt = true;
    }
    
    else
    {
        std::cout
        <<"\nYou have already searched the boat.\n\n";
    }
}

/******************************************************************************
 * Function: searchTreehouse
 * Description: Search function for the Treehouse. The prompt depends on the 
        number of visits the user has made to the Treehouse. If the number of 
        visits is less than 3, the user will be able to search to find a 
        BLANKET, which will be added to their backpack. If the player has 
        visited 3 times, it will come crashing to the ground and the ship
        part will also fall; part1Obt will be set to true. If the user has 
        already obtained part2 also, they are on their way to winning the game.
        After 3 visits, the player will not be able to go back to the Treehouse;
        they must walk back to the House.
 ******************************************************************************/
void Game::searchTreehouse()
{
    if (treehouse->getNumVisits() == 3)
    {
        std::cout
        << "\nThe Tree House can no longer hold your weight.\n"
        << "It comes crashing down. Your ship part is on the ground!\n\n";
        
        //collect ship part
        part1Obt = true;
        
        if (part2Obt && part1Obt)
        {
            std::cout
            <<"\nYou have found both parts of the ship! Head back to the barn\n"
            <<"to get the wheelbarrow to help you bring them back to the crash site.\n\n";
        }
        else if (!part2Obt)
        {
            std::cout
            <<"\nYou have one more part to find! It's in the lake.\n\n";
        }
        
        std::cout << "You walk back to the house.\n\n";
        setCurrent(house);
    }
    
    else if (treehouse->getNumVisits() < 3)
    {
        if (!blanketObt)
        {
            std::cout
            <<"\nLooking around the treehouse, the only thing you can find is a blanket.\n\n";
            player->addItem("Blanket");
            
            //set boolean to true if blanket is added to backpack
            if (player->searchItem("Blanket"))
                blanketObt = true;
        }
    
        else
        {
            std::cout << "\nThere's nothing else in here!\n\n";
        }
    }
    else if (treehouse->getNumVisits() > 3)
    {
        //cannot go back to the treehouse
        std::cout
        << "\nThe Tree House is broken! You walk back to the House.\n\n";
        house->move();
    }
}

/******************************************************************************
 * Function: searchGarden
 * Description: Search function for the Garden. In order to search this space,
        the player must have a FLASH LIGHT in their backpack. A DOG TOY is 
        added to the player's container when they search the Garden.
        Some Earth plants are poisonous to Zenosynelings, so if the Player 
        visits too many times (3 times), they will pass out (num tries by be
        decremented by 5).
 ******************************************************************************/
void Game::searchGarden()
{
    //visiting 3 times decrements the numTries by 5
    if (garden->getNumVisits() == 3)
    {
        numTries -=5;
    }
    
    if(flightObt && !dogToyObt)
    {
        if (player->searchItem("Flash Light"))
        {
            std::cout
            <<"\nYou take the flash light out of your backpack and use it to search.\n"
            <<"You find a dog toy amongst the tulips.\n\n";
            player->addItem("Dog Toy");
            
            //set boolean to true if dog toy is added to backpack
            if (player->searchItem("Dog Toy"))
                dogToyObt = true;
        }
        
        else
        {
            std::cout
            <<"\nYou found the flash light but have removed it from your backpack.\n"
            <<"It's too dark out here, without the flashlight, you can't search the garden.\n\n";
        }
    }
    else if (flightObt && !dogToyObt)
    {
        std::cout
        <<"\nIt's too dark out here! Go find a flashlight to search the garden.\n\n";
    }
    
    else if(flightObt && dogToyObt)
    {
        std::cout
        <<"\nYou have already searched the garden.\n\n";
    }
}

/******************************************************************************
 * Function: spBoat
 * Description: Special function for the Boat. If the player has the BOAT KEYS
        in their backpack, they will be able to start the boat to go the
        lake in order to pick up the second ship part. If both both parts
        have been picked up, the player will be prompted to go to the barn to 
        get the wheelbarrow. If the player has removed the boat keys from 
        their backpack, they will not be able to start the boat.
 ******************************************************************************/
void Game::spBoat()
{
    if (boatKeyObt)
    {
        if (player->searchItem("Boat Keys"))
        {
            std::cout
            <<"\nYou take the boats keys out of your backpack and use them\n"
            <<"to start the boat. It works! You move the boat to the lake\n"
            <<"and steer it towards the floating saucer piece in the middle.\n"
            <<"...After about a minute, you get close enough to the piece to \n"
            <<"pick it up. You put it in the boat and head back towards shore.\n\n";
            
            part2Obt = true;
            
            if (part1Obt && part2Obt)
            {
                std::cout
                <<"\nYou have found both parts of the ship! Head back to the barn\n"
                <<"to get the wheelbarrow to help you bring them back to the crash site.\n\n";
            }
            else if (!part1Obt)
            {
                std::cout
                <<"\nYou have one more part to find! It's in Tree House.\n\n";
            }
        }
        
        else
        {
            std::cout
            <<"\nYou found the keys, but have removed them from your backpack!\n"
            <<"Without the boat keys, you can't get the ship part from the lake.\n\n";
        }
    }
    
    else
    {
        std::cout
        <<"\nYou cannot start the boat without a key. Go find the boat keys!\n\n";
    }
}

/******************************************************************************
 * Function: spLake
 * Description: Special function for the Lake. If the player has FLOATIES in
        their backpack, they will be able to swim in the lake. If they have
        not yet obtained the second ship part, they will swim to it to collect
        it - since swimming takes longer than taking the boat, the number of
        tries will be decremented by 3.
 ******************************************************************************/
void Game::spLake()
{
    if (floatiesObt)
    {
        if (player->searchItem("Floaties"))
        {
            if (!part2Obt)
            {
                std::cout
                <<"\nYou take the floaties out of your backpack, blow them up, put them on,\n"
                <<"and jump into the lake to swim towards the ship part. This takes you \n"
                <<"a really long time, but you are successful at collecting the part.\n\n";
                
                //floaties have been used, get rid of them
                player->removeStr("Floaties");
                
                //collect ship part
                part2Obt = true;
                
                //decrement number of tries by 3
                numTries -= 3;
                
                std::cout
                <<"\nYou have one more part to find! It's in the Tree House\n\n";
            }
            
            else if (part2Obt && part1Obt)
            {
                std::cout
                <<"\nYou have found both parts of the ship! Head back to the barn\n"
                <<"to get the wheelbarrow to help you bring them back to the crash site.\n\n";
            }
            
            else
            {
                std::cout
                <<"\nYou take the floaties out of your backpack, blow them up, put them on,\n"
                <<"and jump into the lake for just a quick swim. Time to get back to the task!\n\n";
                
                //floaties have been used, get rid of them
                player->removeStr("Floaties");
            }
            
        }
        else
        {
            std::cout
            <<"\nYou have already removed the floaties from your backpack and\n"
            <<"threw them away! That means you won't be able to swim, sorry!\n\n";
        }
    }
    else
    {
        std::cout
        <<"\nSilly alien! You don't know how to swim!\n"
        <<"You'll need to find some kind of flotation device\n\n";
    }
}

/******************************************************************************
 * Function: spBarn
 * Description: Special function for the Barn. This function is used to get 
        the wheelbarrow from the barn. The player will not be able to take 
        this unless they have otained both parts of the ship. Once the player
        takes the wheelbarrow, the boolean won will be set to true.
 ******************************************************************************/
void Game::spBarn()
{
    if (part1Obt && part2Obt)
    {
        std::cout
        <<"\nYou have the wheelbarrow now! You put the ship parts into the \n"
        <<"wheelbarrow and head west towards the ship crash site\n\n";
        
        //player wins the game
        won = true;
        results();
    }
    else
    {
        std::cout
        <<"\nThe wheelbarrow is useless to you right now. Come back later when you have\n"
        <<"obtained your ship parts. It will help you move them back to crash site.\n\n";
    }
}

/******************************************************************************
 * Function: spTreehouse
 * Description: Special function for the Treehouse. The ship part on top of 
        the Treehouse can be obtained two ways: by visiting 3 times to cause 
        it to fall, or by using the HOOK and ROPE to help get it down.
 ******************************************************************************/
void Game::spTreehouse()
{
    if (treehouse->getNumVisits() == 3)
    {
        std::cout
        << "\nThe Tree House can no longer hold your weight.\n"
        << "It comes crashing down. Your ship part is on the ground!\n\n";
        part1Obt = true;
        
        if (part2Obt && part1Obt)
        {
            std::cout
            <<"\nYou have found both parts of the ship! Head back to the barn\n"
            <<"to get the wheelbarrow to help you bring them back to the crash site.\n\n";
        }
        else if (!part2Obt)
        {
            std::cout
            <<"\nYou have one more part to find! It's in the Lake.\n\n";
        }
        
        std::cout << "\nYou walk back to the house.\n\n";
        setCurrent(house);
    }
    else if (treehouse ->getNumVisits() < 3)
    {
        if (flightObt)
        {
            if (hookObt && ropeObt)
            {
                std::cout
                <<"\nYou take out the hook and rope from your backpack and use it to help you\n"
                <<"get the missing piece of your ship down from the top of the tree\n"
                <<".....After several tries, you successfully get it down from the tree!\n\n";
                
                //collect ship part
                part1Obt = true;
        
                if (part2Obt && part1Obt)
                {
                    std::cout
                    <<"\nYou have found both parts of the ship! Head back to the barn\n"
                    <<"to get the wheelbarrow to help you bring them back to the crash site.\n\n";
                }
                else if (!part2Obt)
                {
                    std::cout
                    <<"\nYou have one more part to find! It's in the lake.\n\n";
                }
            }
            else
            {
                std::cout
                <<"\nYou're having trouble reaching! Go find some tools that'll help.\n\n";
            }
        }
        else
        {
            std::cout
            <<"\nIt's too dark to see anything out here! You need to find a flash light.\n\n";
        }
    }
    else if (treehouse->getNumVisits() > 3)
    {
        //cannot go back to the treehouse
        std::cout
        << "\nThe Tree House is broken! You walk back to the House.\n\n";
        house->move();
    }
}

/******************************************************************************
 * Function: results
 * Description: Displays the game results depending on the boolean values 
        gameOver and won.
 ******************************************************************************/
void Game::results()
{
    //player loses game
    if (gameOver)
    {
        std::cout
        <<"\n------------------YOU HAVE FAILED---------------------\n"
        <<"\nYou have been spotted by the humans. Unfortunately,\n"
        <<"there is no way to return home now. The humans will\n"
        <<"surely capture and interroate you about your planet...\n"
        <<"...Aliens and UFOs will not longer be a mystery...\n"
        <<"----------------------END GAME-----------------------\n\n";
    }
    
    //player wins game
    if (won)
    {
        std::cout
        <<"\n-----------------------YOU WIN-----------------------\n"
        <<"You made it back safely to the ship crash site\n"
        <<"without being spotted! You work fast to put the\n"
        <<"two parts of the ship back.\n\n"
        <<"After a while, you're successful at fixing the ship.\n"
        <<"Time to take off and head back to Zenosyne!\n\n"
        <<"It took you " <<NUM_TRIES - numTries <<" tries to win! Nicely done!\n"
        <<"-----------------------END GAME----------------------\n\n";
    }
}
