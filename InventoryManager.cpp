// Implementation file for class InventoryManager


#include "InventoryManager.h"
#include "Asset.h"
#include "Server.h"
#include "Desktop.h"
#include "Mobile.h"

#include <cctype>   // needed for toupper()
#include <cstdlib>  // needed for system()
#include <iostream> // needed for cin,cout
#include <unordered_map>    // needed for unordered_map
#include <memory>    // needed for smart pointers (unique_ptr)
#include <limits>    // for the numeric_limits on cin.ignore
#include <fstream>      // needed for file operations (ifstream, ofstream)

using namespace std;

// checks if ID exists in assetMap and returns true/false
bool InventoryManager::isIDAvailable(int targetID) 
{
    auto idResult = assetMap.find(targetID);    // .find() returns an iterator

    return (idResult == assetMap.end());    // returns true/false
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
            
            asset->writeAttributesToStream(cout); // calls asset-specific function to print attributes
                                                  // ex: if Desktop object, it will call the Desktop version
                                                  // cout stream type is passed as arg so that it will print to console
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
   
    // gets input and validates it in a loop until valid input is given
    while (true)
    {
        cout << "Enter the number for the type of asset to be created: ";
        cin >> assetTypeChoice;

        // checks for input not of the correct data type
        if (cin.fail())
        {
            cin.clear();    // clears error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    // Discard invalid input

            cout << "\nNon-numeric input was entered. \n";
        }

        // validates that input is within menu option bounds
        else if (!(assetTypeChoice >= 1 && assetTypeChoice <= 3))
            cout << "\nInvalid choice (input was not 1, 2 or 3).\n";
        else
            break;
    }

    string assetName;   // temp holder for name of newAsset
    int assetID;    // temp holder for ID of newAsset 

    // creates the relevant unique_ptr object based on user choice of asset type.
    // Each "newAsset = ..." creates an object of that class (ex. Desktop) on the heap but each of them are actually stored as a unique_ptr<Asset>
    switch (assetTypeChoice)
    {
        case 1:
            newAsset = make_unique<Desktop>();  // creates a new Desktop object and wraps it in a unique ptr called newAsset 

            // checks that auto-generated ID does not already exist
            // if true, it will regenerate a new ID
            while (!isIDAvailable(newAsset->getID()))
                newAsset->regenerateID();

            // prompt user for name of Desktop
            cout << "\nWhat would you like to name the Desktop? ";
            cin.ignore();
            getline(cin, assetName);

            newAsset->setName(assetName);   // calls Asset function setName() from newAsset pointer (which points to a Desktop object)

            newAsset->setAttributes();      // calls function to set all Desktop attributes (will also call Computer::setAttributes() )

            assetID = newAsset->getID();    // sets assetID for use in .emplace and cout statement 

            // adds entry to assetMap with asset ID as key and newAsset object as value
            // move() transfers ownership of the object from newAsset to assetMap 
            assetMap.emplace(assetID, std::move(newAsset)); // without the "std::" I get an "unqualified call to std::move" warning

            // later i should put a check to make sure object was actually created before printing the below line 
            cout << "\nCreated new Desktop \"" << assetName << "\" with ID " << assetID << endl;

            break;
        case 2: 
            newAsset = make_unique<Server>();  // creates a new Server object and wraps it in a unique ptr called newAsset

            // checks that auto-generated ID does not already exist
            // if true, it will regenerate a new ID
            while (!isIDAvailable(newAsset->getID()))
                newAsset->regenerateID();

            // prompt user for name of Server
            cout << "\nWhat would you like to name the Server? ";
            cin.ignore();
            getline(cin, assetName);

            newAsset->setName(assetName);   // calls Asset function setName() from newAsset pointer (which points to a Server object)
            
            newAsset->setAttributes();  // calls function to set all Server attributes (will also call Computer::setAttributes() )

            assetID = newAsset->getID();    // sets assetID for use in .emplace and cout statement
                                            
            // adds entry to assetMap with asset ID as key and newAsset object as value
            // move() transfers ownership of the object from newAsset to assetMap 
            assetMap.emplace(assetID, std::move(newAsset)); // without the "std::" I get an "unqualified call to std::move" warning

            // later i should put a check to make sure object was actually created before printing the below line 
            cout << "\nCreated new Server \"" << assetName << "\" with ID " << assetID << endl;

            cin.ignore();   // needed so that cin.get() outside switch statement doesn't accept newline character

            break;
        case 3: 
            newAsset = make_unique<Mobile>();  // creates a new Mobile object and wraps it in a unique ptr called newAsset

            // checks that auto-generated ID does not already exist
            // if true, it will regenerate a new ID
            while (!isIDAvailable(newAsset->getID()))
                newAsset->regenerateID();

            // prompt user for name of Mobile device
            cout << "\nWhat would you like to name the Mobile device? ";
            cin.ignore();
            getline(cin, assetName);

            newAsset->setName(assetName);   // calls Asset function setName() from newAsset pointer (which points to a Mobile object)

            newAsset->setAttributes();  // calls function to set all Mobile attributes (will also call Computer::setAttributes() )

            assetID = newAsset->getID();    // sets assetID for use in .emplace and cout statement
                                            //
            // adds entry to assetMap with asset ID as key and newAsset object as value
            // move() transfers ownership of the object from newAsset to assetMap 
            assetMap.emplace(assetID, std::move(newAsset)); // without the "std::" I get an "unqualified call to std::move" warning
           
            // later i should put a check to make sure object was actually created before printing the below line 
            cout << "\nCreated new Mobile device \"" << assetName << "\" with ID " << assetID << endl;

            cin.ignore();   // needed so that cin.get() outside switch statement doesn't accept newline character

            break;
        default:
            cout << "Invalid choice!";
            break;
    }

    // waits for user input before continuing
    cout << "\n\nEnter any key to continue...";
    cin.get();

}

