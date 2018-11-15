/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: This class represents a room within the game. It 
 * contains a 2D array of pointers to spaces which is used as a playing 
 * field that characters can interact with. This class is essentially
 * the brains of the game. It sets up the playing field, presents an
 * in-game menu, and controls all of the characters.
 * *********************************************************************/
#include "room.hpp"

//These variables are losing condition controls. 
//cold - if drops to zero you die from hypothermia.
//princessCountDown - if drops to zero the bandits escape with the princess.
int Room::cold = 300;
int Room::princessCountDown = 1000;

/***********************************************************************
 * ** Description: This default constructor is empty. It is good
 * practice to have a default constructor.
 * *********************************************************************/
Room::Room()
{
    //empty.
}

/***********************************************************************
 * ** Description: This constructor initializes member variables and 
 * creates the characters. It also creates the room, fills it with 
 * objects and connects the spaces. Basically, it sets up the playing
 * field for the room.
 *
 * Parameters: 
 * 1. bool - whether or not a battle is occuring in the room.
 * 2. Character* - the player that the user will be controlling.
 * 3. unsigned - number of rows the room has. 
 * 4. unsigned - number of columns the room has.
 * 5-8. string(s) - the file names of the files that provide generation
 * information for the Room class.
 * *********************************************************************/
Room::Room(bool inBattle, Character* Player, RoomType roomType, unsigned rows, unsigned columns, 
           const string &mobsInput, const string &treesInput,  
           const string &rocksInput, const string &waterInput)
{
    this->roomType = roomType;
    this->rows = rows;
    this->columns = columns;
    this->treesInput = treesInput;
    this->mobsInput = mobsInput;
    this->rocksInput = rocksInput;
    this->waterInput = waterInput;
    this->inBattle = inBattle;

    endGame = false;
    moveToRoom = NO_TRANSITION;
    controlChoice = "notquit";

    north = nullptr;
    south = nullptr;
    east = nullptr;
    west = nullptr;

    endPlayerTurn = false;
    endMobTurn = true;

    stage = nullptr;

    this->Player = Player;

    //Sets the direction that the player is facing depending on which
    //room type the player is in.
    if(this->roomType == BEGIN || this->roomType == BEFORE_INTERSECTION 
        || this->roomType == INTERSECTION || this->roomType == DEAD_END)
    {
        playerDirection = UP;
        playerGraphics = '^';
    } 

    else if(this->roomType == HIDEOUT || this->roomType == DUNGEON)
    {
        playerDirection = RIGHT;
        playerGraphics = '>';
    }

    mobNumber = countMob(); 
    mob = new Character*[mobNumber];

    createRoom();
    createMobs();
    fillRoom();
    connectSpaces();
}

/***********************************************************************
 * ** Description: This destructor cleans up the heap memory generated
 * by pointers in the room. 
 * *********************************************************************/
Room::~Room()
{
    //Deletes all the spaces.
    for(unsigned i = 0; i < rows; i++)
    {
        for(unsigned j = 0; j < columns; j++)
        {
            delete stage[i][j];
        }

        delete [] stage[i];
    }

    delete [] stage;
    stage = nullptr;

    //Deletes all the mobs and characters.
    for(unsigned i = 0; i < mobNumber; i++)
    {
        delete mob[i];
    }

    delete [] mob;
    mob = nullptr;

    //Sets player to nullptr. The actual player object
    //will be deleted in main.
    Player = nullptr;

    //Sets directions to nullptr.
    north = nullptr;
    south = nullptr;
    east = nullptr;
    west = nullptr;
}

/***********************************************************************
 * ** Description: This function sets the graphics for the character
 * depending on which direction she is facing.
 *
 * Parameters: Directions - represents the direction the player is facing.
 *
 * Return: void.
 * *********************************************************************/
void Room::setPlayerGraphics(Directions playerDirection)
{
    switch(playerDirection)
    {
        case UP:
            playerGraphics = '^';
            break;

        case DOWN:
            playerGraphics = 'v';
            break;

        case LEFT:
            playerGraphics = '<';
            break;

        case RIGHT:
            playerGraphics = '>';
            break;
    }
}

/***********************************************************************
 * ** Description: This function sets the graphics for the different
 * spaces in the game.
 *
 * Parameters: SpaceType - represents the type of space. 
 *
 * Return: char - the corresponding graphics to the space.
 * *********************************************************************/
char Room::getGraphics(SpaceType space)
{
    char graphics = ' ';

    switch(space)
    {
        case GROUND:
            graphics = '.';
            break;

        case TREE:
            graphics = 'T';
            break;

        case ROCK: 
            graphics = 'o';
            break;

        case WATER:
            graphics = '~';
            break;
        
        case CAMPFIRE:
            graphics = '*';
            break;

        case DOOR:
            graphics = '#';
            break;
    }

    return graphics;
}

/***********************************************************************
 * ** Description: This function connects all of the spaces via the four
 * direction spaces pointers within the Space class.
 *
 * Parameters: none. 
 *
 * Return: void. 
 * *********************************************************************/
void Room::connectSpaces()
{
    Space* connectOne = nullptr;
    Space* connectTwo = nullptr;

    //Connect the horizontal pointers.
    for(unsigned i = 0; i < rows; i++)
    {
        for(unsigned j = 0; j < columns - 1; j++)
        {
            connectOne = stage[i][j];
            connectTwo = stage[i][j + 1];

            connectOne->connectSpaces(RIGHT, connectTwo);
            connectTwo->connectSpaces(LEFT, connectOne);
        }
    }

    //Connect the vertical pointers.
    for(unsigned i = 0; i < columns; i++)
    {
        for(unsigned j = 0; j < rows - 1; j++)
        {
            connectOne = stage[j][i];
            connectTwo = stage[j + 1][i];

            connectOne->connectSpaces(DOWN, connectTwo);
            connectTwo->connectSpaces(UP, connectOne);
        }
    }
}

/***********************************************************************
 * ** Description: This function generates a 2D array of pointers to the
 * Space class. The pointers will utilize polymorphism to change the
 * spaces to the specifications in each corresponding setup file.
 *
 * Parameters: none. 
 *
 * Return: void. 
 * *********************************************************************/
void Room::createRoom()
{
    if(rows == 0 || columns == 0)
    {
        cout << "\nThe room does not minimum requirements!!!" << endl;   
    }

    else if(rows > 0 && columns > 0)
    {
        stage = new Space**[rows];

        for(unsigned i = 0; i < rows; i++)
        {
            stage[i] = new Space*[columns];
        }
    }
}

/***********************************************************************
 * ** Description: This function fills the 2D array of pointers with
 * Ground spaces created in heap, then replaces the Ground spaces with
 * objects using other functions.
 *
 * Parameters: none. 
 *
 * Return: void. 
 * *********************************************************************/
void Room::fillRoom()
{
    //Fill the space pointers with Ground spaces.
    for(unsigned i = 0; i < rows; i++)
    {
        for(unsigned j = 0; j < columns; j++)
        {
            stage[i][j] = new Ground;
        }
    }

    //Deletes the Ground spaces and replaces them with other
    //types of spaces according to the .txt setup files.
    placeSpace(treesInput, TREE);
    placeSpace(rocksInput, ROCK);
    placeSpace(waterInput, WATER);
    
    //Place certain special spaces individually.
    if(roomType == BEGIN) 
    {
        placeSpecialSpace(2, 10, CAMPFIRE);
    }

    else if(roomType == BEFORE_INTERSECTION)
    {
        placeSpecialSpace(6, 5, CAMPFIRE);
    }

    else if(roomType == INTERSECTION)
    {
        placeSpecialSpace(7, 12, DOOR);
    }

    else if(roomType == HIDEOUT)
    {
        placeSpecialSpace(7, 13, DOOR);
        placeSpecialSpace(7, 8, CAMPFIRE);
    }

    placeMobs();
}

