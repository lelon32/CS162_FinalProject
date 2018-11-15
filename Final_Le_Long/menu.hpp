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
#ifndef MENU_HPP
#define MENU_HPP

/**********************************************************************
    //PROGRAM SPECIFIC HEADER FILES. EDIT/ADD HERE!!!!!
 **********************************************************************/

#include "inputValidation.hpp"

#include <cfloat>

#include <vector>
using std::vector;

#include <iomanip>
using std::showpoint;
using std::setprecision;
using std::fixed;

#include <fstream>
using std::ifstream;

//Enumerated data type for user choices. 
enum Choices {START_GAME = 1, CREDITS, EXIT};

//Enumerated data type for menu prompts.
enum MenuOptions {MAIN_MENU, MERCY, QUIT};

class Menu
{
    private:
    string          menuTitle;
    vector<string>  menuOptions;
    Choices userChoice;

    string          subMenuTitle;
    vector<string>  subMenuOptions;

/**********************************************************************
    //PROGRAM SPECIFIC PRIVATE SPECIFICATIONS. EDIT/ADD HERE!!!!!
 **********************************************************************/
    InputValidation validInput; 

    bool quitProgram;

    void printMenu(const string &, const vector<string> &); 
    void printMenuOptions(MenuOptions);

    void removeSpaces(string &);

    void getTitleGraphics(const string &);


    public:
    Menu();
    ~Menu();

    char userInputYN(MenuOptions); 

    string userInputString();
    string userInputString(MenuOptions);

    int userInputInteger(int, int, MenuOptions); 
    //double Menu::userInputDouble(MenuOptions menu)

    bool getQuitProgram() const;
    Choices getUserChoice() const;

    void initiateMenu(); 

/**********************************************************************
    //PROGRAM SPECIFIC PUBLIC MEMBER FUNCTIONS. EDIT/ADD HERE!!!!!
 **********************************************************************/
}; 

#endif
