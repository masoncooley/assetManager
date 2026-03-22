// Specification file for class Server

#ifndef SERVER_H
#define SERVER_H


#include "Computer.h"
class Server : public Computer // the ": public Asset" allows Server to inherit from Asset class
{
    private:
        unsigned int uptime,
                     numCPUsockets;
        bool memoryIsECC;

    public:
        Server();   // default constructor
        Server(unsigned, unsigned, bool);     // constructor with arguments
        void displayAttributes() const override;    // overrides virtual functions from Asset & Computer 
        void setAttributes() override;              // to provide Server-specific behavior
};
#endif
