// Client-facing Program

#include "InventoryManager.h"
#include "InputValidation.h"

#include <iostream>
using namespace std;

// clears screen and displays menu of options
void displayMenu()
{
    cout << "\033[2J\033[H";     // ANSI escape code to clear screen (can be used w/ any OS)

    cout << "Mason's IT Asset Management System\n"
        << "_____________________________________\n\n";
        
    cout << " 1 | View a current list of assets\n"
         << " 2 | Create a new asset\n"
         << " 3 | Modify an existing asset\n"
         << " 4 | Delete an existing asset\n"
         << " 5 | Search for a single asset\n"
         << " 6 | Save assets to a file\n"
         << " 7 | Read assets from a file\n"
         << " 8 | Exit program\n"
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
            menuChoice = validateInteger("\nEnter menu choice: ", 1, 8);

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

    cout << "\033[2J\033[H";     // ANSI escape code to clear screen (can be used w/ any OS)
    cout << "Exiting now...";

    return 0;
}
