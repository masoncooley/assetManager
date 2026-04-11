// Specification file for class Desktop

#ifndef DESKTOP_H
#define DESKTOP_H

#include "Computer.h"
#include <iostream>

class Desktop : public Computer // the ": public Asset" allows Desktop to inherit from Asset class
{
    private:
        bool hasGPU;
        string GPUmodel;
        int VRAMcapacity;
   
    // functions marked "override" will override virtual functions defined in Asset & Computer
    public:
        Desktop();   // default constructor
        Desktop(bool, string, int);     // constructor with arguments
        void writeAttributesToStream(ostream&) const override;
        void setAttributes() override;

        void displayModifiableAttributes() const override;
        void modifyAttributes(int) override;

        void readAttributesFromFile(istream&) override;

};
#endif