/***********************************************************************
 * ** Description: This function manually places the Campfire or Door
 * spaces.
 *
 * Parameters:
 * 1. int(s) - represents the coordinates to place the space. 
 * 2. Spacetype - represents the space type to place. 
 *
 * Return: void. 
 * *********************************************************************/
void Room::placeSpecialSpace(int row, int column, SpaceType type)
{
    delete stage[row][column];

    switch(type)
    {
        case CAMPFIRE:
            stage[row][column] = new Campfire;
            break;

        case DOOR:
            stage[row][column] = new Door;
            break;

        case TREE:
        case ROCK:
        case WATER:
        case GROUND: 
            break;
    }
}

/***********************************************************************
 * ** Description: This function replaces the GROUND space types with
 * TREES according to the setup .txt text file.
 *
 * Parameters: none. 
 *
 * Return: void. 
 * *********************************************************************/
void Room::placeSpace(const string &fileName, SpaceType objectType)
{
    ifstream inputFile;
    unsigned temp;
    unsigned count = 0;
    unsigned numberOfObjects;

    inputFile.open(fileName);

    if(!inputFile)
    {
        cout << "\nThe " << fileName << " file could not open!!" << endl;
    }

    else
    {
        //Count the number of digits in the file.
        while(inputFile >> temp)
        {
            count++; 
        }

        //The number of objects are half the size of 
        //row and column coordinates, since there are two
        //digits to a coordinate..
        numberOfObjects = count / 2; 

        //Reset the file pointer position.
        inputFile.close();
        inputFile.open(fileName);

        Coordinates* objects = new Coordinates[numberOfObjects];

        //Store the coordinate information.
        for(unsigned i = 0; i < numberOfObjects; i++)
        {
                inputFile >> objects[i].row; 
                inputFile >> objects[i].column;
        }

        //Replace the ground 
        for(unsigned i = 0; i < numberOfObjects; i++)
        {
            delete stage[objects[i].row][objects[i].column];

            switch(objectType)
            {
                case TREE:
                    stage[objects[i].row][objects[i].column] = new Tree;
                    break;
                    
                case ROCK:
                    stage[objects[i].row][objects[i].column] = new Rock;
                    break;

                case WATER:
                    stage[objects[i].row][objects[i].column] = new Water;
                    break;

                case DOOR:
                case GROUND: 
                case CAMPFIRE:
                break;
            }
        }

        inputFile.close();

        delete [] objects;
    }
}

/***********************************************************************
 * ** Description: This function marks the character location as occupied. 
 *
 * Parameters: Character* - A pointer to characters that can represent
 * the player, npcs, or mobs. 
 *
 * Return: void. 
 * *********************************************************************/
void Room::placeCharacter(Character* character)
{
    stage[character->getCoordinates().row][character->getCoordinates().column]->setOccupied(true);
}

/***********************************************************************
 * ** Description: This function removes the mark that the character 
 * location is occupied. 
 *
 * Parameters: Character* - A pointer to characters that can represent
 * the player, npcs, or mobs. 
 *
 * Return: void. 
 * *********************************************************************/
void Room::unPlaceCharacter(Character* character)
{
    stage[character->getCoordinates().row][character->getCoordinates().column]->setOccupied(false);
}

/***********************************************************************
 * ** Description: This function prints out the room to console. 
 *
 * Parameters: none.  
 *
 * Return: void. 
 * *********************************************************************/
void Room::printRoom()
{
    //Border.
    cout << ' ' << string((columns * 2) + 1, '-') << endl;

    for(unsigned i = 0; i < rows; i++)
    {
        cout << '|';

        for(unsigned j = 0; j < columns; j++)
        {
            //Use space graphics if the space is not occupied.
            if(stage[i][j]->getOccupied() == false)
            {
                cout << setw(2) << getGraphics(stage[i][j]->getSpaceType());
            }

            else
            {

                //Print the character graphics.
                if(i == Player->getCoordinates().row && j == Player->getCoordinates().column)
                {
                    cout << setw(2) << playerGraphics; 
                }

                //Print the mob graphics.
                for(unsigned k = 0; k < mobNumber; k++)
                {
                    if(i == mob[k]->getCoordinates().row && j == mob[k]->getCoordinates().column) 
                    {
                        if(mob[k]->getDeadStatus() == false)
                        {
                            cout << ' ' << getMobGraphics(mob[k]->getMobType());
                        }

                        else
                        {
                            cout << setw(2) << 'x';
                        }
                    }
                }
            }
        }

        //Border.
        cout << " |" << endl;
    }

    //Border.
    cout << ' ' << string((columns * 2) + 1, '-') << endl;
}

/***********************************************************************
 * ** Description: This function prints out the room to console. 
 * For mobs or other char in battle
 *
 * Parameters: 
 * 1. unsigned - How much movement points the character has left for the
 * battle turn.
 * 2. Character* - A character the function is checking.
 *
 * Return: void. 
 * *********************************************************************/
void Room::printRoom(unsigned move, Character* character)
{
    //Border.
    cout << ' ' << string((columns * 2) + 1, '-') << endl;

    for(unsigned i = 0; i < rows; i++)
    {
        cout << '|';

        for(unsigned j = 0; j < columns; j++)
        {
            //Use space graphics if the space is not occupied.
            if(stage[i][j]->getOccupied() == false)
            {
                cout << setw(2) << getGraphics(stage[i][j]->getSpaceType());
            }

            else
            {

                //Print the character graphics.
                if(i == Player->getCoordinates().row && j == Player->getCoordinates().column)
                {
                    cout << setw(2) << playerGraphics; 
                }

                //Print the mob graphics.
                for(unsigned k = 0; k < mobNumber; k++)
                {
                    if(i == mob[k]->getCoordinates().row && j == mob[k]->getCoordinates().column) 
                    {
                        if(mob[k]->getDeadStatus() == false)
                        {
                            cout << ' ' << getMobGraphics(mob[k]->getMobType());
                        }

                        else
                        {
                            cout << setw(2) << 'x';
                        }
                    }
                }
            }
        }

        //Border.
        cout << " |"; 

        //Extra prints on the right side.
        if(i == 0) 
        {
            cout << "    Move: " << move;
        }

        if(i == 2)
        {
            cout << "    HP:   " << character->getHitPoints();
        }

        if(i == 3)
        {
            cout << "    Armor: " << character->getArmor();
        }

        cout << endl;
    }

    //Border.
    cout << ' ' << string((columns * 2) + 1, '-') << endl;

}

/***********************************************************************
 * ** Description: This function prints out the room to console. 
 * For player with HP and Armor. 
 *
 * Parameters: Character* - the character the function is checking. 
 *
 * Return: void. 
 * *********************************************************************/
void Room::printRoom(Character* character)
{
    //Border.
    cout << ' ' << string((columns * 2) + 1, '-') << endl;

    for(unsigned i = 0; i < rows; i++)
    {
        cout << '|';

        for(unsigned j = 0; j < columns; j++)
        {
            //Use space graphics if the space is not occupied.
            if(stage[i][j]->getOccupied() == false)
            {
                cout << setw(2) << getGraphics(stage[i][j]->getSpaceType());
            }

            else
            {

                //Print the character graphics.
                if(i == Player->getCoordinates().row && j == Player->getCoordinates().column)
                {
                    cout << setw(2) << playerGraphics; 
                }

                //Print the mob graphics.
                for(unsigned k = 0; k < mobNumber; k++)
                {
                    if(i == mob[k]->getCoordinates().row && j == mob[k]->getCoordinates().column) 
                    {
                        if(mob[k]->getDeadStatus() == false)
                        {
                            cout << ' ' << getMobGraphics(mob[k]->getMobType());
                        }

                        else
                        {
                            cout << setw(2) << 'x';
                        }
                    }
                }
            }
        }

        //Border.
        cout << " |"; 

        //Extra prints on the right side.
        if(i == 2)
        {
            cout << "    HP:   " << character->getHitPoints();
        }
        
        if(i == 3)
        {
            cout << "    Armor: " << character->getArmor();
        }

        cout << endl;
    }

    //Border.
    cout << ' ' << string((columns * 2) + 1, '-') << endl;

}

