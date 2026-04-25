// Implementation file for class Mobile

#include "Mobile.h"
#include "Asset.h"
#include "InputValidation.h"

#include <iostream> // needed for cin,cout,istream,ostream

using namespace std;

// default constructor
Mobile::Mobile()
{
    manufacturer = "Generic";
    model = "No model";
    storageCapacity = 0;
    setAssetType("Mobile");
}

// constructor w/ arguments
Mobile::Mobile(string make, string mobileModel, unsigned int capacity)
{
    manufacturer = make;
    model = mobileModel;
    storageCapacity = capacity;

}

// overridden Asset function to send Mobile attributes to an output stream
// if cout passed as arg (os), data will be sent to console 
// if ofstream file object passed as arg (os), data will be passed to file
void Mobile::writeAttributesToStream(ostream& os) const
{
    Asset::writeAttributesToStream(os);    // displays general Asset attributes

    os << "Device manufacturer: " << manufacturer << endl;
    os << "Device model: " << model << endl;
    os << "Storage capacity: " << storageCapacity << "GB" << endl; 

    os << "------------------------------------------\n";
}

// overridden Asset function to set Mobile-specific attributes
void Mobile::setAttributes()
{
    Asset::setAttributes();     // doesn't actually do anything bc the function implementation for this function is empty
                                // however, it's needed so that objects created in InventoryManager can set Mobile attributes thru an Asset pointer 

    cout << "\nEnter device manufacturer: ";
    getline(cin, manufacturer);

    cout << "\nEnter device model: ";
    getline(cin, model);

    storageCapacity = validateInteger("\nEnter storage capacity (in GB): ", 0, 9999);
}

// displays list of attributes that can be modified
void Mobile::displayModifiableAttributes() const
{
    Asset::displayModifiableAttributes();   // displays Asset-controlled attribute choices

    cout << "(2) - Device manufacturer\n"
         << "(3) - Device model\n"
         << "(4) - Storage capacity\n";
}

// allows user to modify individual attributes of a Mobile object
void Mobile::modifyAttributes(int attributeChoice)
{
    if (attributeChoice == 1)   // displays Asset-controlled attributes
        Asset::modifyAttributes(attributeChoice);
    else if (attributeChoice >= 2 && attributeChoice <= 4)   // displays Mobile-controlled attributes 
    {
        switch (attributeChoice)
        {
            case 2:
                cout << "\nEnter new device manufacturer: ";
                cin.ignore();
                getline(cin, manufacturer);
                break;
            case 3:
                cout << "\nEnter new device model: ";
                cin.ignore();
                getline(cin, model);
                break;
            case 4:
                storageCapacity = validateInteger("\nEnter new device storage capacity: ", 0, 9999);
                break;


        }
    }
}

// takes data from input stream and uses the data to set values of attributes
// when ifstream file objects passed as arg (is) (like in InventoryManager.cpp), it will read lines from a file 
void Mobile::readAttributesFromFile(istream& is)
{
    Asset::readAttributesFromFile(is);

    string line;

    // assignment operations below search thru line with .find() until they reach the colon at the end of the attribute title, 
    // then create a new string (with substr) and assign it to the attribute value
    getline(is, line);
    model = line.substr(line.find(":") + 2);

    getline(is, line);
    manufacturer = line.substr(line.find(":") + 2);

    getline(is, line);
    storageCapacity = stoi(line.substr(line.find(":") + 2));    // converts string to an int before assigning it to the attribute value

}

