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

    // functions marked "override" will override virtual functions defined in Asset    
    public:
        Computer(); // default constructor
        Computer(string model, unsigned cores, unsigned RAM, unsigned storageDev, unsigned storageCap); // constructor w/ arguements
        void writeAttributesToStream(ostream&) const override;  
        void setAttributes() override;  
        
        void displayModifiableAttributes() const override;
        void modifyAttributes(int) override;

        void readAttributesFromFile(istream&) override;
};
#endif