/***********************************************************************
 * ** Description: This function returns a char graphics that 
 * represents a mob.
 *
 * Parameters: MobType - enumerated data type that represents the mob.  
 *
 * Return: char - the mob graphics. 
 * *********************************************************************/
char Room::getMobGraphics(MobType type)
{
    char mobGraphics;

    switch(type)
    {
        case GOBLIN:
            mobGraphics = 'g';
            break;

        case ORC:
            mobGraphics = '@';
            break;

        case OGRE:
            mobGraphics = '&';
            break;
            
        case BANDIT:
            mobGraphics = 'b';
            break;

        case BANDIT_KING:
            mobGraphics = 'B';
            break;

        case PRINCESS:
            mobGraphics = 'P';
            break;

        case NONE:
            break;
    }

    return mobGraphics;
}

/***********************************************************************
 * ** Description: This function allows the user to control the player.  
 *
 * Parameters: unsigned - represents how many move points a character
 * has.  
 *
 * Return: void. 
 * *********************************************************************/
void Room::controlMenu(unsigned move)
{
    cout << hud() << endl << endl;

    //Print different displays depending
    //on battle status.
    if(inBattle)
    {
        printRoom(move, Player);     
    }

    else if(!inBattle)
    {
        printRoom(Player);     
    }

    cout << string("\nChoice: ");

    //User choice input.
    controlChoice = gameMenu.userInputString();

    if(controlChoice == "u")
    {
        playerDirection = UP;
        setPlayerGraphics(playerDirection);    
    }

    else if(controlChoice == "d")
    {
        playerDirection = DOWN;
        setPlayerGraphics(playerDirection);    
    }

    else if(controlChoice == "l")
    {
        playerDirection = LEFT;
        setPlayerGraphics(playerDirection);    
    }

    else if(controlChoice == "r")
    {
        playerDirection = RIGHT;
        setPlayerGraphics(playerDirection);    
    }
    
    else if(controlChoice == "f")
    {
        moveCharacter(Player);

        //Decrements the player's cold levels every time
        //the player chooses to go forward and does not have
        //a travel cloak.
        if(Player->checkForTravelCloak() == false)
        {
            cold--;
        }

        else if(cold < 300)
        {
            cold++;
        }

        //Counts down losing condition every time the user
        //chooses to go forward.
        princessCountDown--;
    }

    else if(controlChoice == "i")
    {
        interactEnvironment(Player);

        if(inBattle)
        {
            endPlayerTurn = true;
        }
    }

    else if(controlChoice == "quit")
    {
        controlChoice = " ";
    }

    else if(controlChoice == "e" && inBattle)
    {
        endPlayerTurn = true;
    }

    //Enters the in-game menu.
    else if(controlChoice == "m")
    {
        do
        {
            //Print display.
            cout << "\033[2J\033[1;1H";
            cout << hudPlayerMenu() << endl << endl;
            printRoom(Player);     
            cout << string("\nChoice: ");

            controlPlayerMenu = gameMenu.userInputString();

            //Displays the items in the backpack.
            if(controlPlayerMenu == "t")
            {
                Item** packContents;
                unsigned packSize;
                string deleteChoice = "";

                do
                {
                    packContents = Player->backpackContents();   
                    packSize = Player->getBackpackSize();

                    cout << "\033[2J\033[1;1H";
                    cout << "\n\n[Max 6] ITEMS:";

                    //Displays the items in the backpack.
                    for(unsigned i = 0; i < packSize; i++)
                    {
                        if(packContents[i] != nullptr)
                        {
                            cout << "\n " << packContents[i]->getItemName();
                        }
                    }

                    cout << "\n\nToss Items = \"toss\"";
                    cout << "\n\nGo Back = 'b'" << endl << endl;

                    printRoom(Player);     

                    cout << string("\nEnter the first letter of the item.\n");
                    cout << string("\nChoice: ");
                    
                    controlBackpack = gameMenu.userInputString();

                    //User chooses to delete items.
                    if(controlBackpack == "toss")
                    {
                        string tempCompare = "";
                        bool deletedItem = false;

                        do
                        {
                            deletedItem = false;
                            cout << "\033[2J\033[1;1H";
                            cout << "\n\nTOSS ITEMS:";

                            //Displays the items in the backpack.
                            for(unsigned i = 0; i < packSize; i++)
                            {
                                if(packContents[i] != nullptr)
                                {
                                    cout << '\n' << packContents[i]->getItemName();
                                }
                            }

                            cout << "\n\nGo Back = 'b'" << endl << endl;

                            printRoom(Player);     
                            cout << string("\nEnter the first letter of the item.\n");
                            cout << string("\nChoice: ");
                            
                            //user chooses which item to delete.
                            deleteChoice = gameMenu.userInputString();

                            for(unsigned i = 0; i < packSize && !deletedItem; i++) 
                            {
                                if(packContents[i] != nullptr)
                                {
                                    tempCompare = packContents[i]->getItemName()[0];
                                }

                                if(deleteChoice == tempCompare)
                                {
                                    if(deleteChoice == "m")
                                    {
                                        delete packContents[i]; 
                                        packContents[i] = nullptr;
                                        cout << "\nYou tossed medicinal herb." << endl;
                                        deletedItem = true;
                                        cin.ignore(INT_MAX, '\n');
                                    }

                                    else if(deleteChoice == "a")
                                    {
                                        delete packContents[i]; 
                                        packContents[i] = nullptr;
                                        cout << "\nYou tossed apple." << endl;
                                        deletedItem = true;
                                        cin.ignore(INT_MAX, '\n');
                                    }

                                    else if(deleteChoice == "t")
                                    {
                                        cout << "\nYou need this cloak to keep warm." << endl;
                                        deletedItem = true;
                                        cin.ignore(INT_MAX, '\n');
                                    }

                                    else if(deleteChoice == "h")
                                    {
                                        cout << "\nYou need this key." << endl;
                                        deletedItem = true;
                                        cin.ignore(INT_MAX, '\n');
                                    }
                                    
                                    else if(deleteChoice == "d")
                                    {
                                        cout << "\nYou need this key." << endl;
                                        deletedItem = true;
                                        cin.ignore(INT_MAX, '\n');
                                    }
                                }
                            }
                        } while(deleteChoice != "b");
                    }

                    //The player wants to choose an item to use.
                    else if(controlBackpack != "b")
                    {
                        string tempCompare = "";
                        bool usedItem = false;

                        //Iterates through every item in the backpack()
                        for(unsigned i = 0; i < packSize && !usedItem; i++) 
                        {
                            if(packContents[i] != nullptr)
                            {
                                tempCompare = packContents[i]->getItemName()[0];
                            }

                            if(controlBackpack == tempCompare)
                            {
                                if(controlBackpack == "m")
                                {
                                    if(Player->getHitPoints() < 12)
                                    {
                                        cout << "\nYou applied medicinal herb to your wounds." << endl;
                                        Player->recoverHitPoints(4);
                                        delete packContents[i];
                                        packContents[i] = nullptr;
                                        usedItem = true;
                                        endPlayerTurn = true;
                                    }

                                    else
                                    {
                                        cout << "\nYou do not need to mend any wounds." << endl;
                                        usedItem = true;
                                    }

                                    cin.ignore(INT_MAX, '\n');
                                }

                                else if(controlBackpack == "a")
                                {
                                    if(Player->getHitPoints() < 12)
                                    {
                                        cout << "\nYou hungrily ate an apple." << endl;
                                        Player->recoverHitPoints(2);
                                        delete packContents[i];
                                        packContents[i] = nullptr;
                                        usedItem = true;
                                        endPlayerTurn = true;
                                    }

                                    else if(Player->getHitPoints() == 12)
                                    {
                                        cout << "\nYou are not hungry." << endl;
                                        usedItem = true;
                                    }

                                    cin.ignore(INT_MAX, '\n');
                                }

                                else if(controlBackpack == "t")
                                {
                                    cout << "\nA very nice, warm, travel cloak." << endl;
                                    usedItem = true;
                                    cin.ignore(INT_MAX, '\n');
                                }

                                else if(controlBackpack == "h")
                                {
                                    cout << "\nA typical key used to open a door." << endl;
                                    usedItem = true;
                                    cin.ignore(INT_MAX, '\n');
                                }
                                
                                else if(controlBackpack == "d")
                                {
                                    cout << "\nA special key used to open a dungeon." << endl;
                                    usedItem = true;
                                    cin.ignore(INT_MAX, '\n');
                                }
                            }
                        }
                    }

                } while(controlBackpack != "b");
            }

            else if(controlPlayerMenu == "s")
            {
                Player->getStats();
            }

            else if(controlPlayerMenu == "quit")
            {
                char tempChoice = gameMenu.userInputYN(QUIT);

                //Asks a y/n question to make sure the
                //player wants to quit.
                if(tempChoice == 'y')
                {
                    controlChoice = "quit";
                    controlPlayerMenu = "b";
                }
            }

        } while(controlPlayerMenu != "b"); 
    }
}

