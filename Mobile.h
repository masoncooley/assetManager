// Specification file for class Mobile

#ifndef MOBILE_H
#define MOBILE_H

#include "Asset.h"
using namespace std;

class Mobile : public Asset     // the ": public Asset" allows Mobile to inherit from Asset class
{
    private:
        string manufacturer,
               model;
        unsigned int storageCapacity;

    public:
        Mobile();   // default constructor
        Mobile(string, string, unsigned);     // constructor with arguments
};
#endif