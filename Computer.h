// Specification file for class Computer
//  
// Both Desktop and Server should inherit attributes from Computer class


#ifndef COMPUTER_H
#define COMPUTER_H

#include "Asset.h"


class Computer : public Asset     // the ": public Asset" allows Computer to inherit from Asset class
{
    private:
        string CPUmodel;
        unsigned int numCPUcores,
                     RAMcapacity,
                     numStorageDevices,
                     totalStorageCapacity;

    public:
        Computer(); // default constructor
        Computer(string model, unsigned cores, unsigned RAM, unsigned storageDev, unsigned storageCap); // constructor w/ arguements
        void displayAttributes() const override;   // overrides virtual functions from Asset 
        void setAttributes() override;             // to provide Computer-specific behavior 
};
#endif