/***********************************************************************
 * ** Description: This function returns a string that is the hud of the
 * room.  
 *
 * Parameters: string - represents the display. 
 * has.  
 *
 * Return: void. 
 * *********************************************************************/
string Room::hud() const
{
    string control = 
    
      string("\n\nCONTROLS: ")
    + string("\nFace Up    = 'u'") + string("      ") + string("Interact = 'i'")
    + string("\nFace Down  = 'd'") + string("      ") + string("Menu     = 'm'")
    + string("\nFace Left  = 'l'") 
    + string("\nFace Right = 'r'");

    if(inBattle) 
    {
      control += string("      ");
      control += string("End Turn = 'e'");
    }

    control += string("\nForward    = 'f'");

    control += string("\n\n") + string("Bandits Escape: ") + to_string(princessCountDown);
    control += string("\n") + string("Hypothermia: ") + to_string(cold);

    return control;
}

/***********************************************************************
 * ** Description: This function returns a string that is the sub-hud of 
 * the room.  
 *
 * Parameters: string - represents the display. 
 * has.  
 *
 * Return: void. 
 * *********************************************************************/
string Room::hudPlayerMenu() const
{
    string control = 
    
      string("\n\nMENU: ")
    + string("\nTravel Pack  = 't'") + string("  ") + string("Quit Game = \"quit\"")
    + string("\nPlayer Stats = 's'") 
    + string("\n")
    + string("\nGo Back      = 'b'")
    + string("\n");

    control += string("\n\n") + string("Bandits Escape: ") + to_string(princessCountDown);
    control += string("\n") + string("Hypothermia: ") + to_string(cold);

    return control;
}

/***********************************************************************
 * ** Description: This function allows the user to make the character 
 * interact with the environment.  
 *
 * Parameters: Character* - the character to be used to interact with the
 * environment.  
 *
 * Return: void. 
 * *********************************************************************/
void Room::interactEnvironment(Character* character)
{
    int rowCoord = character->getCoordinates().row;
    int colCoord = character->getCoordinates().column;

    //This pointer to Space is set to the current position
    //of the player.
    Space* interactSpace = stage[character->getCoordinates().row][character->getCoordinates().column];

    //These if statements changes the coordinates by one depending on 
    //what direction the player is facing.
    if(playerDirection == UP)
    {
        rowCoord--;
        interactDirection(UP, interactSpace, rowCoord, colCoord);
    }
    
    else if(playerDirection == DOWN)
    {
        rowCoord++; 
        interactDirection(DOWN, interactSpace, rowCoord, colCoord);
    }

    else if(playerDirection == LEFT)
    {
        colCoord--;
        interactDirection(LEFT, interactSpace, rowCoord, colCoord);
    }

    else if(playerDirection == RIGHT)
    {
        colCoord++;
        interactDirection(RIGHT, interactSpace, rowCoord, colCoord);
    }
}

/***********************************************************************
 * ** Description: This function allows the user to make the character 
 * interact with the environment.  
 *
 * Parameters: 
 * 1. An enumerated data type that represents the direction the character
 * is facing.
 * 2. Space* - A pointer to space which checks the space type or whether
 * it is occupied by another character.
 * 3. int(s) - coordinate of the player.
 *
 * Return: void. 
 * *********************************************************************/
void Room::interactDirection(Directions facing, Space* interactSpace, unsigned row, unsigned col)
{
    Space* currentSpace = interactSpace;

    //The player stands facing the border.
    if(interactSpace->traverse(facing) == nullptr)
    {
        //Interact with the current space.
        interactSpace->interact();
        cin.ignore(INT_MAX, '\n');
    }

    else
    {
        interactSpace = interactSpace->traverse(facing);

        //If the space ahead is occupied and battle is commencing.
        if(interactSpace->getOccupied() == true && inBattle)
        {
            //Peform battle functions.
            for(unsigned i = 0; i < mobNumber; i++)
            {
                //Checks to see if the space ahead of the player has a mob on it.
                if(mob[i]->getCoordinates().row == row && mob[i]->getCoordinates().column == col)
                {
                    //Attack the mob of it's not dead yet.
                    if(mob[i]->getDeadStatus() == false)
                    {
                        mob[i]->defend(Player->attack());
                        endPlayerTurn = true;
                        cin.ignore(INT_MAX, '\n');
                    }

                    else
                    {
                        cout << '\n' << mob[i]->getIdentity() << " is already dead..." << endl;
                        cin.ignore(INT_MAX, '\n');
                    }
                }
            }
        }

        //If the space ahead is occupied and battle is commencing.
        else if(interactSpace->getOccupied() == true && !inBattle)
        {
            for(unsigned i = 0; i < mobNumber; i++)
            {
                if(mob[i]->getCoordinates().row == row && mob[i]->getCoordinates().column == col)
                {
                    if(mob[i]->getDeadStatus() == true)
                    {
                        cout << "\n You see the dead body of " << mob[i]->getIdentity() << '.' << endl;
                        Player->grabLoot(mob[i]);
                        cin.ignore(INT_MAX, '\n');
                    }

                    else if(mob[i]->getDeadStatus() == false)
                    {
                        //The only character you'll interact with that is
                        //not dead in this game is the princess. Therefore,
                        //this is an end game condition.
                        endGame = mob[i]->interact();
                    }
                }
            }
        }

        //The Ground type will interact with the Ground the
        //player is standing on. Not the Ground ahead.
        else if(interactSpace->getSpaceType() == GROUND)
        {
            currentSpace->interact();
            cin.ignore(INT_MAX, '\n');
        }

        //Interacting with a Campfire space will recover
        //some warmth (up to 10 pts).
        else if(interactSpace->getSpaceType() == CAMPFIRE)
        {
            int warmth = cold;
            
            interactSpace->interact();

            cout << endl;

            for(unsigned i = 0; i < 10 && cold < 300; i++)
            {
                ++cold;
            }

            cout << " +" << (cold - warmth) << " warmth";
            cin.ignore(INT_MAX, '\n');
        }

        //Interacting with a door will check to see if
        //the player has a key first.
        else if(interactSpace->getSpaceType() == DOOR)
        {
            if(Player->checkForKey() == true)
            {
                delete stage[Player->getCoordinates().row][Player->getCoordinates().column + 1];
                stage[Player->getCoordinates().row][Player->getCoordinates().column + 1] = new Ground;
                connectSpaces();
            }
        }

        else if(interactSpace->getSpaceType() == ROCK)
        {
            interactSpace->interact();
            cout << endl;
            cin.ignore(INT_MAX, '\n');
        }

        //Interact with the space ahead and try to
        //grab any loot it might contain.
        else
        {
            interactSpace->interact();
            cout << endl;
            Player->grabLoot(interactSpace);
            cin.ignore(INT_MAX, '\n');
        }
    }
}