// allows user to modify any attribute (except ID) of an existing asset
// uses searchAsset() to let user find the asset they wish to modify and view its attributes before modification
void InventoryManager::modifyAsset()
{
    int searchReturnCode = InventoryManager::searchAsset(); // searchAsset() returns a code depending if the map is empty or not

    // if no assets were found during execution of searchAsset, exit to main menu
    // if there are no assets, there's nothing to modify
    if (searchReturnCode == 1)  // code 1 indicates that assetMap was empty
        return;

    int assetID,
        attributeChoice = 1;  // 1 is arbitrary

    // serves 2 purposes:
    // - gets user confirmation on asset selection 
    // - provides ID to this function for use in modifying assets
    cout << "\nRe-type ID of the asset you want to modify (for confirmation purposes): ";
    cin >> assetID;

    unique_ptr<Asset>& assetToModify = assetMap.at(assetID);    // sets current asset to be modified by function

    do 
    {
        system("clear");

        cout << "\nList of modifiable attributes:\n"
             << "_________________________________\n\n";

        assetToModify->displayModifiableAttributes();    // displays list of attributes that can be modified for specific asset type
        cout << "(0) - Exit modification menu \n";

        // gets attributeChoice and validates input until valid
        while (true)
        {
            cout << "\nEnter integer corresponding with the attribute you would like to modify: ";
            cin >> attributeChoice;

            // catches non-numeric input
            if (cin.fail()) 
            {
                cin.clear();    // clears error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');    // Discard invalid input

                cout << "\nNon-numeric input was entered. \n";
            }

            // catches input out of range of menu options
            if (attributeChoice < 0 || attributeChoice > 9)
                cout << "Input must be between 0 and 9!\n";
            else
                break;
        }

        assetToModify->modifyAttributes(attributeChoice);   // calls modify function specific to asset type

    } while ( attributeChoice != 0); // 0 is exit code  
}

