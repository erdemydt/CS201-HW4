// Name: Erdem Pülat
// ID: 22103566 Section: 2
#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <vector>
#include <stdexcept>

template <typename Typ>
class Stack {
private:
    Typ* arr;
    int top;
    int capacity;
public:

    Stack(int size = 10) {
        arr = new Typ[size];
        capacity = size;
        top = -1;
    }


    ~Stack() {
        delete[] arr;
    }


    void push(Typ value) {
   
        if (isFull()) {
            throw std::out_of_range("Stack Overflow");
        }
        top+=1;
        arr[top] = value;
    }


    Typ pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack Underflow");
        }
        return arr[top--];
    }


    bool isEmpty() const {
        return top == -1;
    }


    bool isFull() const {
        return top == capacity - 1;
    }


    Typ peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return arr[top];
    }
    Typ* peekPtr() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return arr+top;
    }
};
#endif