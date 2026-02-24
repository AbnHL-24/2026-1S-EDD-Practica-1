#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <iostream>
#include "Mano.h"

class Jugador {
private:
    std::string nombre;
    int id;
    Mano* mano;

public:
    Jugador(std::string nombre, int id) : nombre(nombre), id(id) {
        mano = new Mano();
    }

    ~Jugador() {
        delete mano;
    }

    // Acciones de juego
    void tomarCarta(Carta* carta) {
        mano->agregarCarta(carta);
    }

    Carta* jugarCarta(int indice) {
        return mano->jugarCarta(indice);
    }
    
    // Getters
    std::string getNombre() const { return nombre; }
    int getId() const { return id; }
    Mano* getMano() const { return mano; }

    // Helpers
    void mostrarMano() const {
        std::cout << "Mano de " << nombre << ":" << std::endl;
        mano->mostrarMano();
    }
};

#endif // JUGADOR_H
