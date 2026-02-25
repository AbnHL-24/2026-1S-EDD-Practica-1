#ifndef JUEGO_H
#define JUEGO_H

#include "Mazo.h"
#include "ListaCircular.h"
#include "Pila.h"
#include "Carta.h"

class Juego {
private:
    Mazo* mazo;
    ListaCircular* jugadores;
    Pila<Carta*>* pilaDescarte;
    
    // Estado del juego
    bool sentidoHorario;
    Color colorActual;
    Valor valorActual;
    bool juegoTerminado;

    // Métodos privados de ayuda
    void repartirCartasIniciales();
    void jugarTurno(Jugador* jugadorActual);
    bool validarJugada(Carta* cartaJugada);
    void aplicarEfectoCarta(Carta* carta);
    void siguienteTurno();

public:
    Juego();
    ~Juego();

    void inicializarJuego();
    void buclePrincipal();
};

#endif // JUEGO_H
