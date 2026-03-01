// Implementation file for class Asset

#include "Asset.h"
#include <iostream>
#include <cstdlib>  // needed for srand function
#include <ctime>    // needed to use time function

using namespace std;

// generates random ID value
int generateRandomID()
{
    const int MIN_VALUE = 1,
              MAX_VALUE = 10000; // 10000 is an arbitrary limit
    unsigned int seed = time(0);    // defines seed value
                                    // unsigned b/c time is never negative

    int randNum;

    srand(seed);    // sets seed value for rand function

    randNum = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE; // calculates rand num between 1-10000
    
    return randNum;
}

// sets id and name if none are supplied by the user
Asset::Asset()
{
    id = generateRandomID();
    name = "No Name Given";
}

// sets asset name with name supplied as argument
void Asset::setName(string n)
{
    name = n;
}

// get asset name
string Asset::getName()
{
    return name;
}

// get asset ID
int Asset::getID()
{
    return id;
}
