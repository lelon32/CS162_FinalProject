/***********************************************************************
 * ** Program name: Isa's Adventures
 * ** Author: Long Le
 * ** Date: 6/12/2017
 * ** Description: The InputValidation class is a work in progress and 
 * aims to validate user inputs of different types. Currently, it has 
 * member functions to validate user entered integers, decimal numbers, 
 * or alphabetic letters. Member functions that are called to validate 
 * input will return false if the user entered input fails validation.
 * *********************************************************************/
#include "inputValidation.hpp"

/***********************************************************************
 * ** Description: This function validates inputs as integers. The
 * function will reject any input that is not an integer and return
 * false. 
 *
 * Parameters: A constant reference to a string that needs to be verified
 * as an integer.
 *
 * Return: Bool. The function will return true if the user input is an
 * integer and will return false if it is not.
 * *********************************************************************/
bool InputValidation::validateInteger( const string &userInput )
{
    bool validInteger = false;
    
    string tempString = userInput;
            
    //Remove a negative sign from the string if it exists.
    if( tempString[0] == '-')
    {
        tempString.erase( tempString.begin() );
    }

    if( tempString.length() > 6 )
    {
        cout << "\nThat input is too large. \nPress <enter> to try again." << endl;       

        cin.clear();
        cin.ignore( INT_MAX, '\n' );
    }   

    //Display an error if the user did not enter anything.
    else if( tempString.length() == 0 )
    {
        cout << "\nYou did not enter anything. \nPress <enter> to try again." << endl; 

        cin.clear();
        cin.ignore( INT_MAX, '\n' );
    }   

    else 
    {
        validInteger = true; 

        //Check every character to make sure it is a digit.
        for( unsigned int i = 0; i < tempString.length() && validInteger; i++)
        {
            if( !isdigit( tempString[i] ) )
            {
                validInteger = false;
            }   
        }  
        
        if( !validInteger )
        {
            cout    << "\nThat is not a valid integer." 
                    << "\nPress <enter> to try again." << endl;

            cin.clear();
            cin.ignore( INT_MAX, '\n' );
        }
    }

    return validInteger;
}

/***********************************************************************
 * ** Description: This function validates inputs as a double. The
 * function will reject any input that is not an integer and return
 * false. 
 *
 * Parameters: A constant reference to a string that needs to be verified
 * as an integer.
 *
 * Return: Bool. The function will return true if the user input is a
 * double and will return false if it is not.
 * *********************************************************************/
bool InputValidation::validateDouble( const string &userInput )
{
    bool validDouble = false;
    int countDecimal = 0;
    
    string tempString = userInput;
            
    //Remove a negative sign from the string if it exists.
    if( tempString[0] == '-')
    {
        tempString.erase( tempString.begin() );
    }

    if( tempString.length() > 20 )
    {
        cout << "\nThat input is too large. \nPress <enter> to try again." << endl;       

        cin.clear();
        cin.ignore( INT_MAX, '\n' );
    }   

    //Display an error if the user did not enter anything.
    else if( tempString.length() == 0 )
    {
        cout << "\nYou did not enter anything. \nPress <enter> to try again." << endl; 

        cin.clear();
        cin.ignore( INT_MAX, '\n' );
    }   

    else 
    {
        validDouble = true; 

        //Check every character to make sure it is a digit. The '.' cannot be
        //found more than once or the number is not a decimal number.
        for( unsigned int i = 0; i < tempString.length() && validDouble; i++)
        {

            if(tempString[tempString.length() - 1] == '.' || countDecimal > 1)
            {
                validDouble = false;
            }

            else if(tempString[i] == '.')
            {
                ++countDecimal;

            }

            else if( !isdigit( tempString[i] ) )
            {
                validDouble = false;
            }   

        }  

        if( !validDouble )
        {
            cout    << "\nThat is not a valid decimal number." 
                    << "\nPress <enter> to try again." << endl;

            cin.clear();
            cin.ignore( INT_MAX, '\n' );
        }
    }

    return validDouble;
}

/***********************************************************************
 * ** Description: This function validates inputs as alphabetical letters.
 * The function will reject any input that is not a letter or letters of 
 * the alphabet and will return false. 
 *
 * Parameters: A constant reference to a string that needs to be verified
 * as an alphabetical letters.
 *
 * Return: Bool. The function will return true if the user input are 
 * alphabetical letters and will return false if it is not.
 * *********************************************************************/
bool InputValidation::validateAlpha(const string &userInput)
{
    bool validAlpha = false;
    string enter;
    
    string tempString = userInput;
            
    if( tempString.length() > 50 )
    {
        cout << "\nThat input is too large. \nPress <enter> to try again." << endl;       

        cin.clear();
        cin.ignore( INT_MAX, '\n' );
    }   

    //Display an error if the user did not enter anything.
    else if( tempString.length() == 0 )
    {
        cout << "\nYou did not enter anything. \nPress <enter> to try again." << endl; 

        cin.clear();
        cin.ignore( INT_MAX, '\n' );
    }   

    else 
    {
        validAlpha = true; 

        //Check every character to make sure it is a letter of the alphabet.
        for( unsigned int i = 0; i < tempString.length() && validAlpha; i++)
        {
            if( !isalpha ( tempString[i] ) )
            {
                validAlpha = false;
            }   
        }  
        
        if( !validAlpha )
        {
            cout    << "\nUser entry are not valid letters." 
                    << "\nPress <enter> to try again." << endl;

            cin.clear();
            cin.ignore( INT_MAX, '\n' );
        }

    }

    return validAlpha;
}
