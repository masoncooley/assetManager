// Implementation file for class Asset

#include "Asset.h"
#include <iostream> // needed for cin,cout,istream,ostream
#include <cstdlib>  // needed for srand function

using namespace std;

// generates and returns random ID value
int generateRandomID()
{
    const int MIN_VALUE = 1,
              MAX_VALUE = 9999; // only want 4 digit IDs 

    int randNum;

    // seed is set in main()
    
    randNum = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE; // calculates rand num between 1-10000
    
    return randNum;
}

// sets id and name if none are supplied by the user
Asset::Asset()
{
    id = generateRandomID();
    name = "No Name Given";
}

// sets asset name with name supplied as argument
void Asset::setName(string n)
{
    name = n;
}

// get asset name
string Asset::getName() const
{
    return name;
}

// get asset ID
int Asset::getID() const
{
    return id;
}

// generates a new random getID
// used only when duplicate ID was created 
void Asset::regenerateID()
{
    id = generateRandomID();
}

// sets asset type (ex: Desktop, Server, Mobile)
void Asset::setAssetType(string type)
{
    assetType = type;
}

// returns asset type (ex: Desktop, Server, Mobile)
string Asset::getAssetType() const
{
    return assetType;
}

// displays attribute values from any output stream type supplied to function
// if cout passed as arg, it will send data to user's screen
// if ofstream file objects passed as arg (like in InventoryManager.cpp), it will send data to a file
void Asset::writeAttributesToStream(ostream& os) const
{
    os << "Type: " << assetType << endl;
    os << "ID: " << id << endl;
    os << "Name: " << name << endl;
}

// pure virtual function; each child class will implement their own version
void Asset::setAttributes()
{}

// displays list of attributes available to modify; each child class will override
void Asset::displayModifiableAttributes() const
{
    cout << endl << endl;

    cout << "(1) - Name\n";
}

// allows user to modify individual attributes for an existing asset
// attributeChoice serves no purpose here (i think its needed for child functions tho)
void Asset::modifyAttributes(int attributeChoice)
{
    cout << "\nEnter new name: ";
    cin.ignore();
    getline(cin, name);
}

// takes input from an input stream and sets appropriate variables based on input data
// when ifstream file objects passed as arg (like in InventoryManager.cpp), it will read lines from a file
void Asset::readAttributesFromFile(istream& is)
{
    string line;

    // assignment operations below search thru line with .find() until they reach the colon at the end of the attribute title, 
    // then create a new string (with substr) and assigns it to the attribute value

    getline(is, line);  // gets 1 entire line from file
    id = stoi(line.substr(line.find(":") + 2));      // converts string to an int before assigning it to the attribute value

    getline(is, line);  // gets 1 entire line from file
    name = line.substr(line.find(":") + 2);
}