/***********************************************************************
 * ** Description: This function allows the character to traverse the
 * spaces.
 *
 * Parameters: Character* - the character that will be moving.
 *
 * Return: void. 
 * *********************************************************************/
void Room::moveCharacter(Character* character)
{
    Space* moveSpace = stage[character->getCoordinates().row][character->getCoordinates().column];

    if(playerDirection == UP)
    {
        moveDirection(UP, moveSpace); 
    }
    
    else if(playerDirection == DOWN)
    {
        moveDirection(DOWN, moveSpace); 
    }
    
    else if(playerDirection == LEFT)
    {
        moveDirection(LEFT, moveSpace); 
    }

    else if(playerDirection == RIGHT)
    {
        moveDirection(RIGHT, moveSpace); 
    }
}

/***********************************************************************
 * ** Description: This function allows the character to traverse the
 * spaces.
 *
 * Parameters: 
 * 1. An enumerated data type that represents the direction the character
 * is facing.
 * 2. Space* - A pointer to space which is used to check whether or not
 * the space is a border space or whether the space type is one characters
 * can walk on.
 *
 * Return: void. 
 * *********************************************************************/
void Room::moveDirection(Directions facing, Space* moveSpace)
{        
    Space* currentSpace = moveSpace;

    if(moveSpace->traverse(facing) == nullptr)
    {
        if(inBattle)
        {
            cout << "\nYou cannot leave the battle!" << endl; 
            cin.ignore(INT_MAX, '\n');
        }

        //The following if statements set the information
        //to be able to transition between rooms.
        else if(facing == UP && north != nullptr)  
        {
            if(north->getRoomType() == BEFORE_INTERSECTION)   
            {
                moveToRoom = BEFORE_INTERSECTION;        
                unPlaceCharacter(Player);
                movingDirection = UP;

                //This sets the player direction
                //and graphics if the player returns
                //to the room.
                playerDirection = DOWN;
                playerGraphics = 'v';
            }

            else if(north->getRoomType() == INTERSECTION)   
            {
                moveToRoom = INTERSECTION;        
                unPlaceCharacter(Player);
                movingDirection = UP;
                playerDirection = DOWN;
                playerGraphics = 'v';
            }

            else if(north->getRoomType() == DEAD_END)   
            {
                moveToRoom = DEAD_END;        
                unPlaceCharacter(Player);
                movingDirection = UP;
                playerDirection = DOWN;
                playerGraphics = 'v';
            }


        }

        else if(facing == DOWN && south != nullptr)
        {
            if(south->getRoomType() == BEGIN)   
            {
                moveToRoom = BEGIN;        
                unPlaceCharacter(Player);
                movingDirection = DOWN;
                playerDirection = UP;
                playerGraphics = '^';
            }

            else if(south->getRoomType() == BEFORE_INTERSECTION)   
            {
                moveToRoom = BEFORE_INTERSECTION;        
                unPlaceCharacter(Player);
                movingDirection = DOWN;
                playerDirection = UP;
                playerGraphics = '^';
            }

            else if(south->getRoomType() == INTERSECTION)   
            {
                moveToRoom = INTERSECTION;        
                unPlaceCharacter(Player);
                movingDirection = DOWN;
                playerDirection = UP;
                playerGraphics = '^';
            }
        }

        else if(facing == RIGHT && east != nullptr)
        {
            if(east->getRoomType() == HIDEOUT)   
            {
                moveToRoom = HIDEOUT;        
                unPlaceCharacter(Player);
                movingDirection = RIGHT;
                playerDirection = LEFT;
                playerGraphics = '<';
            }

            else if(east->getRoomType() == DUNGEON)   
            {
                moveToRoom = DUNGEON;        
                unPlaceCharacter(Player);
                movingDirection = RIGHT;
                playerDirection = LEFT;
                playerGraphics = '<';
            }
        }

        else if(facing == LEFT && west != nullptr)
        {
            if(west->getRoomType() == HIDEOUT)   
            {
                moveToRoom = HIDEOUT;        
                unPlaceCharacter(Player);
                movingDirection = LEFT;
                playerDirection = RIGHT;
                playerGraphics = '>';
            }

            else if(west->getRoomType() == INTERSECTION)   
            {
                moveToRoom = INTERSECTION;        
                unPlaceCharacter(Player);
                movingDirection = LEFT;
                playerDirection = RIGHT;
                playerGraphics = '>';
            }
        }

        else
        {
            cout << "\nYou cannot move past here!" << endl; 
            cin.ignore(INT_MAX, '\n');
        }
    }

    else
    {
        moveSpace = moveSpace->traverse(facing);

        if(moveSpace->getSpaceType() != GROUND) 
        {
            cout << "\nThere is something in the way!" << endl; 
            cin.ignore(INT_MAX, '\n');
        }

        else if(moveSpace->getOccupied() == true) 
        {
            cout << "\nThere is somebody in the way!" << endl; 
            cin.ignore(INT_MAX, '\n');
        }

        else if(moveSpace->getSpaceType() == GROUND) 
        {
            //Move the player and set occupied status on spaces.
            currentSpace->setOccupied(false);
            Player->moveCharacter(facing); 
            moveSpace->setOccupied(true);
        }
    }
}

/***********************************************************************
 * ** Description: This function tries to move the mob towards the
 * "facing" direction. If it cannot because there is something in the
 * way it will skip its turn. Depending on the recursionLimit value the
 * mob will try to move a different direction the amount of times equal 
 * to the recursionLimit number. The order it will try to move is
 * RIGHT, LEFT, DOWN, UP, because of how enumerated values work. If the
 * recursionLimit is set to 4, it will check each direction to see if
 * it's available to make a move.
 * 
 * Parameters: 
 * 1. An enumerated data type that represents the direction the mob 
 * is facing.
 * 2. Space* - the current space the mob is located on.
 * 3. Character* - the actual mob.
 * 4. int - the number of times the mob will try to move.  
 *
 * Return: void. 
 * *********************************************************************/
