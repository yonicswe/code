
#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <list>

class sri_t;

using namespace std;

class Hash {
	private:
		list<sri_t*> *m_table;

		unsigned long m_size;

		unsigned long hash_func(unsigned long long key);

	public:
		// constructor
		Hash(unsigned int size): m_size(size) 
		{
			m_table = new list<sri_t*>[m_size];
		}

		// destructor
		~Hash()
		{
			delete[] m_table;
		}

		void set(unsigned long long tid,
				 sri_t* sri); 

		int get(unsigned long long tid,
			    unsigned long long sccp_da,
                sri_t* sri_desc); 
};

#endif // _HASH_TABLE_H_
