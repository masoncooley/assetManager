// Specification file for class Mobile

#ifndef MOBILE_H
#define MOBILE_H

#include "Computer.h"
using namespace std;

class Mobile : public Computer // the ": public Asset" allows Mobile to inherit from Asset class
{
    private:
        string manufacturer,
               model;
        unsigned int storageCapacity;

    // functions marked "override" will override virtual functions defined in Asset
    public:
        Mobile();   // default constructor
        Mobile(string, string, unsigned);     // constructor with arguments
        void writeAttributesToStream(ostream&) const override;    // overrides virtual functions from Asset
        void setAttributes() override;              // to provide Mobile-specific behavior
        
        void displayModifiableAttributes() const override;
        void modifyAttributes(int) override;

        void readAttributesFromFile(istream&) override;
};
#endif
