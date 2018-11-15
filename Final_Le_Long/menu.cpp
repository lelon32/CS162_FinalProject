/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: The Menu class serves as a menu template for command 
 * line interface programs created in C++. The menu is constantly being 
 * improved to allow easier transfer to other programs. The menu display 
 * is customizable and need to be edited in the header file and in the 
 * implementation file. 
 *
 * MUST EDIT:
 * 1. Header File - Please add any additional necessary header files,
 * member variables, and public and private member functions.
 * 2. Constructor - The main menu and the submenu print statements will
 * be edited in the constructor.
 * 3. printMenuOptions - Add any extra menu print statements. 
 * 4. enum MenuOptions - Edit what the data types contain to match the 
 * menu options.
 *
 * Note: To use this class for a program, the commented sections marked 
 * for editing and adding code will guide the process.
 * *********************************************************************/
#include "menu.hpp"

/***********************************************************************
 * ** Description: This is the constructor for the Menu class where all 
 * the member variables are initialized. The strings that will display in 
 * the main menus of the program are edited here. If more options are
 * added to the program, the initiateMenu() function needs to be changed 
 * to reflect the new options.
 * *********************************************************************/
Menu::Menu():

quitProgram(false)

{
    //EDIT MAIN MENU HERE!!!!
    menuTitle = "\n\n                 ISA's ADVENTURES\n"; 
    menuOptions.push_back("1. Start Game"); 
    menuOptions.push_back("2. Credits"); 

    menuOptions.push_back("\n3. Exit"); 
}

/***********************************************************************
 * ** Description: This destructor is empty. 
 * *********************************************************************/
Menu::~Menu()
{
    //empty.
}

/***********************************************************************
 * ** Description: This function are the different menu prompt options. 
 * The prompts can be edited as needed for the program. Add another 
 * MenuOptions enum in the header file and add another option to the 
 * list below to use.
 *
 * Parameter: A MenuOptions enum that represents the menu choices.
 *
 * Return: void.
 * *********************************************************************/
void Menu::printMenuOptions(MenuOptions choiceIn)
{
    switch(choiceIn)
    {
        case MAIN_MENU:
            getTitleGraphics("title.txt");
            printMenu(menuTitle, menuOptions);
            break;

        case MERCY:
            cout << "\nDo you want to spare Billy the Bandit?" << endl;
            break;

        case QUIT:
            cout << "\nAre you sure you want to quit game?";
            cout << "\nGame progress will not be saved.";
            cout << "\nChoice (Y/N):";
            break;
    }
}

/***********************************************************************
 * ** Description: This function displays the main menu prompt as edited  
 * in the constructor.
 *
 * Parameter: None.
 *
 * Return: Void.
 * *********************************************************************/
void Menu::initiateMenu() 
{
    int userChoiceAsNumber = -1;

    //Validates choices as integers.
    userChoiceAsNumber = userInputInteger(1, menuOptions.size(), MAIN_MENU); 

    //Converts the user choice from integer to the enumerated data type.
    userChoice = static_cast<Choices>(userChoiceAsNumber);

    if(userChoice == EXIT)
    {
        quitProgram = true;
    }

}


/***********************************************************************
 * ** Description: This function prints out the main program menu. 
 * 
 * Parameter: 
 * 1. string - The title of the program.
 * 2. vector<string> - the menu options. 
 *
 * Return: Void.
 * *********************************************************************/
void Menu::printMenu(const string &title, const vector<string> &menuArray) 
{
    cout << title << endl;

    for(unsigned i = 0; i < menuArray.size(); i++) 
    {
        cout << menuArray.at(i) << endl;
    }

    cout << "\nPlease choose from the available options: ";
}

/***********************************************************************
 * ** Description: This function receives the input from the user for
 * yes or no questions, verifies the answer, and returns the verified
 * answer in the form of a char 'y' or 'n'.
 *
 * Parameter: An enumerated data type that represents the menu prompt. 
 *
 * Return: char - This char is the verified user entered yes or no answer.
 * The function will return either a 'y' or 'n' based on the correct
 * input the user has entered.
 * *********************************************************************/
char Menu::userInputYN(MenuOptions menu)
{
    string  testInput;
    char yesNo;
    bool inputVerified = false;

    while(!inputVerified)
    {
        //Clear screen and move cursor.
        cout << "\033[2J\033[1;1H";

        printMenuOptions(menu); 

        getline(cin, testInput);

        inputVerified = validInput.validateAlpha(testInput);

        if(inputVerified)
        {
            yesNo = testInput[0];

            if(yesNo == 'Y' || yesNo == 'y')
            {
                inputVerified = true;
                yesNo = 'y';
            }
            
            else if (yesNo == 'N' || yesNo == 'n')
            {
                inputVerified = true;
                yesNo = 'n';
            }

            else
            {
                cout    << "\nPlease answer 'y' or 'n'\n"
                        << "Press <enter> to try again" << endl;

                cin.clear();
                cin.ignore(INT_MAX, '\n');

                inputVerified = false;
            }
        }
    }

    return yesNo;
}

/***********************************************************************
 * ** Description: This function receives the input from the user for
 * menu choices, verifies the choice is an integer, then returns that
 * choice as an int.
 *
 * Parameter: 
 * 1. int - represents the minimum value that the user can enter.
 * 2. int - represents the maximum value that the user can enter.
 * 3. An enuermated data type that represents the menu prompt.
 *
 * Return: int - This integer is the verified user input that is within
 * the minimum and maximum specifications of the menu choices.
 * *********************************************************************/
