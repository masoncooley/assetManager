// Implementation file for class Desktop

#include "Desktop.h"
#include <iostream>

using namespace std;


Desktop::Desktop()
{   
    hasGPU = false;
    GPUmodel = "No model given";
    VRAMcapacity = 0;
}

Desktop::Desktop(bool dedGPU, string model, int vram)
{
    hasGPU = dedGPU;
    GPUmodel = model;
    VRAMcapacity = vram;
}