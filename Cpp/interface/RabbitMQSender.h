#ifndef _RABBITMQ_SENDER_H
#define _RABBITMQ_SENDER_H

#include <string>
using namespace std;

#include "IBroker.h"

class RabbitMQSender : public IBroker
{
    private:
        string m_host;
        string m_port;
        string m_exchange;
        string m_routingKey; 

    public:       
        RabbitMQSender(string host, 
                       string port,
                       string exchange,
                       string routingKey):
            m_host(host),
            m_port(port),
            m_exchange(exchange),
            m_routingKey(routingKey)
        {};            

        virtual void send(int m);
        virtual void receive();

        int EstablishConnection();
        BOOL IsConnectionEstablished(){return m_IsConnected != CnS_Closed ;}

        void ShutdownConnection();

        ConnState GetConnectionState(){return m_IsConnected; }

};

#endif // _RABBITMQ_SENDER_H
