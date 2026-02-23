#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
    T data;
    Node* next;
    
    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class Stack {
private:
    Node<T>* topNode;
    int size;

public:
    Stack() : topNode(nullptr), size(0) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = topNode;
        topNode = newNode;
        size++;
    }

    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        Node<T>* temp = topNode;
        T value = temp->data;
        topNode = topNode->next;
        delete temp;
        size--;
        return value;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return topNode->data;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    int getSize() const {
        return size;
    }
};

#endif // STACK_H
