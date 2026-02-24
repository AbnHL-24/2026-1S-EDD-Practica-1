#include <iostream>
#include <string>
#include <vector>
#include "include/Carta.h"
#include "include/Mazo.h"
#include "include/Mano.h"
#include "include/Jugador.h"
#include "include/ListaCircular.h"

int main() {
    std::cout << "=== PRUEBA DE ESTRUCTURAS DE JUGADORES ===" << std::endl;

    // 1. Crear Lista de Jugadores
    ListaCircular lista;
    lista.agregarJugador("Juan");
    lista.agregarJugador("Pedro");
    lista.agregarJugador("Ana");

    // 2. Mostrar Jugadores
    std::cout << "Jugadores en partida:" << std::endl;
    lista.mostrarJugadores();

    // 3. Crear Mazo y Barajar
    Mazo mazo(false);
    mazo.barajar();

    // 4. Repartir Cartas
    // (Lógica simplificada para probar Mano y Jugador)
    std::cout << "\nRepartiendo 5 cartas a cada uno..." << std::endl;
    for (int i = 0; i < 3; ++i) { // 3 jugadores
        Jugador* actual = lista.obtenerJugadorActual();
        for (int j = 0; j < 5; ++j) {
            actual->tomarCarta(mazo.robarCarta());
        }
        lista.siguienteTurno();
    }

    // 5. Mostrar Manos
    std::cout << "\nManos después de repartir:" << std::endl;
    lista.siguienteTurno(); // Reiniciar al primer jugador (si es circular)
    for (int i = 0; i < 3; ++i) {
        Jugador* actual = lista.obtenerJugadorActual();
        actual->mostrarMano();
        std::cout << "--------------------" << std::endl;
        lista.siguienteTurno();
    }

    std::cout << "=== PRUEBA FINALIZADA ===" << std::endl;
    return 0;
}
