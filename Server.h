// Specification file for class Server

#ifndef SERVER_H
#define SERVER_H

#include "Asset.h"

class Server : public Asset     // the ": public Asset" allows Server to inherit from Asset class
{
    private:
        unsigned int uptime,
                     numCPUsockets;
        bool memoryIsECC;

    public:
        Server();   // default constructor
        Server(unsigned, unsigned, bool);     // constructor with arguments
};
#endif