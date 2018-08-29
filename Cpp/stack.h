
#pragma once

#include <iostream>
using namespace std;

template <class T> 
class node
{
public:
   // members   
   T data;
   node* next;
   
   // methods   
   node(T _data):data(_data){};
   node(void):next(NULL){};

   void show(void); 
};


template <class T> 
class list : public node <T>
{
private:
   // members 
   node<T> *head;
   node<T> *tail;

public:
   // methods
   list(void):head(NULL),tail(NULL){};
   ~list(void); 
   void add(T _data);
   void show(void);
};



template <class T> 
class stack
{
   T* head;
public:

   stack(void):head(NULL){};
   ~stack(void); 
   void push(T

};
