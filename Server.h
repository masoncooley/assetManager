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

    // functions marked "override" will override virtual functions defined in Asset
    public:
        Server();   // default constructor
        Server(unsigned, unsigned, bool);     // constructor with arguments
        void writeAttributesToStream(ostream&) const override;  
        void setAttributes() override;
        
        void displayModifiableAttributes() const override;
        void modifyAttributes(int) override;

        void readAttributesFromFile(istream&) override;
};
#endif
