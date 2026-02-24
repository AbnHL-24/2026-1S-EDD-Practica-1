#ifndef MANO_H
#define MANO_H

#include "Carta.h"
#include <iostream>

struct NodoCarta {
    Carta* carta;
    NodoCarta* siguiente;
    NodoCarta* anterior;

    NodoCarta(Carta* c) : carta(c), siguiente(nullptr), anterior(nullptr) {}
};

class Mano {
private:
    NodoCarta* cabeza;
    NodoCarta* cola;
    int cantidadCartas;

public:
    Mano() : cabeza(nullptr), cola(nullptr), cantidadCartas(0) {}

    ~Mano() {
        while (cabeza != nullptr) {
            NodoCarta* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp->carta; // Ojo: ¿Quién es dueño de la carta? El mazo las crea, pero la mano las posee.
            delete temp;
        }
    }

    void agregarCarta(Carta* carta) {
        NodoCarta* nuevo = new NodoCarta(carta);
        if (cabeza == nullptr) {
            cabeza = cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            nuevo->anterior = cola;
            cola = nuevo;
        }
        cantidadCartas++;
    }

    // Método para jugar (remover) una carta específica por índice (para la UI de consola)
    Carta* jugarCarta(int indice) {
        if (indice < 0 || indice >= cantidadCartas) return nullptr;

        NodoCarta* actual = cabeza;
        for (int i = 0; i < indice; ++i) {
            actual = actual->siguiente;
        }

        // Desvincular nodo
        if (actual->anterior) actual->anterior->siguiente = actual->siguiente;
        else cabeza = actual->siguiente; // Era la cabeza

        if (actual->siguiente) actual->siguiente->anterior = actual->anterior;
        else cola = actual->anterior; // Era la cola

        Carta* cartaJugada = actual->carta;
        delete actual;
        cantidadCartas--;
        return cartaJugada;
    }
    
    Carta* obtenerCarta(int indice) const {
        if (indice < 0 || indice >= cantidadCartas) return nullptr;
        NodoCarta* actual = cabeza;
        for (int i = 0; i < indice; ++i) {
            actual = actual->siguiente;
        }
        return actual->carta;
    }

    int getCantidad() const { return cantidadCartas; }

    void mostrarMano() const {
        NodoCarta* actual = cabeza;
        int i = 1;
        while (actual != nullptr) {
            std::cout << i << ". " << actual->carta->toString() << std::endl;
            actual = actual->siguiente;
            i++;
        }
    }
};

#endif // MANO_H
