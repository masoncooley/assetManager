// Implementation file for class InventoryManager


#include "InventoryManager.h"
#include "Asset.h"
#include "Server.h"
#include "Desktop.h"
#include "Mobile.h"

#include <iostream>
#include <unordered_map>    // needed for unordered_map
#include <memory>    // needed for smart pointers (unique_ptr)
#include <limits>    // for the numeric_limits on cin.ignore

using namespace std;

// currently unused in program
void InventoryManager::getAssetTypes()
{
    cout << "The 3 asset types are: Desktop, Server, and Mobile Device";
}

// prints out each asset and all of its attributes 
void InventoryManager::getFullAssetList()
{
    system("clear");    // Linux clear screen 
    system("cls");      // Windows clear screen

    cout << "Getting all assets...\n\n";

    // checks if any assets are stored in the map
    if (assetMap.empty())
          cout << "There are no assets stored!";
    else
        // makes pair data type named pair to represent 1 singular key:value pair from unordered_map assetMap
        // this pair represents one id:object element in the unordered_map
        for (pair< const int, unique_ptr<Asset>>& pair : assetMap)
        {
            unique_ptr<Asset>& asset = pair.second; // makes object called asset of Asset class and initializes it to the second value of the pair
            
            asset->displayAttributes(); // calls asset-specific function to print attributes
                                        // ex: if Desktop object, it will call the Desktop version, 
                                        // which will call the Computer version, which will call the Asset version
        }

    // stops program from immediately reprinting the main menu by waiting for user input
    cout << "\n\nEnter any key to continue...";
    cin.ignore();   // ignores the \n left in the buffer
    cin.get();
}

/*
All functions in InventoryManager need to work for all three asset types, so I define the unique_ptr as type Asset.
Asset is the base class, so it applies for all child classes (Desktop, Server, Mobile). 
*/
void InventoryManager::addAsset()
{
    // creates a brand new object of the Asset class named newAsset and allocates a portion of memory for it with a unique pointer
    unique_ptr<Asset> newAsset;

    // print menu
    system("clear");
    system("cls");
    cout << "Asset Types: \n"
         << "_____________\n";
    cout << "1 - Desktop\n" << "2 - Server\n" << "3 - Mobile Device\n\n";

    // get user choice for asset type
    int assetTypeChoice;
    cout << "Enter the number for the type of asset to be created: ";
    cin >> assetTypeChoice;

    // checks if input fails and informs user
    while (true)
    {
        if (cin.fail())
        {
            cin.clear();    // clears error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    // Discard invalid input

            cout << "\nInvalid input was entered. Please enter a positive number from 1 to 3.\n";
        }
        else
            break;
    }


    string assetName;   // temp holder for name of newAsset
    int assetID;    // temp holder for ID of newAsset 

    // creates the relevant unique_ptr object based on user choice of asset type.
    // Each "newAsset = ..." creates an object of that class (ex. Desktop) on the heap but each of them 
    // are actually stored as a unique_ptr<Asset>
    switch (assetTypeChoice)
    {
        case 1:
            newAsset = make_unique<Desktop>();  // creates a new Desktop object and wraps it in a unique ptr called newAsset 

            // prompt user for name of Desktop
            cout << "\nWhat would you like to name the Desktop? ";
            cin.ignore();
            getline(cin, assetName);

            newAsset->setName(assetName);   // calls Asset function setName() from newAsset pointer (which points to a Desktop object)

            newAsset->setAttributes();      // calls function to set all Desktop attributes (will also call Computer::setAttributes() )

            assetID = newAsset->getID();    // sets assetID for use in the cout statement later 

            // adds entry to assetMap with asset ID as key and newAsset object as value
            // -> lets me access the the getID member function of the Desktop object thru the newAsset pointer
            // move() transfers ownership of the object from newAsset to assetMap 
            assetMap.emplace(newAsset->getID(), move(newAsset));

            // later i should put a check to make sure object was actually created before printing the below line 
            cout << "Created new Desktop \"" << assetName << "\" with ID " << assetID << endl;

            break;
        case 2: 
            newAsset = make_unique<Server>();  // creates a new Server object and wraps it in a unique ptr called newAsset

            // prompt user for name of Server
            cout << "\nWhat would you like to name the Server? ";
            cin.ignore();
            getline(cin, assetName);

            newAsset->setName(assetName);   // calls Asset function setName() from newAsset pointer (which points to a Server object)
            
            newAsset->setAttributes();  // calls function to set all Server attributes (will also call Computer::setAttributes() )

            assetID = newAsset->getID();    // sets assetID for use in the cout statement later

            // adds entry to assetMap with asset ID as key and newAsset object as value
            // -> lets me access the the getID member function of the newAsset object thru the pointer
            // move() transfers ownership of the object from newAsset to assetMap 
            assetMap.emplace(newAsset->getID(), move(newAsset));

            // later i should put a check to make sure object was actually created before printing the below line 
            cout << "Created new Server \"" << assetName << "\" with ID " << assetID << endl;

            break;
        case 3: 
            newAsset = make_unique<Mobile>();  // creates a new Mobile object and wraps it in a unique ptr called newAsset
           
            // prompt user for name of Mobile device
            cout << "\nWhat would you like to name the Mobile device? ";
            cin.ignore();
            getline(cin, assetName);

            newAsset->setName(assetName);   // calls Asset function setName() from newAsset pointer (which points to a Mobile object)

            newAsset->setAttributes();  // calls function to set all Mobile attributes (will also call Computer::setAttributes() )

            assetID = newAsset->getID();    // sets assetID for use in the cout statement later

            // adds entry to assetMap with asset ID as key and newAsset object as value
            // -> lets me access the the getID member function of the newAsset object thru the pointer
            // move() transfers ownership of the object from newAsset to assetMap 
            assetMap.emplace(newAsset->getID(), move(newAsset));
           
            // later i should put a check to make sure object was actually created before printing the below line 
            cout << "Created new Mobile device \"" << assetName << "\" with ID " << assetID << endl;

            break;
        default:
            cout << "Invalid choice!";
            break;
    }

    // waits for user input before continuing
    cout << "\n\nEnter any key to continue...";
    cin.get();

}
void InventoryManager::modifyAsset()
{
    
}
void InventoryManager::removeAsset()
{

}
void InventoryManager::searchAsset()
{

}
void InventoryManager::filterAsset()
{

}
void InventoryManager::saveToFile()
{

}
void InventoryManager::readFromFile()
{

}


