#ifndef PILA_H
#define PILA_H

#include <iostream>
#include <stdexcept>

template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente;
    
    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};

template <typename T>
class Pila {
private:
    Nodo<T>* cima;
    int tamano;

public:
    Pila() : cima(nullptr), tamano(0) {}

    ~Pila() {
        while (!estaVacia()) {
            pop();
        }
    }

    void push(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        nuevoNodo->siguiente = cima;
        cima = nuevoNodo;
        tamano++;
    }

    T pop() {
        if (estaVacia()) {
            throw std::runtime_error("La pila está vacía");
        }
        Nodo<T>* temporal = cima;
        T valor = temporal->dato;
        cima = cima->siguiente;
        delete temporal;
        tamano--;
        return valor;
    }

    T peek() const {
        if (estaVacia()) {
            throw std::runtime_error("La pila está vacía");
        }
        return cima->dato;
    }

    bool estaVacia() const {
        return cima == nullptr;
    }

    int getTamano() const {
        return tamano;
    }
};

#endif // PILA_H
