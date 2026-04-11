// Implementation file for class Computer
//
// Desktop and Server inherit from Computer class


#include "Computer.h"
#include "Asset.h"
#include <iostream>     // needed for cin,cout,istream,ostream

using namespace std;

// default constructor
Computer::Computer()
{    
    CPUmodel = "No model";
    numCPUcores = 0;
    RAMcapacity = 0;
    numStorageDevices = 0;
    totalStorageCapacity = 0;
}

// constructor with arguments
Computer::Computer(string model, unsigned cores, unsigned RAM, unsigned storageDev, unsigned storageCap)
{
    CPUmodel = model;
    numCPUcores = cores;
    RAMcapacity = RAM;
    numStorageDevices = storageDev;
    totalStorageCapacity = storageCap;
}

// overridden Asset function to send Computer and Asset attributes to an output stream
// if cout passed as arg, data will be sent to console 
// if ofstream file object passed as arg, data will be passed to file
void Computer::writeAttributesToStream(ostream& os) const
{
    Asset::writeAttributesToStream(os);     // displays general Asset info (ID, name, assetType)

    os << "CPU model: " << CPUmodel << endl;
    os << "# of CPU cores: " << numCPUcores << endl;
    os << "RAM capacity: " << RAMcapacity << "GB" << endl;
    os << "# of storage devices: " << numStorageDevices << endl;
    os << "Total storage capacity: " << totalStorageCapacity << "GB" << endl;
}

// overridden Asset function to set Computer attributes
void Computer::setAttributes()
{
    Asset::setAttributes(); // this doesn't actually do anything; Asset attributes are set w/ setID() and setName()
                            // however, it's needed so that objects created in InventoryManager can set Computer attributes thru an Asset pointer 

    cout << "\nEnter CPU model: ";
    getline(cin, CPUmodel);

    cout << "\nEnter # of CPU cores: ";
    cin >> numCPUcores;

    cout << "\nEnter RAM capacity (in GB): ";
    cin >> RAMcapacity;

    cout << "\nEnter # of storage devices (hard drives, solid state drive, etc): ";
    cin >> numStorageDevices;

    cout << "\nEnter total storage capacity (in GB) (1TB = 1000GB): ";
    cin >> totalStorageCapacity;
}

// displays list of attributes that can be modified
void Computer::displayModifiableAttributes() const
{
    Asset::displayModifiableAttributes();        // displays modifiable options common to all Assets (Name)

    cout << "(2) - CPU model\n"
         << "(3) - # of CPU cores\n"
         << "(4) - RAM capacity (in GBs)\n"
         << "(5) - # of storage devices\n"
         << "(6) - Total storage capacity (in GBs)\n";
}

// allows user to modify individual attributes for an existing asset
void Computer::modifyAttributes(int attributeChoice)
{
    if (attributeChoice == 1)   // if user wants to modify Asset-controlled attribute
        Asset::modifyAttributes(1);

    if (attributeChoice >= 2 && attributeChoice <= 6)   // if user wants to modify Computer-controlled attributes
    {
        switch (attributeChoice)
        {
            case 2:
                cout << "\nEnter new CPU model: ";
                cin.ignore();
                getline(cin, CPUmodel);
                break;
            case 3:
                cout << "\nEnter new # of CPU cores: ";
                cin >> numCPUcores;
                break;
            case 4:
                cout << "\nEnter new RAM capacity (in GBs): ";
                cin >> RAMcapacity;
                break;
            case 5: 
                cout << "Enter new # of storage devices: ";
                cin >> numStorageDevices;
                break;
            case 6:
                cout << "\nEnter new total storage capacity (in GBs): ";
                cin >> totalStorageCapacity;
                break;
        }
    }
}

// takes data from input stream and uses the data to set values of attributes
// when ifstream file objects passed as arg (like in InventoryManager.cpp), it will read lines from a file
void Computer::readAttributesFromFile(istream& is)
{
    Asset::readAttributesFromFile(is);  // reads Asset-controlled attributes first

    string line;

    // assignment operations below search thru line with .find() until they reach the colon at the end of the attribute title, 
    // then create a new string (with substr) and set that string equal to the attribute value

    getline(is, line);  // reads 1 entire line from stream
    CPUmodel = line.substr(line.find(":") + 2);

    getline(is, line);  // reads 1 entire line from stream
    numCPUcores = stoi(line.substr(line.find(":") + 2));      // converts string to an int before assigning it to the attribute value

    getline(is, line);  // reads 1 entire line from stream
    RAMcapacity = stoi(line.substr(line.find(":") + 2));      // converts string to an int before assigning it to the attribute value

    getline(is, line);  // reads 1 entire line from stream
    numStorageDevices = stoi(line.substr(line.find(":") + 2));      // converts string to an int before assigning it to the attribute value

    getline(is, line);  // reads 1 entire line from stream
    totalStorageCapacity = stoi(line.substr(line.find(":") + 2));      // converts string to an int before assigning it to the attribute value

}

