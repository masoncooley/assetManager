// Specification file for class Desktop

#ifndef DESKTOP_H
#define DESKTOP_H

#include "Asset.h"

class Desktop : public Asset     // the ": public Asset" allows Desktop to inherit from Asset class
{
    private:
        bool hasGPU;
        string GPUmodel;
        int VRAMcapacity;
    
    public:
        Desktop();   // default constructor
        Desktop(bool, string, int);     // constructor with arguments
};
#endif