// allows user to remove an individual asset
void InventoryManager::removeAsset()
{
    int searchReturnCode = InventoryManager::searchAsset(); // searchAsset() returns a code depending if the map is empty or not

    // if no assets were found during execution of searchAsset, exit to main menu
    // if there are no assets, there's nothing to delete 
    if (searchReturnCode == 1)  // code 1 indicates that assetMap was empty
        return;

    int targetID;
    string confirmation;

    // gets targetID and validates input until valid input is entered
    while (true)
    {
        cout << "\nEnter the ID for the asset you wish to delete: ";
        cin >> targetID;

        // catches non-numeric input
        if (cin.fail()) 
        {
            cin.clear();    // clears error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    // Discard invalid input
            cout << "\nNon-numeric input was entered. \n";
        }

        // catches input outside of ID range
        if (targetID < 0 || targetID > 10000)
            cout << "Input must be between 0 and 10,000!\n";
        else
            break;
    }

    unique_ptr<Asset>& assetToDelete = assetMap.at(targetID);   // creates new Asset object matching the asset user wants to delete
                                                                // in order to print out asset type, ID, and name

    // makes sure user wants to delete chosen asset
    cout << "Are you sure you want to delete " << assetToDelete->getAssetType() << " asset \"" << assetToDelete->getName() 
         << "\" with ID #" << assetToDelete->getID() << "? ";
    cout << "\nEnter \"CONFIRM\" to confirm deletion: ";
    cin >> confirmation;
   
    // standardizes confirmation string by converting each individual character to uppercase
    for (int i = 0; i < confirmation.length(); i++)
        confirmation[i] = toupper(confirmation[i]);

    // if user is sure, erases 
    if (confirmation == "CONFIRM")
    {
        assetMap.erase(targetID);   // erases asset stored at key targetID in assetMap

        // ensures that chosen asset was deleted by searching for it again
        if (assetMap.find(targetID) == assetMap.end())
        {
            cout << "\n\nAsset successfully deleted! ";

            // wait for user before continuing
            cout << "\nEnter any key to exit to main menu: ";
            cin.ignore();
            cin.get();
        }
    }
    else
        cout << "\n\nConfirmation not received, exiting to main menu...";

}

// searches for a stored asset when given an ID or Name
// return code 0 indicates function executed correctly, code 1 means assetMap was empty (no assets to search for)
int InventoryManager::searchAsset()
{
    system("clear");    // Linux clear screen
    system("cls");      // Windows clear screen

    // if nothing is stored in the asset map, exit the function early to prevent unwanted behavior
    if (assetMap.empty())
    {
        cout << "\nThere are no assets to search for!";
        
        // wair for user input before continuing
        cout << "\nEnter any key to exit to main menu...";
        cin.ignore();
        cin.get();

        return 1;   // code indicates no assets present in map
    }

    int searchChoice = 0;

    // gets searchChoice and validates until valid input is entered
    while (true)
    {
        cout << "Search by ID (enter 1) or Name (enter 2)? ";
        cin >> searchChoice;

        // catches non-numeric input
        if (cin.fail())
        {
            cin.clear();    // clears error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    // Discard invalid input

            cout << "\nNon-numeric input was entered. \n";
        }
        // catches input not in range of choices
        else if (searchChoice != 1 && searchChoice != 2)
            cout << "\nInvalid choice (input was not 1 or 2).\n";
        else
            break;
    }

    // searches by ID or Name based on user choice
    switch (searchChoice) 
    {
        case 1: // search by ID
        {
            int searchID;

            // gets searchID and validates until valid input is entered
            while (true)
            {
                cout << "\n\nEnter the asset ID to search for: ";
                cin >> searchID;

                // catches non-numeric input
                if (cin.fail()) 
                {
                    cin.clear();    // clears error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');    // Discard invalid input

                    cout << "\nNon-numeric input was entered. \n";
                }
                // catches input not in range of valid IDs
                else if (searchID < 0 || searchID > 10000)
                    cout << "Input must be between 0 and 10,000!\n";
                else
                    break;
            }

            auto idResult = assetMap.find(searchID);    // .find() returns an iterator

            // ensure chosen asset exists
            // idResult will = end of map if no key matching the input was found
            if (idResult == assetMap.end())
                cout << "\nAn asset with that ID does not exist. Please try again.";
            else
            {
                unique_ptr<Asset>& assetResult = assetMap.at(searchID); // creates new Asset object and sets address to 
                                                                        // value associated with key searchID in the map
               
                system("clear");
                system("cls");

                // prints all attributes for resulting asset object
                cout << "Search results for ID #" << searchID << ": \n\n";
                assetResult->writeAttributesToStream(cout);     // cout is given as arg so that output will be displayed on console
            }
        }
        break;

        case 2: // search by Name
        {
            string targetName;

            bool found = false;    // flag variable to allow for exiting the switch statement when targetName is found in the map 

            // get name to search for
            cout << "\n\nEnter the name to search for: ";
            cin.ignore();
            getline(cin, targetName);

            system("clear");    // Linux clear screen
            system("cls");      // Windows clear screen

            cout << "Search results for \"" << targetName << "\":\n\n";

            // prints all instances of targetName found in assetMap
            // makes pair data type named pair to represent 1 singular key:value pair from unordered_map assetMap
            // this pair represents one id:object element in the unordered_map
            for (pair< const int, unique_ptr<Asset>>& pair : assetMap)
            {
                unique_ptr<Asset>& asset = pair.second; // makes object called asset of Asset class and initializes it to the second value of the pair
            
                // if a match is found, display the attributes of the matching asset
                if (targetName == asset->getName())
                {
                    asset->writeAttributesToStream(cout);   // cout arg means output will be displayed on console
                    found = true;   // flag var set to true to indicate a match was found
                }
            }

            // if no match found (flag var is false), inform user 
            if (!found)
                cout << "\nAsset \"" << targetName << "\" not found!";

            break;
        }
        default:
        {
            cout << "Invalid choice";
            break;
        }
    }

    // wait for user input before continuing
    cout << "\n\nEnter any key to continue...";
    cin.ignore();
    cin.get();
    
    return 0;
}

