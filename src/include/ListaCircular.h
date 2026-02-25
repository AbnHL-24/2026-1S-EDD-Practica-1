#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H

#include "Jugador.h"
#include <iostream>

struct NodoJugador {
    Jugador* jugador;
    NodoJugador* siguiente;
    NodoJugador* anterior; // Añadido para facilitar reversa

    NodoJugador(Jugador* j) : jugador(j), siguiente(nullptr), anterior(nullptr) {}
};

class ListaCircular {
private:
    NodoJugador* cabeza;
    NodoJugador* turnoActual;
    int cantidadJugadores;
    bool sentidoHorario; // true = horario (default), false = antihorario

public:
    ListaCircular() : cabeza(nullptr), turnoActual(nullptr), cantidadJugadores(0), sentidoHorario(true) {}

    ~ListaCircular() {
        if (!cabeza) return;
        NodoJugador* actual = cabeza;
        do {
            NodoJugador* siguiente = actual->siguiente;
            delete actual->jugador;
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
    }

    void agregarJugador(std::string nombre) {
        Jugador* nuevoJugador = new Jugador(nombre, cantidadJugadores + 1);
        NodoJugador* nuevoNodo = new NodoJugador(nuevoJugador);

        if (!cabeza) {
            cabeza = nuevoNodo;
            cabeza->siguiente = cabeza;
            cabeza->anterior = cabeza;
            turnoActual = cabeza;
        } else {
            NodoJugador* ultimo = cabeza->anterior;
            ultimo->siguiente = nuevoNodo;
            nuevoNodo->anterior = ultimo;
            nuevoNodo->siguiente = cabeza;
            cabeza->anterior = nuevoNodo;
        }
        cantidadJugadores++;
    }

    void siguienteTurno() {
        if (!turnoActual) return;
        if (sentidoHorario) {
            turnoActual = turnoActual->siguiente;
        } else {
            turnoActual = turnoActual->anterior;
        }
    }

    void invertirSentido() {
        sentidoHorario = !sentidoHorario;
    }

    Jugador* obtenerJugadorActual() const {
        return turnoActual ? turnoActual->jugador : nullptr;
    }
    
    // Método para obtener el siguiente jugador SIN avanzar el turno (para ver a quién le toca comer +2, etc)
    Jugador* obtenerSiguienteJugador() const {
        if (!turnoActual) return nullptr;
        return sentidoHorario ? turnoActual->siguiente->jugador : turnoActual->anterior->jugador;
    }

    int getCantidad() const { return cantidadJugadores; }

    void mostrarJugadores() const {
        if (!cabeza) return;
        NodoJugador* temp = cabeza;
        do {
            std::cout << (temp == turnoActual ? "-> " : "   ") 
                      << temp->jugador->getNombre() << " (ID: " << temp->jugador->getId() << ")" << std::endl;
            temp = temp->siguiente;
        } while (temp != cabeza);
    }
};

#endif // LISTACIRCULAR_H