void Room::mobMove(Directions facing, Space* moveSpace, Character* character, int recursionLimit)
{        
    Space* currentSpace = moveSpace;

    if(endMobTurn == false) 
    {
        //Checks if the space the mob is trying to move is a border.
        if(moveSpace->traverse(facing) == nullptr)
        {
            if(recursionLimit > 0)
            {
                --recursionLimit;
                facing = static_cast<Directions>(recursionLimit);
                mobMove(facing, currentSpace, character, recursionLimit);
                endMobTurn = true;
            }

            else if(recursionLimit <= 1)
            {
                cout << '\n' << character->getIdentity() << " decides to skip the turn!" << endl;
                endMobTurn = true;
                cin.ignore(INT_MAX, '\n');
            }
        }

        else
        {
            //Sets moveSpace to one space ahead of the direction the mob wants to move.
            //This is used to check whether or not the space ahead is available to move.
            moveSpace = moveSpace->traverse(facing);

            if(moveSpace->getOccupied() == true || moveSpace->getSpaceType() != GROUND)
            {
                if(recursionLimit <= 1)
                {
                    cout << '\n' << character->getIdentity() << " decides to skip the turn!" << endl;
                    endMobTurn = true;
                    cin.ignore(INT_MAX, '\n');
                }

                else if(recursionLimit > 0)
                {
                    facing = static_cast<Directions>(--recursionLimit);
                    mobMove(facing, currentSpace, character, recursionLimit);
                    endMobTurn = true;
                }
            }

            else
            {
                //Move the player and set occupied status on spaces.
                currentSpace->setOccupied(false);
                character->moveCharacter(facing); 
                moveSpace->setOccupied(true);
            }
        }
    }

    else
    {
        cout << '\n' << character->getIdentity() << " skips turn!" << endl;
        endMobTurn = true;
        cin.ignore(INT_MAX, '\n');
    }
}

/***********************************************************************
 * ** Description: This function receives the first number in the
 * mobs .txt file. This number is the total amount of mobs in the room. 
 *
 * Parameters: none.
 *
 * Return: unsigned - the number of mobs in the room. 
 * *********************************************************************/
unsigned Room::countMob()
{
    unsigned mobCount;

    countMobFile.open(mobsInput);

    if(!countMobFile)
    {
        cout << "\nThe file failed to open!!" << endl;
    }

    else
    {
        countMobFile >> mobCount;
    }

    countMobFile.close();

    return mobCount;
}

/***********************************************************************
 * ** Description: This function creates and places the mobs in the room 
 * according to the mobs .txt file. 
 *
 * Parameters: none.
 *
 * Return: void. 
 * *********************************************************************/
void Room::createMobs()
{
    string mobType;
    unsigned row,
             column;
    ifstream inputFile;

    inputFile.open(mobsInput);

    if(!inputFile)
    {
        cout <<"\nThe " << mobsInput << " file could not open!!" << endl;
    }

    else
    {
        //Skip the first number in the file because it is
        //the mob count information.
        inputFile >> row;

        //Retrieves mob generation data from the .txt file.
        for(unsigned i = 0; i < mobNumber; i++)
        {
            inputFile >> mobType;
            inputFile >> row;
            inputFile >> column;

            mob[i] = generateMob(mobType, row, column);
        }
    }

    inputFile.close();


    //Gives special items to characters as
    //the mobs iterrate through.
    for(unsigned i = 0; i < mobNumber; i++)
    {
        if(mob[i]->getIdentity() == "a person")
        {
            mob[i]->giveItem(KEY_HIDEOUT);
        }

        if(mob[i]->getIdentity() == "Orc 1")
        {
            mob[i]->giveItem(CLOAK);
        }

        if(mob[i]->getIdentity() == "Billy the Bandit")
        {
            mob[i]->giveItem(KEY_DUNGEON);
        }
    }
}

/***********************************************************************
 * ** Description: This function creates new mobs in heap using the
 * mobs .txt config file. It determines what mob to create based on the
 * character in the .txt file.
 *
 * Parameters: 
 * 1. string - represents mob.
 * 2. unsigned row & column - represents the mob coordinates.
 *
 * Return: Character* - represents the mob that was created. 
 * *********************************************************************/
Character* Room::generateMob(const string &mob, unsigned row, unsigned column)
{
    Character* returningMob = nullptr;

    if(mob == "g")
    {
        returningMob = new Goblin(row, column);
    }

    else if(mob == "c")
    {
        returningMob = new Orc(row, column);
    }
    
    else if(mob == "o")
    {
        returningMob = new Ogre(row, column);
    }
    
    else if(mob == "b")
    {
        returningMob = new Bandit(row, column);
    }

    else if(mob == "B")
    {
        returningMob = new Billy(row, column);
    }

    else if(mob == "d")
    {
        returningMob = new DeadGuy(row, column);
    }
    
    else if(mob == "p")
    {
        returningMob = new Princess(row, column);
    }

    return returningMob;
}

/***********************************************************************
 * ** Description: This function marks the space occupied by mobs as 
 * being occupied.
 *
 * Parameters: none.
 *
 * Return: void. 
 * *********************************************************************/
void Room::placeMobs()
{
    for(unsigned i = 0; i < mobNumber; i++)
    {
        placeCharacter(mob[i]);
    }
}

/***********************************************************************
 * ** Description: This function prints out the heads up display to
 * console.
 *
 * Parameters: none.
 *
 * Return: void. 
 * *********************************************************************/
void Room::printHud() 
{
    cout << "\033[2J\033[1;1H";
    cout << hud() << endl << endl;
    printRoom();
}

/***********************************************************************
 * ** Description: This function is the enemy AI movement and attack
 * when it is the mob's turn. The mob will try to find the shortest
 * path to the player. If the mob get's stuck, it will try to find an
 * opening. Otherwise the mob will skip its turn.
 *
 * *Note*: This is a very basic AI. The mobs will often dance (move back
 * and forth). I could have probably shortened the code but it was too
 * late.
 * 
 * Parameters: Character* - the mob who's turn it is to move and attack.
 *
 * Return: void. 
 * *********************************************************************/
