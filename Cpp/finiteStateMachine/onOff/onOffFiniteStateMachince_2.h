
#include <iostream>
using namespace std;

class Machine;

class State
{
    public:
        virtual void on(Machine *m);
        virtual void off(Machine *m);
        virtual void show() =0;
};


class ON: public State
{
    public:
        void off(Machine *m);
        void show();
};

class OFF: public State
{
    public:
        void on(Machine *m);
        void show();
};

class Machine
{
    private:
        class State *current;

    public:
        Machine(); 

        // actions
        void on();
        void off();

        //states 
        enum eState
        {
            ON_STATE,
            OFF_STATE  
        };

        ON  on_;
        OFF off_;

        void setCurrent(eState s);
        void show();

};

