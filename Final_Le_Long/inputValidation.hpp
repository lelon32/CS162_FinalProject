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
#ifndef INPUT_VALIDATION_HPP
#define INPUT_VALIDATION_HPP

#include <cctype>
#include <climits>

#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<string>
using std::string;
using std::stoi;
using std::stod;
using std::to_string;

class InputValidation 
{
    public:
    bool validateInteger(const string &);
    bool validateDouble(const string &);
    bool validateAlpha(const string &);
};

#endif
