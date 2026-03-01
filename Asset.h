// Specification file for class Asset

/*
The Asset class is meant to just act as a blueprint for ALL asset types

Every asset is going to have an ID and name, regardless of asset type

*/


#ifndef ASSET_H
#define ASSET_H

#include <string>
using namespace std;


class Asset
{

    private:
        int id;
        string name;
    public:
        Asset();    // default constructor
        virtual ~Asset() = default;   // destructor (MUST BE virtual b/c there are classes derived from Asset); 
                                      // default just means call the compiler-generated destructor instead of a custom one
        void setName(string);
        string getName();
        int getID();
        // no setID function b/c I only want IDs to be set by the program, not by the user
};
#endif