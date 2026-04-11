// Client-facing Program

#include "InventoryManager.h"

#include <iostream>
#include <limits>   // for the numeric_limits on cin.ignore
using namespace std;

// clears screen and displays menu of options
void displayMenu()
{
    system("cls");      // clear screen on windows
    system("clear");    // clear screen on Linux
    
    cout << "Mason's IT Asset Management System\n"
        << "_____________________________________\n\n";
        
    cout << "1 | View a current list of assets\n"
         << "2 | Create a new asset\n"
         << "3 | Modify an existing asset\n"
         << "4 | Delete an existing asset\n"
         << "5 | Search for a single asset\n"
         << "6 | Save assets to a file\n"
         << "7 | Read assets from a file\n"
         << "8 | Exit program\n"
         << "-------------------------------------------\n";
};

// gets user menu choice and calls corresponding function
void getMenuChoice()
{
    InventoryManager manager;

    int menuChoice;
    
    do
    {  
        displayMenu();
        
        // get menu choice and validate until input is valid 
        while (true)
        {
            // get menu choice
            cout << "\nEnter menu choice: ";
            cin >> menuChoice;

            // catches non-numeric input
            if (cin.fail())
            {
                cin.clear();    // clears error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');    // Discard invalid input

                cout << "\nNon-numerical input was entered.\n";
            }
            // catches input not in range of menu choices
            else if (menuChoice < 1 || menuChoice > 8)
                cout << "\nInvalid menu choice. Input must be between 1 and 8! ";
            else
                break;
        }

        // calls appropriate function based on user menu choice
        switch (menuChoice)
        {
        case 1:
            manager.getFullAssetList();
            break;
        case 2:
            manager.addAsset();
            break;
        case 3:
            manager.modifyAsset();
            break;
        case 4:
            manager.removeAsset();
            break;
        case 5:
            manager.searchAsset();
            break;
        case 6:
            manager.saveToFile();
            break;
        case 7:
            manager.readFromFile();
            break;
        default:
            break;
        }
    } while (menuChoice != 8);  // will loop until exit code (7) is entered for menu choice
    
    return;
}

int main()
{
    srand(time(0));     // sets seed value for rand() function used in Asset.cpp 
                        // otherwise the seed would change with each function call, possibly leading to duplicate IDs 

    getMenuChoice();

    system("clear");    // clear screen on Linux
    system("cls");      // clear screen on Windows
    cout << "Exiting now...";

    return 0;
}
