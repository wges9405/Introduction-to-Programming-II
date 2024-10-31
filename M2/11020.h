#ifndef function_h
#define function_h

#include <iostream>
#include <math.h>
using namespace std;

class BST{
public:
    BST():Height(0){}
    virtual ~BST() {}
    virtual void insert(const int &) = 0;
    virtual bool search(const int &) const = 0;
    virtual void print() const = 0;
    int height() const { return Height; }// An empty tree has height of 0. A tree with only root node has height of 1.

protected:
    int Height;
};

class Array_BST : public BST{
public:
    Array_BST();
    virtual ~Array_BST() {}
    virtual void insert(const int &) override; //root node is stored at index 1.
    virtual bool search(const int &) const override;
    virtual void print() const override{
        int k = pow(2, height());
        for (int i = 1; i <= k-1; i++) {
            if (array[i] != 0)
                cout << array[i] << " ";
        }
    }
private:
    int array[1025];
};

class ListNode{
    friend class List_BST; //make List_BST a friend

public:
    ListNode(const int &info):key( info ),left( NULL ),right( NULL ) //constructor
    {
    }//end ListNode constructor

private:
    int key;
    ListNode *left;
    ListNode *right;
};//end class ListNode

class List_BST : public BST{
public:
    List_BST();
    virtual ~List_BST()
    {
        deleteTree(root);
    }
    virtual void insert(const int &) override;
    virtual bool search(const int &) const override;
    virtual void print() const override{
        int i;
        for(i = 1; i <= Height; i++){
            printGivenLevel(root, i);
        }
    }

private:
    ListNode *root;
    // private member functions
    ListNode* createLeaf(int key) const; //new a ListNode and return its address
    /* clean a tree.*/
    void deleteTree(ListNode *root);

    void printGivenLevel(ListNode* Ptr, int level) const {
        if (Ptr == NULL)
            return;
        if (level == 1)
            cout << Ptr->key << " ";
        else if (level > 1)
        {
            printGivenLevel(Ptr->left, level-1);
            printGivenLevel(Ptr->right, level-1);
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////

Array_BST::Array_BST() {    // initial
    for (int i = 0 ; i < 1025 ; i++)
        array[i] = 0;
    Height = 0;
}
void Array_BST::insert(const int &num) {
    int i = 1;
    int h = 1;
    while (array[i]) {
        h++;
        if (array[i] < num) i = 2*i+1;
		else if (array[i] == num) return;
        else if (array[i] > num) i = 2*i;
    }
    if (Height < h) Height = h;
    array[i] = num;
}
bool Array_BST::search(const int &num) const {
    int i = 1;
    while (array[i]) {
        if (array[i] < num) i = 2*i+1;
        else if (array[i] > num) i = 2*i;
        else if (array[i] == num) return true;
    }
    return false;
}
List_BST::List_BST() {		// initial
    root = NULL;
}
void List_BST::insert(const int &num) {
    ListNode* temp = root;
    int h = 1;
    while (temp!=NULL) {
        h++;
        if (temp->key < num ) {
            if (temp->right == NULL) {
                if (Height < h) Height = h;
				temp->right = createLeaf(num);
                return;
            }
            else temp = temp->right;
        }
		
		else if (temp->key == num) return;
		
        else if (temp->key > num) {
            if (temp->left == NULL) {
                if (Height < h) Height = h;
				temp->left = createLeaf(num);
                return;
            }
            else temp = temp->left;
        }
    }
    if (Height < h) Height = h;
    root = createLeaf(num);
}
bool List_BST::search(const int &num) const {
    ListNode* temp = root;
    while (temp!=NULL) {
        if (temp->key < num) temp = temp->right;
        else if (temp->key > num) temp = temp->left;
        else if (temp->key == num) return true;
    }
    return false;
}

ListNode* List_BST::createLeaf(int key) const {
    ListNode* temp = new ListNode(key);
    return temp;
}

void List_BST::deleteTree(ListNode* root) {
    ListNode* temp = root;
    if (temp != NULL) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete temp;
    }
}
#endif /* function_h */
