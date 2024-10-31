/*#include <iostream>
using namespace std;

class Node
{
friend class List;
public:
    Node (string &name) : data(name), next(NULL) {};
private:
    string data;
    Node *next;
};

class List
{
public:
    List();
    ~List();
    void push(string &);
    void pop();
    void front();
private:
    Node *head;
    Node *tail;
};

List::List() {
    head = NULL;
    tail = NULL;
}

List::~List() {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

void List::push(string &name) {
    if (head == NULL)
        head = tail = new Node(name);
    else {
        Node *temp = new Node(name);
        tail->next = temp;
        tail = temp;
        temp = NULL;
        delete temp;
    }
}

void List::pop() {
    if (head != NULL) {
        Node *temp = head;

        if (head == tail) head = tail = NULL;
        else head = head->next;

        delete temp;
    }
}

void List::front() {
    if (head != NULL) cout << head->data << endl;
    else cout << "empty" << endl;
}

int main () {
    string buffer;
    List Queue;

    while (cin >> buffer) {
        if (buffer == "Push") {
            cin >> buffer;
            Queue.push(buffer);
        }
        else if (buffer == "Pop")
            Queue.pop();
        else if (buffer == "Front")
            Queue.front();
    }
}*/

#include <iostream>
#include <queue>
using namespace std;
int main () {
    queue <string> List;
    string buffer;

    while (cin >> buffer) {
        if (buffer == "Push") {
            if (cin >> buffer)
                List.push(buffer);
        }
        else if (buffer == "Pop") {
            if (!List.empty()) List.pop();
        }
        else if (buffer == "Front") {
            if (List.empty()) cout << "empty" << endl;
            else {
                cout << List.front() << endl;
            }
        }
    }
    return 0;
}
/*
I:
Push Bruce
Push Alan
Front
Pop
Push Tom
Pop
Front
Pop
Pop
Pop
Front

O:
Bruce
Tom
empty
*/