// saves all currently stored assets from program memory into a file of user's choice
void InventoryManager::saveToFile()
{
    system("clear");
    system("cls");

    string userFilename;
    ofstream outputFile;    // creates output file stream object

    // get filename for file assets will be saved to 
    cout << "\nEnter filename to save data to (leave empty for default). "
         << "\nWARNING: If file already exists, it WILL BE OVERWRITTEN!\n"
         << "\nFilename: ";
    cin.ignore();
    getline(cin, userFilename);

    // if user DOES NOT leave input empty, open object with user filename
    if (userFilename != "")
        outputFile.open(userFilename);
    // else (no input given), open object with default filename
    else 
        outputFile.open("assets.txt");

    // if file opens correctly, write attributes for all assets to file
    if (outputFile)
    {
        // makes pair data type named pair to represent 1 singular key:value pair from unordered_map assetMap
        // this pair represents one id:object element in the unordered_map
        for (pair< const int, unique_ptr<Asset>>& pair : assetMap)
        {
            unique_ptr<Asset>& asset = pair.second; // makes object called asset of Asset class and initializes it to the second value of the pair

            asset->writeAttributesToStream(outputFile); // outputFile arg means output will be sent to file (not console like in cout)
        }
    }
    else
        cout << "\nError opening the file!\n";

    outputFile.close();
}

// adds assets into program memory from existing file of user's choice
void InventoryManager::readFromFile()
{
    
    system("clear");
    system("cls");

    string inputFilename;
    ifstream inputFile;    // creates output file stream object

    cout << "\nEnter filename to read data from (leave empty for default). "
         << "\nFilename must include a \".txt\" extension at the end.\n"
         << "\nFilename: ";
    cin.ignore();
    getline(cin, inputFilename);

    // if user didn't supply a filename, use default
    if (inputFilename != "")
        inputFile.open(inputFilename);
    // else, use provided filename
    else
        inputFile.open("assets.txt");

    string line;

    // reads data from file as long as EOF isnt reached 
    while (getline(inputFile, line))
    {
        unique_ptr<Asset> newAsset;     // create new Asset object to store attributes for

        // creates new object of applicable type depending on asset type provided in file
        if (line == "Type: Desktop")
            newAsset = make_unique<Desktop>();
        else if (line == "Type: Server")
            newAsset = make_unique<Server>();
        else if (line == "Type: Mobile")
            newAsset = make_unique<Mobile>();
        else
        {
            cout << "\nError reading asset type from file!\n";
            return;
        }

        newAsset->readAttributesFromFile(inputFile);    // reads all attributes from file into newAsset object

        assetMap.emplace(newAsset->getID(),std::move(newAsset));    // changes ownership of newAsset from InventoryManager to assetMap

        getline(inputFile, line); // skip separator (---) between assets in file
    }

    // if no input can be received from file
    if (!getline(inputFile, line)) 
        cout << "\nError opening the file!\n";

    inputFile.close();
}


