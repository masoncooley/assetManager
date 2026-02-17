// Client-facing Program

#include <iostream>
#include "Asset.h"     // header file for Asset class

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
    int menuChoice;
    
    do
    {
        // get menu choice
        cout << "\nEnter menu choice: ";
        cin >> menuChoice;

        // validate menu choice and allow user to re-enter choice
        while (menuChoice < 1 || menuChoice > 7)
        {
            cout << "\nInvalid menu choice. Please enter a single number between 1 and 7: ";
            cin >> menuChoice;
        }

        // calls appropriate function based on user menu choice
        // 
        // ** NOTE: cout statements & comments for each switch case are just to confirm program is working correctly;
        // these will be removed later when I include actual function calls **
        switch (menuChoice)
        {
        case 1:
            cout << "You pressed 1";
            /* call function to list assets */
            break;
        case 2:
            cout << "You pressed 2";
            /* call function to create asset */ 
            break;
        case 3:
            cout << "You pressed 3";
            /* call function to modify asset */
            break;
        case 4:
            cout << "You pressed 4";
            /* call function to delete asset */
            break;
        case 5:
            cout << "You pressed 5";
            /* call function to search assets */
            break;
        case 6:
            cout << "You pressed 6";
            /* call function to filter assets */
            break;
        default:
            break;
        }
    } while (menuChoice != 7);  // will loop until exit code (7) is entered for menu choice
    
    return;
}

int main()
{
    displayMenu();
    getMenuChoice();

    system("clear");    // clear screen on Linux
    system("cls");      // clear screen on Windows
    cout << "Exiting now...";
}