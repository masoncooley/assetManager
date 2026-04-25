// InputValidation.cpp
//
// File to define reusable functions for input validation

#include "InputValidation.h"
#include <iostream>
#include <limits>

using namespace std;

// gets integer input and validates it in a loop until valid input is given
//
// promptString is just the statement to display to the user before taking input 
// ex: "Enter the number of CPU cores: "
//
// min and max define the lowest and highest values allowed for input (ex: number between 1 and 10) 
int validateInteger(const string &promptString, const int min, const int max)
{
    int input;

    while (true)
    {
        cout << promptString;
        cin >> input;

        // checks for input not of the correct data type
        if (cin.fail())
        {
            cin.clear();    // clears error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    // Discard invalid input

            cout << "\nNon-numeric input was entered. \n";
        }
        // checks that input is in valid range 
        else if (input < min || input > max)
            cout << "\nInput must be between " << min << " and " << max << "! \n"; 
        else
         break;
    }

    return input;
}
