// Implementation file for class Mobile

#include "Mobile.h"
#include <iostream>

using namespace std;


Mobile::Mobile()
{
    manufacturer = "Generic";
    model = "No model";
    storageCapacity = 0;
}

Mobile::Mobile(string make, string mobileModel, unsigned int capacity)
{
    manufacturer = make;
    model = mobileModel;
    storageCapacity = capacity;

}