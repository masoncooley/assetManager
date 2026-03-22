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
         << "6 | Filter assets by specific criteria\n"
         << "7 | Exit program\n"
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
        
        // get menu choice
        cout << "\nEnter menu choice: ";
        cin >> menuChoice;

        // checks if input fails and informs user
        while (true)
        {
            if (cin.fail())
            {
                cin.clear();    // clears error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');    // Discard invalid input

                cout << "\nInvalid input was entered. Please enter a positive number from 1 to 7.\n";
            }
            else
                break;
        }


        // validate menu choice and allow user to re-enter choice
        while (menuChoice < 1 || menuChoice > 7)
        {
            cout << "\nInvalid menu choice. Please enter a single number between 1 and 7: ";
            cin >> menuChoice;
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
            manager.filterAsset();
            break;
        default:
            break;
        }
    } while (menuChoice != 7);  // will loop until exit code (7) is entered for menu choice
    
    return;
}

int main()
{
    getMenuChoice();

    system("clear");    // clear screen on Linux
    system("cls");      // clear screen on Windows
    cout << "Exiting now...";

    return 0;
}
