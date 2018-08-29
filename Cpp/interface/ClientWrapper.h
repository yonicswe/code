#ifndef _CLIENT_WRAPPER_H_
#define _CLIENT_WRAPPER_H_

#include "IBroker.h"
#include <string>
using namespace std;

class SocketWrapper : public IBroker
{ 
    private:

    public:
        int    m_blockinMode;

        virtual int getBlockingMode() =0;
        virtual void setBlockingMode(int) =0;

};

class ClientWrapper : public SocketWrapper
{
    private:
        string m_host;
        int    m_port;       

    public:
        ClientWrapper(string host, int port):
            m_host(host),
            m_port(port)
            {}

        string getHost() { return m_host;} 
        int    getPort() { return m_port;}

        virtual void send(int m);
        virtual void receive(); 
        virtual int  getBlockingMode()      {return m_blockinMode  ;}
        virtual void setBlockingMode(int b) { m_blockinMode=b ;} 
};


#endif // _CLIENT_WRAPPER_H_
