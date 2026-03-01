// Implementation file for class Server

#include "Server.h"
#include <iostream>

using namespace std;

Server::Server()
{
    uptime = 0;
    numCPUsockets = 1;
    memoryIsECC = false;
}

Server::Server(unsigned timeUp, unsigned sockets, bool ecc)
{
    uptime = timeUp;
    numCPUsockets = sockets;
    memoryIsECC = ecc;
}