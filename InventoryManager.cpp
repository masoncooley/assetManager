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


void InventoryManager::getAssetTypes()
{
    cout << "The 3 asset types are: Desktop, Server, and Mobile Device";
}

void InventoryManager::getFullAssetList()
{
    // checks if any assets are stored in the map
    if (assetMap.empty())
        cout << "There are no assets stored!";
    else
        // makes pair data type named pair to represent 1 singular key:value pair from unordered_map assetMap
        for (pair< const int, unique_ptr<Asset>>& pair : assetMap)
        {
            unique_ptr<Asset>& asset = pair.second; // makes object called asset of Asset class and initializes it to the second value of the pair
            
            cout << "ID: " << asset->getID() << endl;   // print ID by calling getID function from asset object
            cout << "Name: " << asset->getName();   // print name by calling getName function from asset object
        }
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

    // creates the relevant unique_ptr object based on user choice of asset type.
    // Each "newAsset = ..." creates an object of that class (ex. Desktop) on the heap but each of them 
    // are actually stored as a unique_ptr<Asset>
    switch (assetTypeChoice)
    {
        case 1:
            newAsset = make_unique<Desktop>();  // creates a new Desktop object and wraps it in a unique ptr called newAsset
            assetMap.emplace(newAsset->getID(), move(newAsset));  // adds entry to assetMap with asset ID as key and newAsset object as value
                                                                  // -> lets me access the the getID member function of the newAsset object thru the pointer
                                                                  // move() transfers ownership of the object from newAsset to assetMap 
            break;
        case 2: 
            newAsset = make_unique<Server>();  // creates a new Server object and wraps it in a unique ptr called newAsset
            assetMap.emplace(newAsset->getID(), move(newAsset));  // adds entry to assetMap with asset ID as key and newAsset object as value
                                                                  // -> lets me access the the getID member function of the newAsset object thru the pointer
                                                                  // move() transfers ownership of the object from newAsset to assetMap 
            break;
        case 3: 
            newAsset = make_unique<Mobile>();  // creates a new Server object and wraps it in a unique ptr called newAsset
            assetMap.emplace(newAsset->getID(), move(newAsset));  // adds entry to assetMap with asset ID as key and newAsset object as value
                                                                  // -> lets me access the the getID member function of the newAsset object thru the pointer
                                                                  // move() transfers ownership of the object from newAsset to assetMap 

            break;
        default:
            cout << "Invalid choice!";
            break;
    }


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