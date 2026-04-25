// Implementation file for class InventoryManager


#include "InventoryManager.h"
#include "Asset.h"
#include "Server.h"
#include "Desktop.h"
#include "Mobile.h"
#include "InputValidation.h"

#include <cctype>   // needed for toupper()
#include <iostream> // needed for cin,cout
#include <unordered_map>    // needed for unordered_map
#include <memory>    // needed for smart pointers (unique_ptr)
#include <fstream>      // needed for file operations (ifstream, ofstream)
#include <thread>   // needed for sleep_for() function
#include <chrono>   // needed for seconds() inside of sleep_for function

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
    cout << "\033[2J\033[H";     // ANSI escape code to clear screen (can be used w/ any OS)

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
    cout << "\033[2J\033[H";     // ANSI escape code to clear screen (can be used w/ any OS)

    cout << "Asset Types: \n"
         << "_____________\n";
    cout << "1 - Desktop\n" << "2 - Server\n" << "3 - Mobile Device\n";

    // get user choice for asset type
    int assetTypeChoice;
  
    assetTypeChoice = validateInteger("\nEnter the number for the type of asset to be created: ", 1, 3);

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

            if (assetMap.find(assetID) == assetMap.end())
                cout << "\nA new Desktop asset was NOT created. Contact developer ";
            else
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

            if (assetMap.find(assetID) == assetMap.end())
                cout << "\nA new Server asset was NOT created. Contact developer ";
            else
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
          
            if (assetMap.find(assetID) == assetMap.end())
                cout << "\nA new Mobile asset was NOT created. Contact developer ";
            else 
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
    assetID = validateInteger("\nRe-type ID of the asset you want to modify (for confirmation purposes): ", 0, 9999);

    // check that an asset with ID assetID actually exists 
    // .at() function will cause program to crash if called with nonexistent ID
    if (assetMap.find(assetID) == assetMap.end())
    {
        cout << "\nAn asset with that ID does not exist!";
        
        // waits for 3 secs before exiting to main menu
        cout << "\n\nExiting to main menu in 3 secs..." << endl;
        this_thread::sleep_for(chrono::seconds(3));
        return;
    }


    unique_ptr<Asset>& assetToModify = assetMap.at(assetID);    // sets current asset to be modified by function

    do 
    {
        cout << "\033[2J\033[H";     // ANSI escape code to clear screen (can be used w/ any OS)

        cout << "\nList of modifiable attributes:\n"
             << "_________________________________\n\n";

        assetToModify->displayModifiableAttributes();    // displays list of attributes that can be modified for specific asset type
        cout << "(0) - Exit modification menu \n";

        // gets attributeChoice and validates input until valid
        attributeChoice = validateInteger("\nEnter integer corresponding with the attribute you would like to modify: ", 0, 9);

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
    targetID = validateInteger("\nEnter the ID for the asset you wish to delete: ", 0, 9999);

    // check that an asset with ID targetID actually exists 
    // .at() function will cause program to crash if called with nonexistent ID
    if (assetMap.find(targetID) == assetMap.end())
    {
        cout << "\nAn asset with that ID does not exist!";
        
        // waits for 3 secs before exiting to main menu
        cout << "\n\nExiting to main menu in 3 secs..." << endl;
        this_thread::sleep_for(chrono::seconds(3));
        return;
    }

    unique_ptr<Asset>& assetToDelete = assetMap.at(targetID);   // creates new Asset object matching the asset user wants to delete
                                                                // in order to print out asset type, ID, and name

    // makes sure user wants to delete chosen asset
    cout << "\nAre you sure you want to delete " << assetToDelete->getAssetType() << " asset \"" << assetToDelete->getName() 
         << "\" with ID #" << assetToDelete->getID() << "? ";
    cout << "\nEnter \"CONFIRM\" to confirm deletion (enter \"NO\" to cancel deletion): ";
    cin >> confirmation;
   
    // standardizes confirmation string by converting each individual character to uppercase
    for (int i = 0; i < static_cast<int>(confirmation.length()); i++)
        confirmation[i] = toupper(confirmation[i]);

    // if user is sure, erases 
    if (confirmation == "CONFIRM")
    {
        assetMap.erase(targetID);   // erases asset stored at key targetID in assetMap

        // ensures that chosen asset was deleted by searching for it again
        if (assetMap.find(targetID) == assetMap.end())
            cout << "\n\nAsset successfully deleted! ";

        else 
            cout << "\n\nConfirmation received but Asset was not successfully deleted! Contact developer ";
    }

    // if user does not EXPLICITLY confirm deletion, nothing will be deleted
    else
        cout << "\n\nConfirmation not received. "; 

    // waits for 3 secs before exiting to main menu
    cout << "Exiting to main menu in 3 secs..." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    return;
}

