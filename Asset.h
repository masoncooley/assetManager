// Specification file for class Asset

/*
The Asset class is meant to just act as a blueprint for ALL asset types

Every asset is going to have an ID and name, regardless of type

*/


#ifndef ASSET_H
#define ASSET_H

class Asset
{

    private:
        string id,
               name;
    public:
        Asset();
};
#endif