void Room::mobTurn(Character* mobMoving)
{
    int mobRow = mobMoving->getCoordinates().row;
    int mobColumn = mobMoving->getCoordinates().column;

    //Difference between the mob and the player, used to
    //determine which way to go.
    int rowDiff = mobRow - Player->getCoordinates().row;
    int columnDiff = mobColumn - Player->getCoordinates().column;

    Space* checkSpace = stage[mobRow][mobColumn];

    rowDiff = abs(rowDiff);
    columnDiff = abs(columnDiff);

    unsigned randomMove = rand() % 2 + 1;

    //Checks to see if the mob can attack the player without moving.
    if((rowDiff == 0 && columnDiff == 1) || (columnDiff == 0 && rowDiff == 1))
    {
        Player->defend(mobMoving->attack());
        endMobTurn = true;
        cin.ignore(INT_MAX, '\n');
    }
    
    //Moves the mob, then attacks if possible.
    else
    {
        //Randomly choose to move up/down.
        if(randomMove == 1)  
        {
            //Mob needs to move down. 
            if(mobMoving->getCoordinates().row < Player->getCoordinates().row)
            {
                checkSpace = checkSpace->traverse(DOWN); 

                //Checks to see if space can be moved into.
                if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(DOWN, checkSpace, mobMoving, 0);

                }

                //Mob needs to move right.
                else if(mobMoving->getCoordinates().column < Player->getCoordinates().column)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(RIGHT);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];

                        //Recursion to check available spaces around the mob.
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                //Mob needs to move left.
                else if(mobMoving->getCoordinates().column > Player->getCoordinates().column)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(LEFT);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(LEFT, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                else
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(RIGHT, checkSpace, mobMoving, 4);
                }
            }
            
            //Mob needs to move up. 
            else if(mobMoving->getCoordinates().row > Player->getCoordinates().row)
            {
                checkSpace = stage[mobRow][mobColumn];
                checkSpace = checkSpace->traverse(UP); 

                //Checks to see if space can be moved into.
                if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(UP, checkSpace, mobMoving, 0);
                }

                //Mob needs to move right.
                else if(mobMoving->getCoordinates().column < Player->getCoordinates().column)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(RIGHT);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                //Mob needs to move left.
                else if(mobMoving->getCoordinates().column > Player->getCoordinates().column)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(LEFT);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(LEFT, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                else
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(RIGHT, checkSpace, mobMoving, 4);
                }
            }
            
            //Mob needs to move left. 
            else if(mobMoving->getCoordinates().column > Player->getCoordinates().column)
            {
                checkSpace = stage[mobRow][mobColumn];
                checkSpace = checkSpace->traverse(LEFT); 

                //Checks to see if space can be moved into.
                if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(LEFT, checkSpace, mobMoving, 0);
                }

                //Mob needs to move down.
                else if(mobMoving->getCoordinates().row < Player->getCoordinates().row)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(DOWN);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(DOWN, checkSpace, mobMoving, 0);
                    }
                    
                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                //Mob needs to move up.
                else if(mobMoving->getCoordinates().row > Player->getCoordinates().row)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(UP);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(UP, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                else
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(RIGHT, checkSpace, mobMoving, 4);
                }
            }

            //Mob needs to move right. 
            else if(mobMoving->getCoordinates().column < Player->getCoordinates().column)
            {
                checkSpace = stage[mobRow][mobColumn];
                checkSpace = checkSpace->traverse(RIGHT); 

                //Checks to see if space can be moved into.
                if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(RIGHT, checkSpace, mobMoving, 0);
                }

                //Mob needs to move down.
                else if(mobMoving->getCoordinates().row < Player->getCoordinates().row)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(DOWN);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(DOWN, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                //Mob needs to move up.
                else if(mobMoving->getCoordinates().row > Player->getCoordinates().row)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(UP);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(UP, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                else
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(RIGHT, checkSpace, mobMoving, 4);
                }
            }
                    
            //Reset difference in location between mob and player.
            rowDiff = mobMoving->getCoordinates().row - Player->getCoordinates().row;
            columnDiff = mobMoving->getCoordinates().column - Player->getCoordinates().column;

            printHud();
            mobAttacksPlayer(abs(rowDiff), abs(columnDiff), mobMoving);
        }

        //Randomly choose to move left/right.
        else if(randomMove == 2)
        {
            checkSpace = stage[mobRow][mobColumn];
           
            //Mob needs to move left. 
            if(mobMoving->getCoordinates().column > Player->getCoordinates().column)
            {
                checkSpace = stage[mobRow][mobColumn];
                checkSpace = checkSpace->traverse(LEFT); 

                //Checks to see if space can be moved into.
                if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(LEFT, checkSpace, mobMoving, 0);
                }

                //Mob needs to move down.
                else if(mobMoving->getCoordinates().row < Player->getCoordinates().row)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(DOWN);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(DOWN, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                //Mob needs to move up.
                else if(mobMoving->getCoordinates().row > Player->getCoordinates().row)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(UP);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(UP, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                else
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(RIGHT, checkSpace, mobMoving, 4);
                }
            }

            //Mob needs to move right. 
            else if(mobMoving->getCoordinates().column < Player->getCoordinates().column)
            {
                checkSpace = stage[mobRow][mobColumn];
                checkSpace = checkSpace->traverse(RIGHT); 

                //Checks to see if space can be moved into.
                if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(RIGHT, checkSpace, mobMoving, 0);
                }

                //Mob needs to move down.
                else if(mobMoving->getCoordinates().row < Player->getCoordinates().row)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(DOWN);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(DOWN, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                //Mob needs to move up.
                else if(mobMoving->getCoordinates().row > Player->getCoordinates().row)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(UP);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(UP, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                else
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(RIGHT, checkSpace, mobMoving, 4);
                }
            }
            
            //Mob needs to move down. 
            else if(mobMoving->getCoordinates().row < Player->getCoordinates().row)
            {
                checkSpace = checkSpace->traverse(DOWN); 

                //Checks to see if space can be moved into.
                if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(DOWN, checkSpace, mobMoving, 0);
                }

                //Mob needs to move right.
                else if(mobMoving->getCoordinates().column < Player->getCoordinates().column)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(RIGHT);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                //Mob needs to move left.
                else if(mobMoving->getCoordinates().column > Player->getCoordinates().column)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(LEFT);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(LEFT, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                else
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(RIGHT, checkSpace, mobMoving, 4);
                }
            }
            
            //Mob needs to move up. 
            else if(mobMoving->getCoordinates().row > Player->getCoordinates().row)
            {
                checkSpace = stage[mobRow][mobColumn];
                checkSpace = checkSpace->traverse(UP); 

                //Checks to see if space can be moved into.
                if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(UP, checkSpace, mobMoving, 0);
                }

                //Mob needs to move right.
                else if(mobMoving->getCoordinates().column < Player->getCoordinates().column)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(RIGHT);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                //Mob needs to move left.
                else if(mobMoving->getCoordinates().column > Player->getCoordinates().column)
                {
                    checkSpace = stage[mobRow][mobColumn];
                    checkSpace = checkSpace->traverse(LEFT);

                    if(checkSpace->getSpaceType() == GROUND && checkSpace->getOccupied() == false) 
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(LEFT, checkSpace, mobMoving, 0);
                    }

                    else
                    {
                        checkSpace = stage[mobRow][mobColumn];
                        mobMove(RIGHT, checkSpace, mobMoving, 4);
                    }
                }

                else
                {
                    checkSpace = stage[mobRow][mobColumn];
                    mobMove(RIGHT, checkSpace, mobMoving, 4);
                }
            }
            
            //Reset difference in location between mob and player.
            rowDiff = mobMoving->getCoordinates().row - Player->getCoordinates().row;
            columnDiff = mobMoving->getCoordinates().column - Player->getCoordinates().column;

            printHud();
            mobAttacksPlayer(abs(rowDiff), abs(columnDiff), mobMoving);
        }
    }
}

/***********************************************************************
 * ** Description: This function is the mob's attempt to attack the
 * player. The function checks if the player is to the left, right, down,
 * or up relative to the mob. If the player is in one of those locations
 * they will be attacked.
 *
 * Parameters: 
 * 1. unsigned - The row difference between the mob and the player.
 * 2. unsigned - The column difference between the mob and the player.
 * 3. Character* - the mob who's turn it is to move and attack.
 *
 * Return: void. 
 * *********************************************************************/
void Room::mobAttacksPlayer(unsigned rowDiff, unsigned columnDiff, Character* mob)
{
    if((rowDiff == 0 && columnDiff == 1) || (columnDiff == 0 && rowDiff == 1))
    {
        Player->defend(mob->attack());
        endMobTurn = true;
        cin.ignore(INT_MAX, '\n');
    }
}

void Room::setNorth(Room* direction)
{
    north = direction;
}

void Room::setSouth(Room* direction)
{
    south = direction;
}

void Room::setEast(Room* direction)
{
    east = direction;
}

void Room::setWest(Room* direction)
{
    west = direction;
}

RoomType Room::getRoomType() const
{
    return roomType;
}

RoomType Room::getMoveToRoom() const
{
    return moveToRoom;
}

void Room::resetMoveToRoom()
{
    moveToRoom = NO_TRANSITION;
}

Directions Room::getMovingDirection() const
{
    return movingDirection;
}

bool Room::getEndGame() const
{
    return endGame;
}
    
/***********************************************************************
 * ** Description: This function initiates the room functions. It also
 * controls the scenes and the flow of battle vs not in battle. It checks
 * all losing conditions.  
 *
 * Parameters: none.
 *
 * Return: void. 
 * *********************************************************************/
