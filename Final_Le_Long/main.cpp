/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This program is an RPG game that utilizes a
 * turn-taking battle style. The goal of the game is to find the
 * princess and rescue her from the bandits and other foes. It is an
 * adventure game! There is a time limit to how long you have in order
 * to rescue the princess. There is also a weather exposure effect that
 * counts down unless the player has certain items. Play the game to
 * find out!
 * *********************************************************************/
#include "room.hpp"
#include "menu.hpp"

//Reads text from a file and prints.
void getPrompts(const string &);

int main()
{
    //Seed random.
    srand(time(NULL));

    Menu mainMenu;
    
    //Create the player and give her items.
    Character* Isa = new Player(14, 6);
    Isa->giveItem(APPLE);

    //Create the rooms.
    Room* begin = new Room(true, Isa, BEGIN, 15, 15, "mobs.txt", "trees.txt", "rocks.txt", "water.txt");
    Room* beforeIntersection = new Room(true, Isa, BEFORE_INTERSECTION, 15, 15, "mobs2.txt", "trees2.txt", "rocks2.txt", "water2.txt");
    Room* intersection = new Room(false, Isa, INTERSECTION, 15, 15, "mobs3.txt", "trees3.txt", "rocks3.txt", "water3.txt");
    Room* deadEnd = new Room(true, Isa, DEAD_END, 15, 15, "mobs4.txt", "trees4.txt", "rocks4.txt", "water4.txt");
    Room* hideout = new Room(true, Isa, HIDEOUT, 15, 15, "mobs5.txt", "trees5.txt", "rocks5.txt", "water5.txt");
    Room* dungeon = new Room(false, Isa, DUNGEON, 15, 15, "mobs6.txt", "trees6.txt", "rocks6.txt", "water6.txt");

    //Connect the rooms.
    begin->setNorth(beforeIntersection);
    beforeIntersection->setNorth(intersection);
    beforeIntersection->setSouth(begin);
    intersection->setNorth(deadEnd);
    intersection->setSouth(beforeIntersection);
    intersection->setEast(hideout);
    deadEnd->setSouth(intersection);
    hideout->setWest(intersection);
    hideout->setEast(dungeon);
    dungeon->setWest(hideout);

    //Transition information.
    RoomType transition; 
    Directions transitionDirection;

    bool gameEnds = false;

    //Menu loop.
    do
    { 
        mainMenu.initiateMenu();

        if(mainMenu.getUserChoice() == START_GAME)
        {
            getPrompts("intro.txt");

            begin->initiate();
            
            //The room the player is moving to.
            transition = begin->getMoveToRoom();

            //The direction the player is moving.
            transitionDirection = begin->getMovingDirection();

            //Reset the transition to NO_TRANSITION.
            begin->resetMoveToRoom();

            //Room transition loop.
            do
            {
                if(transition == BEFORE_INTERSECTION)
                {
                    //Specific character placements for room transitions.
                    if(transitionDirection == UP)
                    {
                        Isa->setCoordinates(14, 7);
                    }

                    else if(transitionDirection == DOWN)
                    {
                        Isa->setCoordinates(0, 7);
                    }
                    
                    beforeIntersection->initiate();

                    //Same transition as above.
                    transition = beforeIntersection->getMoveToRoom();
                    transitionDirection = beforeIntersection->getMovingDirection();
                    beforeIntersection->resetMoveToRoom();

                    //Checks to see if the game ends to break the loop.
                    gameEnds = beforeIntersection->getEndGame();
                }

                else if(transition == BEGIN)
                {
                    Isa->setCoordinates(0, 7);
                    begin->initiate();
                    transition = begin->getMoveToRoom();
                    transitionDirection = begin->getMovingDirection();
                    begin->resetMoveToRoom();
                    gameEnds = begin->getEndGame();
                }

                else if(transition == INTERSECTION)
                {
                    if(transitionDirection == UP)
                    {
                        Isa->setCoordinates(14, 7);
                    }

                    else if(transitionDirection == DOWN)
                    {
                        Isa->setCoordinates(0, 7);
                    }

                    else if(transitionDirection == LEFT)
                    {
                        Isa->setCoordinates(7, 14);
                    }

                    intersection->initiate();
                    transition = intersection->getMoveToRoom();
                    transitionDirection = intersection->getMovingDirection();
                    intersection->resetMoveToRoom();
                    gameEnds = intersection->getEndGame();
                }

                else if(transition == DEAD_END)
                {
                    Isa->setCoordinates(14, 7);
                    deadEnd->initiate();
                    transition = deadEnd->getMoveToRoom();
                    transitionDirection = deadEnd->getMovingDirection();
                    deadEnd->resetMoveToRoom();
                    gameEnds = deadEnd->getEndGame();
                }

                else if(transition == HIDEOUT) 
                {
                    if(transitionDirection == RIGHT)
                    {
                        Isa->setCoordinates(7, 0);
                    }

                    else if(transitionDirection == LEFT)
                    {
                        Isa->setCoordinates(7, 14);
                    }
                    
                    hideout->initiate();
                    transition = hideout->getMoveToRoom();
                    transitionDirection = hideout->getMovingDirection();
                    hideout->resetMoveToRoom();
                    gameEnds = hideout->getEndGame();
                }

                else if(transition == DUNGEON) 
                {
                    if(transitionDirection == RIGHT)
                    {
                        Isa->setCoordinates(7, 0);
                    }

                    dungeon->initiate();
                    transition = dungeon->getMoveToRoom();
                    transitionDirection = dungeon->getMovingDirection();
                    dungeon->resetMoveToRoom();
                    gameEnds = dungeon->getEndGame();
                }

                if(transition == NO_TRANSITION || dungeon->getEndGame())
                {
                    //Reset game if it ends. If the player dies or one of the 
                    //other loop breaking condition occurs, the room 
                    //transition will be NO_TRANSITION and this if 
                    //statement will execute. The game will also need to
                    //execute when you are in the dungeon room and will have
                    //talked to the princess.

                    //The following codes delete the rooms and recreate them
                    //to be able to play again.
                    delete begin; 
                    delete beforeIntersection;
                    delete intersection;
                    delete deadEnd;
                    delete hideout;
                    delete dungeon;
                    delete Isa;

                    Isa = new Player(14, 6);
                    Isa->giveItem(APPLE);
                    
                    begin = new Room(true, Isa, BEGIN, 15, 15, "mobs.txt", "trees.txt", "rocks.txt", "water.txt");
                    beforeIntersection = new Room(true, Isa, BEFORE_INTERSECTION, 15, 15, "mobs2.txt", "trees2.txt", "rocks2.txt", "water2.txt");
                    intersection = new Room(false, Isa, INTERSECTION, 15, 15, "mobs3.txt", "trees3.txt", "rocks3.txt", "water3.txt");
                    deadEnd = new Room(true, Isa, DEAD_END, 15, 15, "mobs4.txt", "trees4.txt", "rocks4.txt", "water4.txt");
                    hideout = new Room(true, Isa, HIDEOUT, 15, 15, "mobs5.txt", "trees5.txt", "rocks5.txt", "water5.txt");
                    dungeon = new Room(false, Isa, DUNGEON, 15, 15, "mobs6.txt", "trees6.txt", "rocks6.txt", "water6.txt");

                    begin->setNorth(beforeIntersection);
                    beforeIntersection->setNorth(intersection);
                    beforeIntersection->setSouth(begin);
                    intersection->setNorth(deadEnd);
                    intersection->setSouth(beforeIntersection);
                    intersection->setEast(hideout);
                    deadEnd->setSouth(intersection);
                    hideout->setWest(intersection);
                    hideout->setEast(dungeon);
                    dungeon->setWest(hideout);

                }

            } while(transition != NO_TRANSITION && !gameEnds); 
        }

        else if(mainMenu.getUserChoice() == CREDITS)
        {
            cout << "\nCreated by Long Le." << endl;
            cout << "\nThe (2)ASCII images are taken from these websites:"
                 << "\n1. http://www.asciiworld.com/-Castels-.html." 
                 << "\n2. http://loveascii.com/princess2.html" << endl;
            cin.ignore(INT_MAX, '\n');
        }

    } while(!mainMenu.getQuitProgram());
                    
    //When user decides to quit,
    //clean up heap.
    delete begin; 
    delete beforeIntersection;
    delete intersection;
    delete deadEnd;
    delete hideout;
    delete dungeon;
    delete Isa;

    return 0;
}

/***********************************************************************
 * ** Description: This function reads from a text file and prints the
 * contents.
 *
 * Parameters: const string & - the name of the file that text will need
 * to read from.
 *
 * Return: void. 
 * *********************************************************************/
void getPrompts(const string &fileName) 
{
    char temp;
    string print = "";
    ifstream inputFile;
    
    inputFile.open(fileName);

    if(!inputFile)
    {
        cout << "\nThe " << fileName << " could not open!!";
        cin.ignore(INT_MAX, '\n');
    }

    else
    {
        while(inputFile >> std::noskipws >> temp)
        {
            //string concatenation.
            print += temp;
        }

        cout << print;
        cin.ignore(INT_MAX, '\n');
    }

    inputFile.close();
}