int Menu::userInputInteger(int min, int max, MenuOptions menu)
{
    string  testInput;
    int     inputReturn;
    bool    inputVerified = false;
    
    while(!inputVerified)
    {
        //Clear screen and move cursor.
        cout << "\033[2J\033[1;1H";

        printMenuOptions(menu); 

        getline(cin, testInput);
        
        inputVerified = validInput.validateInteger(testInput);

        if (inputVerified)
        {
            inputReturn = stoi(testInput); 
        
            //Keep looping if the input is out of range.
            if (inputReturn < min || inputReturn > max)
            {
                cout    << "\nThat is not a valid option.\n"
                        << "Press <enter> to try again." << endl;

                cin.clear();
                cin.ignore(INT_MAX, '\n');

                inputVerified = false;
            }
        }
    }

    return inputReturn;
}

/***********************************************************************
 * ** Description: This function receives the input from the user, 
 * verifies the choice is a double, then returns that choice as a double.
 *
 * Parameter: A constant reference which represents which menu to display.
 *
 * Return: The double number that was verified.
 * *********************************************************************/
/*double Menu::userInputDouble(MenuOptions menu)
{
    string  testInput;
    double inputReturn;
    bool    inputVerified = false;
    
    while(!inputVerified)
    {
        //Clear screen and move cursor.
        cout << "\033[2J\033[1;1H";

        printMenuOptions(menu); 

        getline(cin, testInput);
        
        inputVerified = validInput.validateDouble(testInput);

        if (inputVerified)
        {
            inputReturn = stod(testInput); 
            
            //Keep looping if the input is out of range.
            if (inputReturn < DBL_MIN || inputReturn > DBL_MAX)
            {
                cout    << "\n\nThat is not a valid option.\n"
                        << "Press <enter> to try again." << endl;

                cin.clear();
                cin.ignore(INT_MAX, '\n');

                inputVerified = false;
            }
        }
    }

    return inputReturn;
}*/

/***********************************************************************
 * ** Description: This function receives the input from the user, 
 * removes the front and back spaces, then returns that string.
 *
 * Parameter: None. 
 *
 * Return: A string with front and back spaces removed, if any.
 * *********************************************************************/
string Menu::userInputString()
{
    string testInput;
    bool inputVerified = true;
    int allSpaces = true;

    getline(cin, testInput);
   
    //Limit the string to 50 characters.
    if( testInput.length() > 50 )
    {
        cout << "\nThat input is too large. \nPress <enter> to try again." << endl; 
        inputVerified = false;

        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }       

    else if( testInput.length() == 0 ) 
    {
        cout << "\nYou did not enter anything. \nPress <enter> to try again." << endl; 
        inputVerified = false;

        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    //Display an error if the user did not enter anything.
    else if( testInput[0] == ' ' )
    {
        for(unsigned int i = 0; i < testInput.length(); i++)
        {
            if(testInput[i] != ' ')
            {
                allSpaces = false;
            }
        }

        if(allSpaces)
        {
            cout << "\nYou did not enter anything. \nPress <enter> to try again." << endl; 
            inputVerified = false;

            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }

    }   

    if(inputVerified)
    {
        removeSpaces(testInput);

    }

    return testInput;
}

/***********************************************************************
 * ** Description: This function receives the input from the user, 
 * removes the front and back spaces, then returns that string.
 *
 * Parameter: An enumerated data type which represents which menu to 
 * display.
 *
 * Return: The string with front and back spaces removed, if any.
 * *********************************************************************/
string Menu::userInputString(MenuOptions menu)
{
    string testInput;
    bool inputVerified = false;

    while(!inputVerified)
    {
        //Clear screen and move cursor.
        cout << "\033[2J\033[1;1H";

        printMenuOptions(menu); 

        getline(cin, testInput);
       
        //Limit the string to 50 characters.
        if( testInput.length() > 50 )
        {
            cout << "\nThat input is too large. \nPress <enter> to try again." << endl; 

            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }       

        else if( testInput.length() == 0 ) 
        {
            cout << "\nYou did not enter anything. \nPress <enter> to try again." << endl; 

            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }

        //Display an error if the user did not enter anything.
        else if( testInput[0] == ' ' )
        {
            int allSpaces = true;

            for(unsigned int i = 0; i < testInput.length(); i++)
            {
                if(testInput[i] != ' ')
                {
                    allSpaces = false;
                }
            }

            if(allSpaces)
            {
                cout << "\nYou did not enter anything. \nPress <enter> to try again." << endl; 

                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }

            else
            {
                inputVerified = true;
            }
        }   

        else
        {
            inputVerified = true;
        }

        if(inputVerified) 
        {
            removeSpaces(testInput);

            if(validInput.validateAlpha(testInput) == false) 
            {
                inputVerified = false;
            }
        }
    }

    return testInput;
}
    
/***********************************************************************
 * ** Description: This function removes the front and back spaces of
 * a string.
 *
 * Parameter: A reference to a string that will have the front and back
 * spaces removed.
 *
 * Return: Void. 
 * *********************************************************************/
void Menu::removeSpaces(string &tempString)
{
    int frontOfString = 0;
    int counter = 0;

    //Remove spaces in front.
    while(tempString[frontOfString] == ' ')
    {
            tempString.erase(0, 1);
    }
    
    int backOfString = tempString.length() - 1;
    
    //Remove spaces in back.
    while(tempString[backOfString-counter++] == ' ')
    {
            tempString.pop_back();
    }
}

bool Menu::getQuitProgram() const
{
    return quitProgram;
}

Choices Menu::getUserChoice() const
{
    return userChoice;
}

/***********************************************************************
 * ** Description: This function reads text from a file and prints it
 * out.
 *
 * Parameter: A reference to a string that is the file name. 
 *
 * Return: Void. 
 * *********************************************************************/
void Menu::getTitleGraphics(const string &fileName) 
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
            print += temp;
        }

        cout << print;
    }

    inputFile.close();
}
