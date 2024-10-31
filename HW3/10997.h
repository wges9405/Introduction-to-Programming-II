#ifndef FUNCTION_H
#define FUNCTION_H
#include<iostream>
#include<string.h>
using namespace std;

class ListNode
{
    friend class List_queue; //make List_queue a friend
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

class List_queue {
    public:
        List_queue();
        ~List_queue();
        void enqueue(const int &);
        void dequeue();
        void print();
    private:
        ListNode *head;
        ListNode *tail;
};

//////////////////////////////////////////////////////////////

List_queue::List_queue() {
    this->head = NULL;
    this->tail = NULL;
}

List_queue::~List_queue() {
    ListNode *temp;
    while (this->head != NULL) {
        temp = this->head;
        this->head = this->head->nextPtr;
        delete(temp);
    }
}

void List_queue::enqueue(const int &num) {
    ListNode *temp;

    if (this->head == NULL) {
        this->head = new ListNode(num);
        this->tail = this->head;
    }
    else {
        temp = new ListNode(num);
        temp->prevPtr = this->tail;
        this->tail->nextPtr = temp;
        this->tail = temp;
    }
}

void List_queue::dequeue() {
    ListNode *temp;

    if (this->head != NULL) {
        temp = this->head;

        if (this->head->nextPtr != NULL) {
            this->head = this->head->nextPtr;
            this->head->prevPtr = NULL;
            delete(temp);
        }
        else {
            this->head = NULL;
            delete(temp);
        }
    }
}

void List_queue::print() {
    ListNode *temp;
    temp = this->head;
    while (temp != NULL) {
        if (temp->nextPtr != NULL)
            cout << temp->data << " ";
        else
            cout << temp->data;
        temp = temp->nextPtr;
    }
}

/*
I:
enqueue 26
enqueue 120
dequeue
print
dequeue
print
enqueue 36
enqueue 18
print
O:
120

36 18
*/
#endif


