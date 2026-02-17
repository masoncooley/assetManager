// Specification file for class InventoryManager

/*
The InventoryManager class is meant to be the engine of the entire inventory program

It should be able to see and change every aspect of the assets

*/


#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

class InventoryManager
{
    private:

    // all functions are temporarily of return type "void" until I know exactly what they do and what return type they need
    public:
        void getAssetTypes();
        void getFullAssetList();
        void addAsset();
        void modifyAsset();
        void removeAsset();
        void searchAsset();
        void filterAsset();
        void saveToFile();
        void readFromFile();


};
#endif