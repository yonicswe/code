
#include <vector>
using namespace std;

class Account;
class Customer;


class Account {
    protected:
        int m_id;
        int m_balance;
    public:
        Account(){};
        Account(int id);
        virtual int getBalance();
        virtual void deposit(int amount);
        virtual void withdraw(int amount); 
};

class SavingAccount:public Account
{
    private:
        int m_intrestRate;
    public:
        SavingAccount(int interstRate);
};

class CheckingAccount:public Account
{
    private:
        bool m_overdraft;
    public:
        virtual void withdraw(int amount);
};

class AccountDecorator:public Account {
    private:
        Account* m_account;

    public: 
        AccountDecorator(Account *account) {m_account = account}
        virtual int  getBalance()        {m_account->getBalance()};
        virtual void deposit(int amount) {m_account->deposit(amount)};
        virtual void withdraw(int amount){m_account->withdraw(amount)}; 
};

class CommisionAccount:public AccountDecorator  {

    public:
        CommisionAccount(Account *account):AccountDecorator(amount){};

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

