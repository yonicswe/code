
#include <iostream>
using namespace std;

class Http2Fsm;


//  <<interface>> to hold the events that are handled 
//  by the states 
class Http2State
{
    public:
        virtual void show()                         =0;
        virtual void handlePacket(Http2Fsm *m)      =0;
        virtual void headersFrame(Http2Fsm *m)      =0;
        virtual void dataFrame(Http2Fsm *m)         =0;
        virtual void finishedFrame(Http2Fsm *m)     =0;
        virtual void continuationFrame(Http2Fsm *m) =0;          
        virtual int dataAccounting(Http2Fsm *m);
};

// data state class
class Http2NoneState: public Http2State
{
    public:
        virtual void show();                             
        virtual void handlePacket(Http2Fsm *m);
        virtual void headersFrame(Http2Fsm *m);
        virtual void dataFrame(Http2Fsm *m);
        virtual void finishedFrame(Http2Fsm *m);
        virtual void continuationFrame(Http2Fsm *m);          
        virtual int  dataAccounting(Http2Fsm *m);
};

// headers state class
class Http2HeaderState: public Http2State
{
    public:
        virtual void show(); 
        virtual void handlePacket(Http2Fsm *m);
        virtual void headersFrame(Http2Fsm *m);
        virtual void dataFrame(Http2Fsm *m);
        virtual void finishedFrame(Http2Fsm *m);
        virtual void continuationFrame(Http2Fsm *m);          
};

// data state class
class Http2DataState: public Http2State
{
    public:
        virtual void show(); 
        virtual void handlePacket(Http2Fsm *m);
        virtual void headersFrame(Http2Fsm *m);
        virtual void dataFrame(Http2Fsm *m);
        virtual void finishedFrame(Http2Fsm *m);
        virtual void continuationFrame(Http2Fsm *m);          
};

//================ state machine ============================ 
// http2 finite state machine.
// 
class Http2Fsm
{
    private:
        Http2State *current;

    public:
        Http2Fsm(); 

        // events
        void handlePacket();
        void headersFrame(); 
        void dataFrame();    
        void finishedFrame();
        void continuationFrame();

        //states 
        enum eState
        {
            NONE_STATE,
            HEADERS_STATE,
            DATA_STATE  
        };

        Http2NoneState   noneState_;
        Http2HeaderState headerState_;
        Http2DataState   dataState_;

        // machine operations
        void setCurrent(eState s);
        void show();
        int  parseFrame();
        void addData2Stream(); 
        void controlFrame();
        int dataAccounting();
};