// searches for a stored asset when given an ID or Name
// return code 0 indicates function executed correctly, code 1 means assetMap was empty or ID not found
int InventoryManager::searchAsset()
{
    cout << "\033[2J\033[H";     // ANSI escape code to clear screen (can be used w/ any OS)

    // if nothing is stored in the asset map, exit the function early to prevent unwanted behavior
    if (assetMap.empty())
    {
        cout << "\nThere are no assets to search for!";
        
        // wair for user input before continuing
        cout << "\nExiting to main menu in 4 secs...";
        this_thread::sleep_for(chrono::seconds(4));     // waits for 5 secs so user can read output

        return 1;   // code 1 indicates no assets present in map
    }

    int searchChoice = 0;

    // gets searchChoice and validates until valid input is entered
    searchChoice = validateInteger("Search by ID (enter 1) or Name (enter 2)? ", 1, 2);

    // searches by ID or Name based on user choice
    switch (searchChoice) 
    {
        case 1: // search by ID
        {
            int searchID;

            // gets searchID and validates until valid input is entered
            searchID = validateInteger("\n\nEnter the asset ID to search for: ", 0, 9999);

            auto idResult = assetMap.find(searchID);    // .find() returns an iterator

            // ensure chosen asset exists
            // idResult will = end of map if no key matching the input was found
            if (idResult == assetMap.end())
            {
                cout << "\nAn asset with that ID does not exist. \n\nExiting to main menu in 5 secs..." << endl;
                
                this_thread::sleep_for(chrono::seconds(5));     // pauses program for 5 secs to allow user to read output
                return 1;   // return code indicates that no asset was found 
            }
            else
            {
                unique_ptr<Asset>& assetResult = assetMap.at(searchID); // creates new Asset object and sets address to 
                                                                        // value associated with key searchID in the map
               
                cout << "\033[2J\033[H";     // ANSI escape code to clear screen (can be used w/ any OS)

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

            cout << "\033[2J\033[H";     // ANSI escape code to clear screen (can be used w/ any OS)

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

            // if no match found (flag var is false), inform user and exit
            if (!found)
            {
                cout << "\nAsset \"" << targetName << "\" not found!"
                     << "\nExiting to main menu in 5 secs..." << endl;
                
                this_thread::sleep_for(chrono::seconds(5));     // pauses program for 5 secs to allow user to read output
                return 1;   // return code indicates that no asset was found 
            }
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
    cout << "\033[2J\033[H";     // ANSI escape code to clear screen (can be used w/ any OS)

    string userFilename;
    ofstream outputFile;    // creates output file stream object

    // if there are no assets to store in file, inform user and exit to menu
    if (assetMap.empty())
    {
        cout << "\nThere are no assets stored in memory! "
             << "\nExiting to main menu in 5 secs..." << endl;

        this_thread::sleep_for(chrono::seconds(5));     // waits for 5 secs so user can read output
        return;

    }


    // get filename for file assets will be saved to 
    cout << "\nEnter filename to save data to (leave empty for default). "
         << "\nWARNING: If file already exists, it WILL BE OVERWRITTEN!\n"
         << "\nFilename: ";
    cin.ignore();
    getline(cin, userFilename);

    // if no filename was given, set file name to default
    if (userFilename == "")
        userFilename = "assets.txt";

    outputFile.open(userFilename);

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

        cout << "\nData saved to file \"" << userFilename << "\"! \n";
    }
    else
        cout << "\nError opening the file!\n";

    outputFile.close();

    // waits for 5 secs before exiting to main menu
    cout << "Exiting to main menu in 5 secs..." << endl;
    this_thread::sleep_for(chrono::seconds(5));
    return;

}

// adds assets into program memory from existing file of user's choice
void InventoryManager::readFromFile()
{
    cout << "\033[2J\033[H";     // ANSI escape code to clear screen (can be used w/ any OS)

    string inputFilename;
    ifstream inputFile;    // creates output file stream object

    cout << "\nEnter filename to read data from (leave empty for default). "
         << "\nFilename must include a \".txt\" extension at the end (unless empty).\n"
         << "\nFilename: ";
    cin.ignore();
    getline(cin, inputFilename);

    // if no filename was given, set file name to default
    if (inputFilename == "")
        inputFilename = "assets.txt";
        
    // inform user that current assets will be retained after file import
    if (assetMap.size() != 0)
    {
        cout << "\n\nNOTICE: There are currently " << assetMap.size() << " asset(s) stored in program memory." 
             << "\nAssets from \"" << inputFilename << "\" will be appended to current list of assets. \n";
        this_thread::sleep_for(chrono::milliseconds(4500));   // wait for 4.5 secs so user can read message before file is opened
    }
    inputFile.open(inputFilename);


    if (inputFile.fail())
    {
        cout << "\nFile \"" << inputFilename << "\" was not found, exiting to main menu in 5 secs..." << endl;
        
        this_thread::sleep_for(chrono::seconds(5));     // waits for 5 secs before exiting so user can read output 
        return;
    }

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

    inputFile.close();

    cout << "\nAsset data successfully read from \"" << inputFilename << "\" \n";

    cout << "\nExiting to main menu in 5 secs..." << endl;
    this_thread::sleep_for(chrono::seconds(5));
    return;
}


