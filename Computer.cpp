// Implementation file for class Computer
//
// Desktop and Server inherit from Computer class


#include "Computer.h"
#include "Asset.h"
#include <iostream>

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

// constructor with arguements
Computer::Computer(string model, unsigned cores, unsigned RAM, unsigned storageDev, unsigned storageCap)
{
    CPUmodel = model;
    numCPUcores = cores;
    RAMcapacity = RAM;
    numStorageDevices = storageDev;
    totalStorageCapacity = storageCap;
}

// overridden Asset function to display Computer and Asset attributes
void Computer::displayAttributes() const
{
    Asset::displayAttributes();     // displays general Asset info (ID and name)

    cout << "CPU model: " << CPUmodel << endl;
    cout << "# of CPU cores: " << numCPUcores << endl;
    cout << "RAM capacity: " << RAMcapacity << "GB" << endl;
    cout << "# of storage devices: " << numStorageDevices << endl;
    cout << "Total storage capacity: " << totalStorageCapacity << "GB" << endl;
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
