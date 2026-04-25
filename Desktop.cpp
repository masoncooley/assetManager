// Implementation file for class Desktop

#include "Desktop.h"
#include "Asset.h"
#include "Computer.h"
#include "InputValidation.h"

#include <cctype>   // needed for toupper
#include <iostream> // needed for cin,cout,istream,ostream
#include <thread>   // needed for sleep_for() function
#include <chrono>   // needed for seconds() inside of sleep_for function

using namespace std;

// default constructor
Desktop::Desktop()
{   
    hasGPU = false;
    GPUmodel = "No GPU";
    VRAMcapacity = 0;
    setAssetType("Desktop");
}

// constructor with arguments
Desktop::Desktop(bool dedGPU, string model, int vram)
{
    hasGPU = dedGPU;
    GPUmodel = model;
    VRAMcapacity = vram;
}

// overridden Asset function to send attributes to an output stream 
// if cout passed as arg, data will be sent to console 
// if ofstream file object passed as arg, data will be passed to file 
void Desktop::writeAttributesToStream(ostream& os) const
{
    Computer::writeAttributesToStream(os);  // displays attributes common to all computers

    os << boolalpha;  // makes bool values print in true/false instead of 0/1

    os << "Dedicated GPU: " << hasGPU << endl;
    os << "GPU model: " << GPUmodel << endl;
    os << "GPU VRAM capacity: " << VRAMcapacity << "GB" << endl;
    os << "------------------------------------------\n";
}

// overridden Asset function to set attributes for a Desktop object
void Desktop::setAttributes()
{
    Computer::setAttributes();  // sets Computer-derived attributes for Desktop object

    char char_hasGPU;   
   
    // get user input
    cout << "Does the Desktop have a dedicated Graphics Card? (Y or N) ";
    cin >> char_hasGPU;

    char_hasGPU = toupper(char_hasGPU);     // standardizes Y/N input by converting to uppercase

    // check that input is valid for desktopGPU; if not, reprompt user
    while (char_hasGPU != 'N' && char_hasGPU != 'Y')
    {
        cout << "\nInput must be Y or N! ";
        cin.ignore();
        cin >> char_hasGPU;

        char_hasGPU = toupper(char_hasGPU);     // standardizes Y/N input by converting to uppercase
    }

    // if no GPU, pass default parameters into GPU
    if (char_hasGPU == 'N')
    {    
        // sets GPU-specific attributes to the defaults
        hasGPU = false;
        GPUmodel = "No GPU";
        VRAMcapacity = 0;
       
        // wait for user input before continuing
        cout << "\nNo GPU entered..." << endl;
        this_thread::sleep_for(chrono::seconds(3));     // waits for 3 secs so user can read output
    }
    // if there is GPU, get model and VRAM capacity 
    else if (char_hasGPU == 'Y')
    {
        hasGPU = true;  // user entered Y so the desktop has a GPU

        cout << "\nWhat's the model of the Graphics Card? ";
        cin.ignore();
        getline(cin, GPUmodel);     // getline is used b/c many GPU model names have spaces (ex: RTX 5090)

        VRAMcapacity = validateInteger("\nHow many GBs of VRAM does the Graphics Card have? ", 0, 999);
    }
    // theoretically this will never execute but it's here just in case 
    else 
       cout << "\n\nSomething went wrong with the input for GPU. Try again"; 
}

// displays all attributes for a Desktop object that can be modified
void Desktop::displayModifiableAttributes() const
{
    Computer::displayModifiableAttributes();    // prints out Asset and Computer attribute options

    cout << "(7) - Has dedicated graphics card\n"
         << "(8) - Graphics card model\n"
         << "(9) - Graphics card VRAM capacity\n";
}

// allows user to modify individual attributes for an existing Desktop asset
void Desktop::modifyAttributes(int attributeChoice)
{
    if (attributeChoice == 1)   // if user wants to modify Asset-controlled attribute
        Asset::modifyAttributes(attributeChoice);
    else if (attributeChoice >= 2 && attributeChoice <= 6)   // if user wants to modify Computer-controlled attribute
        Computer::modifyAttributes(attributeChoice);
    else if (attributeChoice >= 7 && attributeChoice <= 9)   // if user wants to modify Desktop-controlled attribute
    {
        switch (attributeChoice)
        {
            case 7:
            {
                char dedGPUChoice;

                cout << "\nEnter new status for dedicated graphics card: ";
                cin >> dedGPUChoice;

                dedGPUChoice = toupper(dedGPUChoice);     // standardizes Y/N input by converting to uppercase

                // sets hasGPU to true/false based on user choice
                if (dedGPUChoice == 'N')
                    hasGPU = false;
                else if (dedGPUChoice == 'Y')
                    hasGPU = true;
                else
                    cout << "\n\nGPU status choice wasn't Y or N!";
            }
                break;
            case 8:
                cout << "\nEnter new graphics card model: ";
                cin.ignore();
                getline(cin, GPUmodel);
                break;
            case 9:
                VRAMcapacity = validateInteger("\nEnter new graphics card VRAM capacity (in GBs): ", 0, 999);
                break;
        }
    }
    else if (attributeChoice == 0)  // if exit code was entered
        return;
    else
        cout << "\nSomething went wrong with the input for attribute choice!";
}

// takes data from input stream and uses the data to set values of attributes
// when ifstream file objects passed as arg (like in InventoryManager.cpp), it will read lines from a file
void Desktop::readAttributesFromFile(istream& is)
{
    Computer::readAttributesFromFile(is);   // reads Asset-controlled attributes

    string line,
           GPUstatus;

    // assignment operations below search thru line with .find() until they reach the colon at the end of the attribute title, 
    // then create a new string (with substr) and set that string equal to the attribute value

    getline(is, line);  // reads 1 entire line from stream
    GPUstatus = line.substr(line.find(":") + 2);

    // converts true/false string from stream into bool and sets hasGPU accordingly
    if (GPUstatus == "true")
        hasGPU = true;
    else if (GPUstatus == "false")
        hasGPU = false;

    getline(is, line);  // reads 1 entire line from stream
    GPUmodel = line.substr(line.find(":") + 2);      // converts string to an int before assigning it to the attribute value

    getline(is, line);  // reads 1 entire line from stream
    VRAMcapacity = stoi(line.substr(line.find(":") + 2));      // converts string to an int before assigning it to the attribute value

}
