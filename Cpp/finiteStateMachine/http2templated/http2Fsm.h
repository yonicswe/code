
#include <iostream>
using namespace std;

template <class SIDE>
class Http2Fsm;



//================ the states ============================ 
//  <<interface>> to hold the events that are handled 
//  by the states 
template<class SIDE> 
class Http2State
{
    public:
        virtual void show()                         =0;
        virtual void handlePacket(Http2Fsm<SIDE> *m)      =0;
        virtual void headersFrame(Http2Fsm<SIDE> *m)      =0;
        virtual void dataFrame(Http2Fsm<SIDE> *m)         =0;
        virtual void finishedFrame(Http2Fsm<SIDE> *m)     =0;
        virtual void continuationFrame(Http2Fsm<SIDE> *m) =0;          
        virtual int dataAccounting(Http2Fsm<SIDE> *m);
        virtual void addData2Stream() =0;
};

// data state class
template<class SIDE> 
class Http2NoneState: public Http2State<SIDE>
{
    public:
        virtual void show();                             
        virtual void handlePacket(Http2Fsm<SIDE> *m);
        virtual void headersFrame(Http2Fsm<SIDE> *m);
        virtual void dataFrame(Http2Fsm<SIDE> *m);
        virtual void finishedFrame(Http2Fsm<SIDE> *m);
        virtual void continuationFrame(Http2Fsm<SIDE> *m);          
        virtual int  dataAccounting(Http2Fsm<SIDE> *m);
        virtual void addData2Stream();
};

// headers state class
template<class SIDE> 
class Http2HeaderState: public Http2State<SIDE>
{
    public:
        virtual void show(); 
        virtual void handlePacket(Http2Fsm<SIDE> *m);
        virtual void headersFrame(Http2Fsm<SIDE> *m);
        virtual void dataFrame(Http2Fsm<SIDE> *m);
        virtual void finishedFrame(Http2Fsm<SIDE> *m);
        virtual void continuationFrame(Http2Fsm<SIDE> *m);          
        virtual void addData2Stream();
};

// data state class
template<class SIDE> 
class Http2DataState: public Http2State<SIDE>
{
    public:
        virtual void show(); 
        virtual void handlePacket(Http2Fsm<SIDE> *m);
        virtual void headersFrame(Http2Fsm<SIDE> *m);
        virtual void dataFrame(Http2Fsm<SIDE> *m);
        virtual void finishedFrame(Http2Fsm<SIDE> *m);
        virtual void continuationFrame(Http2Fsm<SIDE> *m);          
        virtual void addData2Stream();
};

//================ the machine ============================ 
typedef struct ClientSide ClientSide;
typedef struct ServerSide ServerSide;

template<class SIDE>
class Http2Fsm
{
    private:
        Http2State<SIDE> *current;

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

        Http2NoneState<SIDE>   noneState_;
        Http2HeaderState<SIDE> headerState_;
        Http2DataState<SIDE>   dataState_;

        // machine operations
        void setCurrent(eState s);
        void show();
        int  parseFrame();
        void addData2Stream(); 
        void controlFrame();
        int  dataAccounting();
};
//================ the machine ============================ 
