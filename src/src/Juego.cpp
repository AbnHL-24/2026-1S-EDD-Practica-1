#include "../include/Juego.h"
#include <iostream>
#include <limits> // Para std::numeric_limits

Juego::Juego() {
    mazo = new Mazo(false);
    jugadores = new ListaCircular();
    pilaDescarte = new Pila<Carta*>();
    sentidoHorario = true;
    juegoTerminado = false;
    colorActual = Color::NEGRO; // Inicial temporal
    valorActual = Valor::CERO;  // Inicial temporal
}

Juego::~Juego() {
    delete mazo;
    delete jugadores;
    delete pilaDescarte;
}

void Juego::inicializarJuego() {
    int numJugadores;
    std::cout << "Ingrese el número de jugadores (2-10): ";
    while (!(std::cin >> numJugadores) || numJugadores < 2 || numJugadores > 10) {
        std::cout << "Número inválido. Intente de nuevo: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(); // Limpiar buffer

    for (int i = 0; i < numJugadores; ++i) {
        std::string nombre;
        std::cout << "Nombre del Jugador " << (i + 1) << ": ";
        std::getline(std::cin, nombre);
        jugadores->agregarJugador(nombre);
    }

    mazo->barajar();
    repartirCartasIniciales();

    // Poner la primera carta en la pila de descarte
    Carta* primeraCarta = mazo->robarCarta();
    // Validar que no sea un +4 al inicio
    while (primeraCarta->getValor() == Valor::COMODIN_TOMA_CUATRO) {
        mazo->rellenarDesde(*pilaDescarte); 
        primeraCarta = mazo->robarCarta();
    }
    
    pilaDescarte->push(primeraCarta);
    colorActual = primeraCarta->getColor();
    valorActual = primeraCarta->getValor();

    std::cout << "\n¡El juego ha comenzado!" << std::endl;
    std::cout << "Carta inicial: " << primeraCarta->toString() << std::endl;
}

void Juego::repartirCartasIniciales() {
    // 7 cartas a cada jugador
    for (int i = 0; i < 7; ++i) {
        for(int j = 0; j < jugadores->getCantidad(); j++) {
             Jugador* actual = jugadores->obtenerJugadorActual();
             actual->tomarCarta(mazo->robarCarta());
             jugadores->siguienteTurno();
        }
    }
}

void Juego::buclePrincipal() {
    while (!juegoTerminado) {
        Jugador* actual = jugadores->obtenerJugadorActual();
        jugarTurno(actual);

        // Verificar victoria
        if (actual->getMano()->getCantidad() == 0) {
            std::cout << "\n¡¡¡ " << actual->getNombre() << " HA GANADO !!!" << std::endl;
            juegoTerminado = true;
        } else {
            siguienteTurno();
        }
    }
}

void Juego::jugarTurno(Jugador* jugadorActual) {
    bool turnoFinalizado = false;

    while (!turnoFinalizado) {
        std::cout << "\n----------------------------------------" << std::endl;
        std::cout << "Turno de: " << jugadorActual->getNombre() << std::endl;
        std::cout << "Carta en mesa: " << pilaDescarte->peek()->toString() << std::endl;
        
        std::string colorStr;
        switch(colorActual) {
            case Color::ROJO: colorStr = "ROJO"; break;
            case Color::AZUL: colorStr = "AZUL"; break;
            case Color::VERDE: colorStr = "VERDE"; break;
            case Color::AMARILLO: colorStr = "AMARILLO"; break;
            default: colorStr = "NEGRO"; break;
        }
        std::cout << "Color actual juego: " << colorStr << std::endl;

        jugadorActual->mostrarMano();
        
        std::cout << "Opciones: [Indice carta] para jugar, [-1] para robar: ";
        int opcion;
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (opcion == -1) {
            // Robar carta
            if (mazo->estaVacio()) {
                std::cout << "Mazo vacío, rebarajando descarte..." << std::endl;
                if (!pilaDescarte->estaVacia()) {
                    Carta* cima = pilaDescarte->pop(); 
                    mazo->rellenarDesde(*pilaDescarte);
                    pilaDescarte->push(cima); 
                }
            }

            if (!mazo->estaVacio()) {
                Carta* robada = mazo->robarCarta();
                jugadorActual->tomarCarta(robada);
                std::cout << "Has robado: " << robada->toString() << std::endl;
                // Opción para jugar inmediatamente si es válida omitida por simplicidad
            } else {
                std::cout << "No hay cartas para robar." << std::endl;
            }
            turnoFinalizado = true;
        } else {
            // Intentar jugar carta
            Carta* carta = jugadorActual->getMano()->obtenerCarta(opcion - 1); // Indice 1-based en UI
            if (carta != nullptr) {
                if (validarJugada(carta)) {
                    // Jugarla realmente (sacar de mano)
                    jugadorActual->jugarCarta(opcion - 1);
                    pilaDescarte->push(carta);
                    aplicarEfectoCarta(carta);
                    turnoFinalizado = true;
                    
                    // Grito de UNO
                    if (jugadorActual->getMano()->getCantidad() == 1) {
                        std::cout << "¡¡¡ UNO !!!" << std::endl;
                    }
                } else {
                    std::cout << "Jugada inválida. La carta no coincide en color o valor." << std::endl;
                }
            } else {
                std::cout << "Índice inválido." << std::endl;
            }
        }
    }
}

bool Juego::validarJugada(Carta* carta) {
    // 1. Comodines siempre se pueden jugar
    if (carta->getColor() == Color::NEGRO) return true;

    // 2. Coincidir color
    if (carta->getColor() == colorActual) return true;

    // 3. Coincidir valor/símbolo
    if (carta->getValor() == valorActual) return true;

    return false;
}

void Juego::aplicarEfectoCarta(Carta* carta) {
    valorActual = carta->getValor();
    
    // Si es comodín, el usuario elige el color
    if (carta->getColor() == Color::NEGRO) {
        int colorElegido;
        std::cout << "Elige color (0: Rojo, 1: Azul, 2: Verde, 3: Amarillo): ";
        while (!(std::cin >> colorElegido) || colorElegido < 0 || colorElegido > 3) {
            std::cout << "Inválido. 0-3: ";
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        colorActual = static_cast<Color>(colorElegido);
    } else {
        colorActual = carta->getColor();
    }

    // Efectos de acción
    switch (carta->getValor()) {
        case Valor::SALTA:
            std::cout << "¡Turno saltado!" << std::endl;
            jugadores->siguienteTurno(); 
            break;
        case Valor::REVERSA:
            std::cout << "¡Sentido invertido!" << std::endl;
            if (jugadores->getCantidad() == 2) {
                jugadores->siguienteTurno();
            } else {
                jugadores->invertirSentido();
            }
            break;
        case Valor::TOMA_DOS:
        case Valor::COMODIN_TOMA_CUATRO: {
            int cantidad = (carta->getValor() == Valor::TOMA_DOS) ? 2 : 4;
            std::cout << "¡El siguiente jugador come " << cantidad << " cartas y pierde el turno!" << std::endl;
            
            // Obtener siguiente jugador (víctima)
            Jugador* victima = jugadores->obtenerSiguienteJugador();
            if (victima) {
                for (int i = 0; i < cantidad; ++i) {
                     if (mazo->estaVacio()) {
                        Carta* cima = pilaDescarte->pop();
                        mazo->rellenarDesde(*pilaDescarte);
                        pilaDescarte->push(cima);
                    }
                    if (!mazo->estaVacio()) {
                        victima->tomarCarta(mazo->robarCarta());
                    }
                }
                std::cout << victima->getNombre() << " ha robado " << cantidad << " cartas." << std::endl;
            }
            // El jugador víctima pierde su turno
            jugadores->siguienteTurno();
            break;
        }
        default:
            break;
    }
}

void Juego::siguienteTurno() {
    jugadores->siguienteTurno();
}
