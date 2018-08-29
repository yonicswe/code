
#include <vector>
using namespace std;

class Account;
class Customer;


class Account {
    private:
        int m_id;
        int m_balance;
    public:
        Account(){};
        Account(int id);

};


class Customer {
    private:
        int m_id;
        Account * m_account;

    public:
        Customer(int id); 
};



// singleton
class Bank { 

    public:


        static Bank *inst()
        {
            static Bank b;
            return &b;
        };

        void createCustomer();

    private:
        Bank();

    private: 
        int m_lastId;
        vector<Customer* > m_customerList;

};

