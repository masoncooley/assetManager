// Implementation file for class Server

#include "Server.h"
#include "Asset.h"
#include "Computer.h"
#include "InputValidation.h"

#include <cctype>   // needed for toupper 
#include <iostream>

using namespace std;

// default constructor
Server::Server()
{
    uptime = 0;
    numCPUsockets = 1;
    memoryIsECC = false;
    setAssetType("Server");
}

// constructor w/ arguments
Server::Server(unsigned timeUp, unsigned sockets, bool ecc)
{
    uptime = timeUp;
    numCPUsockets = sockets;
    memoryIsECC = ecc;
}

// overridden Asset function to send Server and Computer attributes to an output stream
// if cout passed as arg (os), data will be sent to console 
// if ofstream file object passed as arg (os), data will be passed to file
void Server::writeAttributesToStream(ostream& os) const
{
    Computer::writeAttributesToStream(os);  // displays Computer-controlled attributes 

    os << "Uptime: " << uptime << " days" << endl;
    os << "# of CPU sockets: " << numCPUsockets << endl;
    os << boolalpha;
    os << "ECC memory: " << memoryIsECC << endl;

    os << "------------------------------------------\n";
}

// overridden Asset function to set Server and Computer attributes for a Server object
void Server::setAttributes()
{
    Computer::setAttributes();  // sets Computer-derived attributes for Server object

    uptime = validateInteger("\nEnter uptime (in whole days): ", 0, 99999);

    numCPUsockets = validateInteger("\nEnter # of CPU sockets: ", 0, 10);

    char eccMemoryChoice;

    // gets status of ECC memory and validates it
    do {
        cout << "\nIs the installed memory ECC? (Y or N) ";
        cin >> eccMemoryChoice;
        eccMemoryChoice = toupper(eccMemoryChoice); // standardizes eccMemoryChoice by converting to uppercase

    } while (eccMemoryChoice != 'Y' && eccMemoryChoice != 'N');

    // converts Y/N to true/false
    if (eccMemoryChoice == 'Y')
        memoryIsECC = true;
    else if (eccMemoryChoice == 'N')
        memoryIsECC = false;
}

// displays all attributes for a Server object that can be modified
void Server::displayModifiableAttributes() const
{
    Computer::displayModifiableAttributes();    // displays Computer-controlled attributes

    cout << "(7) - Uptime (in days)\n"
         << "(8) - # of CPU sockets\n"
         << "(9) - ECC memory?\n";
}

// allows user to modify individual attributes for an existing Server asset
void Server::modifyAttributes(int attributeChoice)
{
    if (attributeChoice == 1)   // if user wants to modify Asset-controlled attribute
        Asset::modifyAttributes(attributeChoice);
    else if (attributeChoice >= 2 && attributeChoice <= 6)   // if user wants to modify Computer-controlled attribute
        Computer::modifyAttributes(attributeChoice);
    else if (attributeChoice >= 7 && attributeChoice <= 9)   // if user wants to modify Server-controlled attribute
    {
        switch (attributeChoice)
        {
            case 7:
                uptime = validateInteger("\nEnter new uptime (in days): ", 0, 99999);
                break;
            case 8:
                numCPUsockets = validateInteger("\nEnter new # of CPU sockets: ", 0, 10);
                break;
            case 9:
            {
                char eccMemoryChoice;

            // gets status of ECC memory and validates it
                do {
                    cout << "\nIs the installed memory ECC? (Y or N) ";
                    cin >> eccMemoryChoice;
                    eccMemoryChoice = toupper(eccMemoryChoice); // standardizes eccMemoryChoice by converting to uppercase

                } while (eccMemoryChoice != 'Y' && eccMemoryChoice != 'N');

                // converts Y/N input to true/false
                if (eccMemoryChoice == 'Y')
                    memoryIsECC = true;
                else if (eccMemoryChoice == 'N')
                    memoryIsECC = false;
            }
        }
    }
}

// takes data from input stream and uses the data to set values of attributes
// when ifstream file objects passed as arg (like in InventoryManager.cpp), it will read lines from a file
void Server::readAttributesFromFile(istream& is)
{
    Computer::readAttributesFromFile(is);   // reads Asset-controlled attributes

    string line,
           ECCstatus;

    // assignment operations below search thru line with .find() until they reach the colon at the end of the attribute title, 
    // then create a new string (with substr) and set that string equal to the attribute value

    getline(is, line);  // reads 1 entire line from stream
    uptime = stoi(line.substr(line.find(":") + 2));      // converts string to an int before assigning it to the attribute value

    getline(is, line);  // reads 1 entire line from stream
    numCPUsockets = stoi(line.substr(line.find(":") + 2));      // converts string to an int before assigning it to the attribute value

    getline(is, line);  // reads 1 entire line from stream
    ECCstatus = line.substr(line.find(":") + 2);

    // converts string true/false to bool true/false
    if (ECCstatus == "true")
        memoryIsECC = true;
    else if (ECCstatus == "false")
        memoryIsECC = false;

}

