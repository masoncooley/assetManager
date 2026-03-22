// Implementation file for class Desktop

#include "Desktop.h"
#include "Computer.h"
#include <iostream>

using namespace std;

// default constructor
Desktop::Desktop()
{   
    hasGPU = false;
    GPUmodel = "No GPU";
    VRAMcapacity = 0;
}

// constructor with arguements
Desktop::Desktop(bool dedGPU, string model, int vram)
{
    hasGPU = dedGPU;
    GPUmodel = model;
    VRAMcapacity = vram;
}

// overridden Asset function to display Desktop, Computer, and Asset attributes for Desktop object
void Desktop::displayAttributes() const   // const makes the function immutable
{
    Computer::displayAttributes();  // displays attributes common to all computers

    cout << boolalpha;  // makes bool values print in true/false instead of 0/1

    cout << "\nDedicated GPU: " << hasGPU << endl;
    cout << "GPU model: " << GPUmodel << endl;
    cout << "GPU VRAM capacity: " << VRAMcapacity << "GB" << endl;
    cout << "---------------------------------------\n\n";
}

// overridden Asset function to set Desktop and Computer attributes for Desktop object
void Desktop::setAttributes()   // not const bc the member variables must be changed
{
    Computer::setAttributes();  // sets Computer-derived attributes for Desktop object

    char char_hasGPU;   
    
    cout << "Does the Desktop have a dedicated Graphics Card? (Y or N) ";
    cin >> char_hasGPU;

    // check that input is valid for desktopGPU; if not, reprompt user
    while (char_hasGPU != 'N' && char_hasGPU != 'n' && char_hasGPU != 'Y' && char_hasGPU != 'y')
    {
        cout << "\nInput must be Y or N! ";
        cin.ignore();
        cin >> char_hasGPU;
    }

    // if no GPU, pass default parameters into GPU
    if (char_hasGPU == 'N' || char_hasGPU == 'n')
    {    
        Desktop();
        
        cout << "No GPU entered, press any key to exit...";
        cin.get();
    }
    // if there's GPU, get model and VRAM capacity 
    else if (char_hasGPU == 'Y' || char_hasGPU == 'y')
    {
        hasGPU = true;  // user entered Y so there is a GPU

        cout << "\nWhat's the model of the Graphics Card? ";
        cin.ignore();
        getline(cin, GPUmodel);

        cout << "\nHow many GBs of VRAM does the Graphics Card have? ";
        cin >> VRAMcapacity;

    }

    // theoretically this will never execute but it's here just in case 
    else 
       cout << "\n\nSomething went wrong with the input for GPU. Try again"; 

}
