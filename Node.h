// Name: Erdem Pülat
// ID: 22103566 Section: 2
#ifndef NODE_H
#define NODE_H
template <typename T>
class Node
{
public:
    T data;
    Node<T> *next;
    Node(T val) : data(val), next(nullptr) {}
    void setNext(Node<T> *next);
    bool isEmpty();
    Node<T> *getNext();
};

template <typename T>
void Node<T>::setNext(Node<T> *next)
{
    this->next = next;
}

template <typename T>
Node<T> *Node<T>::getNext()
{
    return next;
}
#endif
