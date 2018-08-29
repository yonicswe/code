#ifndef _IBROKER_H_ 
#define _IBROKER_H_ 

class IBroker {
    
    public:
        virtual void send(int) =0;
        virtual void receive() =0; 

};
#endif // _IBROKER_H 
