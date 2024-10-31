#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
using namespace std;

class Char{
	friend class Str;
	private:
		Char(char text):next(NULL){
			this->text=text;
		}

		~Char(){
            if(next)
                delete next;
		}

		void print(){
            cout<<text;
            if(next)
                next->print();
		}

		char text;
		Char *next;
};

class Str{
	public:
		Str():head(NULL),tail(NULL){}
		Str(char*); // construct a new Str by linked list of Char
		Str(const Str &); // copy constructor
		~Str(){
            if(head)
                delete head;
		}

		Str& strInsert(const Str &);

		Str& strSwap(Str &s){
			Str *tmp=new Str(*this);
			this->~Str();

			*this=s;
            s=*tmp;

            tmp->head=NULL;
            delete tmp;
			return *this;
		}

		void strPrint(){
            if(head)
                head->print();
            cout<<endl;
		}

	private:
		Char *head;
		Char *tail;
};

/////////////////////////////////////////////////////////

Str::Str(char *input) {
    this->head = new Char(input[0]);
	this->tail = this->head;
    int i=1;
    while (input[i]!='\0') {
        this->tail->next = new Char(input[i]);
        this->tail = this->tail->next;
		i++;
    }
}

Str::Str(const Str & s) {
    this->head = new Char(s.head->text);
	this->tail = this->head;
    Char *temp = s.head->next;
    while (temp) {
        this->tail->next = new Char(temp->text);
        this->tail = this->tail->next;
        temp = temp->next;
    }
}

Str& Str::strInsert(const Str & s) {
    Str *tmp = new Str(s);
    this->tail->next = tmp->head;
    this->tail = tmp->tail;

    tmp->head = NULL;
    delete tmp;
    return *this;
}
/*
I:
8
ABC
D
ABC
D
ABC
D
ABC
D
si 0 1
is 2 3
s 4 5
i 6 7
e

O:
DABC
ABC
D
ABCD
D
ABC
ABCD
D
*/
#endif
