// Specification file for class Asset
//
// The Asset class is meant to just act as a blueprint for ALL asset types


#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <string>
using namespace std;


class Asset
{

    private:
        int id;
        string name,
               assetType;
    public:
        Asset();    // default constructor
        virtual ~Asset() = default;   // destructor (MUST BE virtual b/c there are classes derived from Asset); 
                                      // default just means call the compiler-generated destructor instead of a custom one
        void setName(string);
        string getName() const;
        int getID() const;
        void regenerateID();
        void setAssetType(string);
        string getAssetType() const;

        // virtual keyword allows derived classes to have custom implementations of the applicable function
        virtual void writeAttributesToStream(ostream&) const;     // const ensures that the function is read-only (immutable)
        virtual void setAttributes() = 0;   // pure virtual function
        
        virtual void displayModifiableAttributes() const;
        virtual void modifyAttributes(int);

        virtual void readAttributesFromFile(istream&);
};
#endif
