// Implementation file for class Server

#include "Server.h"
#include "Computer.h"
#include <iostream>

using namespace std;

// default constructor
Server::Server()
{
    uptime = 0;
    numCPUsockets = 1;
    memoryIsECC = false;
}

// constructor w/ arguments
Server::Server(unsigned timeUp, unsigned sockets, bool ecc)
{
    uptime = timeUp;
    numCPUsockets = sockets;
    memoryIsECC = ecc;
}

// overridden Asset function to display Server, Computer, and Asset attributes for a Server object
void Server::displayAttributes() const  // const makes the function immutable
{
    Computer::displayAttributes();  // displays attributes common to all computers 

    cout << "\nUptime: " << uptime << " days" << endl;
    cout << "# of CPU sockets: " << numCPUsockets << endl;
    cout << boolalpha;
    cout << "ECC memory: " << memoryIsECC << endl;

    cout << "----------------------------------------------------\n\n";
}

// overridden Asset function to set Server and Computer attributes for a Server object
void Server::setAttributes()
{
    Computer::setAttributes();  // sets Computer-derived attributes for Server object

    cout << "\nEnter uptime (in whole days): ";
    cin >> uptime;

    cout << "\nEnter # of CPU sockets: ";
    cin >> numCPUsockets;

    cout << "\nIs the installed memory ECC? ";
    cin >> memoryIsECC;
}
