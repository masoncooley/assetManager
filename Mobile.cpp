// Implementation file for class Mobile

#include "Mobile.h"
#include "Asset.h"
#include <iostream>

using namespace std;

// default constructor
Mobile::Mobile()
{
    manufacturer = "Generic";
    model = "No model";
    storageCapacity = 0;
}

// constructor w/ arguments
Mobile::Mobile(string make, string mobileModel, unsigned int capacity)
{
    manufacturer = make;
    model = mobileModel;
    storageCapacity = capacity;

}

// overridden Asset function to display all attributes for a Mobile asset
void Mobile::displayAttributes() const
{
    Asset::displayAttributes();     // displays general Asset attributes

    cout << "Device manufacturer: " << manufacturer << endl;
    cout << "Device model: " << model << endl;
    cout << "Storage capacity: " << storageCapacity << "GB" << endl; 

    cout << "------------------------------------------\n\n";
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

    cout << "\nEnter storage capacity (in GB): ";
    cin >> storageCapacity;
}
