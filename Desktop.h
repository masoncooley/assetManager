// Specification file for class Desktop

#ifndef DESKTOP_H
#define DESKTOP_H

#include "Computer.h"

class Desktop : public Computer // the ": public Asset" allows Desktop to inherit from Asset class
{
    private:
        bool hasGPU;
        string GPUmodel;
        int VRAMcapacity;
    
    public:
        Desktop();   // default constructor
        Desktop(bool, string, int);     // constructor with arguments
        void displayAttributes() const override;    // overrides virtual functions from Computer (which overrides from Asset)
        void setAttributes() override;              // to provide Desktop-specific attributes 

};
#endif
