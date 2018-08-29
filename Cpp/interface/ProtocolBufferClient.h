#ifndef _PROTOCOL_BUFFER_CLIENT_H_

#include "ClientWrapper.h"
#include "RabbitMQSender.h"
#include <iostream>
#include <list>
using namespace std;

typedef enum {
  SENDER_TYPE_SOCKET,
  SENDER_TYPE_RABBITMQ    
}eSenderType ;

class ProtocolBufferClient 
{
    private:
        IBroker *m_sender;
        list<int> q;

    public:

        ProtocolBufferClient(eSenderType senderType); 
        void push(int m);
        void processMessages();
    
};

#define _PROTOCOL_BUFFER_CLIENT_H_
#endif // _PROTOCOL_BUFFER_CLIENT_H_
