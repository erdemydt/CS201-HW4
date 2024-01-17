// Name: Erdem Pülat
// ID: 22103566 Section: 2
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream>
#include "Node.h"
using namespace std;
template <typename T>
class LinkedList
{
private:
    Node<T> *head;

public:
    int numOfItems;
    LinkedList() : head(nullptr), numOfItems(0) {}
    LinkedList(const LinkedList<T>& other) {
        head = nullptr; 
        Node<T>* otherCurrent = other.head;
        Node<T>* current = nullptr;

        while (otherCurrent != nullptr) {
            Node<T>* newNode = new Node<T>(otherCurrent->data);
            if (head == nullptr) {
                head = newNode;
                current = newNode;
            } else {
                current->next = newNode;
                current = newNode;
            }

            otherCurrent = otherCurrent->next;
        }
    }
    ~LinkedList()
    {
        clear();
    }
    void insert(T val);

    void display() const;
    bool remove(T val);
    void clear();
    Node<T>* get(int index) const;
    T* get(T val) const;
    int contains(T val) const;
    Node<T> *getHead() const;
};
template <typename T>
void LinkedList<T>::display()
    const
{
    Node<T> *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << endl;
        temp = temp->next;
    }
}
template <typename T>
bool LinkedList<T>::remove(T val)
{
    Node<T> *temp = head;
    Node<T> *prev = nullptr;
    while (temp != nullptr && temp->data != val)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr)
    {
        return false;
    }
    if (prev == nullptr)
    {
        head = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }
    delete temp;
    numOfItems--;
    return true;
}
template <typename T>
void LinkedList<T>::clear()
{
    Node<T> *temp = head;
    while (temp != nullptr)
    {
        Node<T> *nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    head = nullptr;
}
template <typename T>
void LinkedList<T>::insert(T val)
{
    Node<T> *newNode = new Node<T>(val);
    if (head == nullptr || val < head->data)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        Node<T> *current = head;
        while (current->next != nullptr && current->next->data < val)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    numOfItems++;
}

template <typename T>
Node<T>* LinkedList<T>::get(int index)
const
{
    if (index < 0 || index > numOfItems)
    {
        return NULL;
    }
    Node<T> *temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp;
}


template <typename T>
int LinkedList<T>::contains(T val)
    const
{
    int index =0;
    Node<T> *temp = head;
    while (temp != nullptr)
    {
        if (temp->data == val)
        {
            return index;
        }
        index++;
        temp = temp->next;
    }

    return -1;
}
template <typename T>
T* LinkedList<T>::get(T val)
    const
{

    Node<T> *temp = head;
    while (temp != nullptr)
    {
        if (temp->data == val)
        {
            return &temp->data;
        }
        temp = temp->next;
    }
    return nullptr;
}

template <typename T>
Node<T> *LinkedList<T>::getHead()
    const
{
    return head;
}
#endif
