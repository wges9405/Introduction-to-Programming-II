#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>
#include<string.h>
using namespace std;
class ListNode
{
    friend class List_stack; //make List_stack a friend
    public:
        ListNode( const int &info ) //constructor
        : data( info ), nextPtr( NULL ), prevPtr( NULL )
        {
        } //end ListNode constructor

    private:
        int data; //data
        ListNode *nextPtr; // next node in list
        ListNode *prevPtr;
}; //end class ListNode

class List_stack {
    public:
        List_stack();
        ~List_stack();
        void push(const int &);
        void pop();
        void print();
    private:
        ListNode *head;
        ListNode *tail;
};

///////////////////////////////////////////////////////////////

List_stack::List_stack() {  // initial
    this->head = NULL;
    this->tail = NULL;
}
List_stack::~List_stack() {
    while (this->head!=NULL) {
        ListNode *temp = this->head;
        this->head = this->head->nextPtr;
        this->head->prevPtr = NULL;
        delete(temp);
    }
}
void List_stack::push(const int &num) {
    if (this->head==NULL) {
        this->head = new ListNode(num);
        this->tail = this->head;
    }
    else {
        ListNode *temp = new ListNode(num);
        temp->prevPtr = this->tail;
        this->tail->nextPtr = temp;
        this->tail = temp;
    }
}
void List_stack::pop() {
    ListNode *temp = this->tail;
    if (this->head == this->tail)
        this->head = this->tail = NULL;
    else {
        this->tail = temp->prevPtr;
        this->tail->nextPtr = temp->nextPtr;
    }
    delete(temp);

}
void List_stack::print() {
    ListNode *temp = this->tail;
    while (temp!=NULL) {
        if (temp->prevPtr!=NULL)
            cout << temp->data << " ";
        else
            cout << temp->data;
        temp = temp->prevPtr;
    }
}
/*
I:
push 2
push 120
pop
print
pop
print
push 22
push 35
print

O:
2

35 22
*/
#endif // FUNCTION_H