void Room::initiate()
{
    unsigned playerMoveNum = Player->getMoveNumber();
    unsigned mobMove = 1; 

    placeCharacter(Player);

    //The following if statements are just beginning scenes when you
    //walk into the room. Keep hitting the enter key to progress.
    if(roomType == BEGIN && inBattle)
    {
            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nGoblin 1: Why do we always have to do guard duty?!";
            cout << "\n          It's freezing out here. Ugh...\n\n";
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nGoblin 2: At least we have this fire going.\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nGoblin 1: I overheard Billy gave orders";
            cout << "\n          that we're moving out soon.\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nGoblin 2: They never tell us anything...";
            cout << "\n          ...it's almost as if we're expendable.\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nGoblin 1: Yeah... I wonder if anyone would";
            cout << "\n          know if we needed backup.\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nGoblin 2: ...or even care? ... ... ...";
            cout << "\n          What the deuce?? Who goes there!?\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nGoblin 1: Grab your spear!\n\n\n\n" << endl; 
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nIsa: ... \n\n\n\n" << endl; 
            printRoom();     
            cin.ignore(INT_MAX, '\n');
    }
    
    else if(roomType == BEFORE_INTERSECTION && inBattle)
    {
            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nGoblin 3: Do you guys ever talk.\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nORC 1: No.\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nGoblin 3: ... \n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nORC 2: ...\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nGoblin 3: FINE.\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nORC 1: *BATTLE CRY*\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nGoblin 3: WHY?! @#$@!!! ... who's that?!\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nIsa: ... \n\n\n\n" << endl; 
            printRoom();     
            cin.ignore(INT_MAX, '\n');
    }

    else if(roomType == DEAD_END && inBattle)
    {
            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nOgre 1: ... \n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nIsa: ... \n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nOgre 1: ... \n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nIsa: ... \n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nOgre 1: *BATTLE CRY* *GURGLES*.\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nIsa: ... \n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');
    }
    
    if(roomType == HIDEOUT && inBattle)
    {
            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nBandit 1: So... Bored...\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nBilly: Then make me coffee!\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nBandit 1: ... No.\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nBilly: ...insubordination!!\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nBandit 1: Whatever.\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nBilly: Whos that?!!\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nBandits: FINALLY! Something to do!\n\n\n\n" << endl;
            printRoom();     
            cin.ignore(INT_MAX, '\n');

            cout << "\033[2J\033[1;1H";
            cout << "\n\n\nSCENE:    <press enter>\n\n";
            cout << "\nIsa: ...die... \n\n\n\n" << endl; 
            printRoom();     
            cin.ignore(INT_MAX, '\n');
    }

    //The flow of battle.
    if(inBattle == true)
    {

        do
        {
            endPlayerTurn = false;

            //Player's turn.
            while(playerMoveNum != 0 && !endPlayerTurn && inBattle && !endGame && controlChoice != "quit")
            {
                cout << "\033[2J\033[1;1H";
                controlMenu(playerMoveNum);
                
                if(controlChoice == "f")
                {
                    playerMoveNum--;
                }

                //Checks losing conditions.
                if(Player->getDeadStatus() == true)
                {
                    cout << "\nYou have died..." << endl;
                    cout << "\nGAME OVER";
                    cin.ignore(INT_MAX, '\n');
                    controlChoice = "quit";
                    endGame = true;
                }

                //Checks losing conditions.
                if(cold <= 0 || princessCountDown <= 0)
                {
                    if(cold <= 0)
                    {
                        cout << "\nYou have DIED from hypothermia." << endl;
                    }

                    else if(princessCountDown <= 0)
                    {
                        cout << "\nThe bandits have escaped with the princess..." << endl;
                    }

                    cout << "\n                 GAME OVER";
                    cin.ignore(INT_MAX, '\n');
                    controlChoice = "quit";
                    endGame = true;
                }
            }

            playerMoveNum = Player->getMoveNumber();
            
            //End battle conditions.
            for(unsigned i = 0; i < mobNumber && inBattle && !endGame && controlChoice != "quit"; i++)
            {
                unsigned countDead = 0;

                if(mob[i]->getDeadStatus() == true)
                {
                    countDead++;
                }

                if(countDead == mobNumber)
                {
                    inBattle = false;
                }
            }

            //The mob's turn.
            for(unsigned i = 0; i < mobNumber && inBattle && !endGame && controlChoice != "quit"; i++)
            {
                endMobTurn = false;
                mobMove = mob[i]->getMoveNumber();

                while(mobMove != 0 && inBattle && !mob[i]->getDeadStatus() && !endMobTurn && !endGame && controlChoice != "quit")
                {
                    cout << "\033[2J\033[1;1H";
                    cout << hud() << endl << endl;
                    printRoom(mobMove, mob[i]);
                    usleep(505000);
                    mobTurn(mob[i]);

                    //The losing counters still function during
                    //the mob's movements.
                    if(Player->checkForTravelCloak() == false)
                    {
                        cold--;
                    }

                    else if(cold < 300)
                    {
                        cold++;
                    }

                    princessCountDown--;
                    mobMove--;

                    //Checks losing conditions.
                    if(cold <= 0 || princessCountDown <= 0)
                    {
                        if(cold <= 0)
                        {
                            cout << "\nYou have DIED from hypothermia." << endl;
                        }

                        else if(princessCountDown <= 0)
                        {
                            cout << "\nThe bandits have escaped with the princess..." << endl;
                        }

                        cout << "\n                 GAME OVER";
                        cin.ignore(INT_MAX, '\n');
                        controlChoice = "quit";
                        endGame = true;
                    }
                }
                
                //Check losing conditions.
                if(Player->getDeadStatus() == true)
                {
                    cout << "\nYou have been slain..." << endl;

                    cout << "\n    GAME OVER";
                    cin.ignore(INT_MAX, '\n');
                    controlChoice = "quit";
                    endGame = true;
                }

                bool allMobDead = true;

                //Check end battle
                for(unsigned i = 0; i < mobNumber && !endGame; i++)
                {
                    if(mob[i]->getDeadStatus() == false)
                    {
                        allMobDead = false; 
                    }
                }

                //Starts the control loop again out of battle if
                //all mobs are dead.
                if(allMobDead)
                {
                    inBattle = false;
                    
                    while(controlChoice != "quit" && !endGame)
                    {
                        cout << "\033[2J\033[1;1H";
                        controlMenu(playerMoveNum);

                        if(cold <= 0 || princessCountDown <= 0)
                        {
                            //Checks losing conditions.
                            if(cold <= 0)
                            {
                                cout << "\nYou have DIED from hypothermia." << endl;
                            }

                            else if(princessCountDown <= 0)
                            {
                                cout << "\nThe bandits have escaped with the princess..." << endl;
                            }

                            cout << "\n                 GAME OVER";
                            cin.ignore(INT_MAX, '\n');
                            controlChoice = "quit";
                            endGame = true;
                        }

                        else if(moveToRoom != NO_TRANSITION)
                        {
                            controlChoice = "quit";
                        }
                    }
                }
            }

        } while(controlChoice != "quit" && !endGame); 
    }

    //This control loop is for when the room starts not in battle.
    else 
    {
        do
        {
            cout << "\033[2J\033[1;1H";
            controlMenu(playerMoveNum);

            if(cold <= 0 || princessCountDown <= 0)
            {
                //Checks losing conditions.
                if(cold <= 0)
                {
                    cout << "\nYou have DIED from hypothermia." << endl;
                }

                else if(princessCountDown <= 0)
                {
                    cout << "\nThe bandits have escaped with the princess..." << endl;
                }

                cout << "\n            GAME OVER";
                cin.ignore(INT_MAX, '\n');
                controlChoice = "quit";
                endGame = true;
            }

            else if(moveToRoom != NO_TRANSITION)
            {
                controlChoice = "quit";
            }

        } while(controlChoice != "quit" && !endGame);
    }
}
