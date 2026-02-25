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
    jugadorConUnaCartaSinGritar = nullptr;
}

Juego::~Juego() {
    delete mazo;
    delete jugadores;
    delete pilaDescarte;
}

void Juego::inicializarJuego() {
    int numJugadores;
    bool numeroValido = false;
    
    while (!numeroValido) {
        std::cout << "Ingrese el numero de jugadores (minimo 2): ";
        while (!(std::cin >> numJugadores) || numJugadores < 2) {
            std::cout << "Numero invalido. Debe ser minimo 2 jugadores: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        // Advertencia para numeros grandes
        if (numJugadores > 50) {
            std::cout << "\nADVERTENCIA: " << numJugadores << " jugadores puede consumir mucha memoria y hacer el juego muy lento." << std::endl;
            std::cout << "Desea continuar? (s/n): ";
            char confirmacion;
            std::cin >> confirmacion;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (confirmacion == 's' || confirmacion == 'S') {
                numeroValido = true;
            } else {
                std::cout << "Volviendo a solicitar numero de jugadores...\n" << std::endl;
            }
        } else {
            numeroValido = true;
        }
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer

    int cantidadMazosCalculada = ((numJugadores - 1) / 6) + 1;
    int cartasTotales = cantidadMazosCalculada * 108;
    std::cout << "Configuracion: " << numJugadores << " jugadores. Se usaran " << cantidadMazosCalculada << " mazos (" << cartasTotales << " cartas totales)." << std::endl;

    for (int i = 0; i < numJugadores; ++i) {
        std::string nombre;
        std::cout << "Nombre del Jugador " << (i + 1) << ": ";
        std::getline(std::cin, nombre);
        jugadores->agregarJugador(nombre);
    }

    // Calcular número de mazos necesarios
    // Regla: 1-6 jugadores: 1 mazo. 7-12: 2 mazos, etc.
    // Formula: ((n_jugadores - 1) / 6 + 1)
    int cantidadMazos = ((numJugadores - 1) / 6) + 1;
    
    // Reconstruir el mazo con la cantidad correcta
    delete mazo;
    mazo = new Mazo(cantidadMazos, false);

    mazo->barajar();
    repartirCartasIniciales();

    // Poner la primera carta en la pila de descárte
    Carta* primeraCarta = mazo->robarCarta();
    // Validar que no sea un +4 al inicio
    while (primeraCarta->getValor() == Valor::COMODIN_TOMA_CUATRO) {
        mazo->rellenarDesde(*pilaDescarte); 
        primeraCarta = mazo->robarCarta();
    }
    
    pilaDescarte->push(primeraCarta);
    colorActual = primeraCarta->getColor();
    valorActual = primeraCarta->getValor();

    std::cout << "\nEl juego ha comenzado!" << std::endl;
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
        
        // Verificar si alguien quiere reportar antes de que inicie el turno
        verificarReporteUNO();
        
        jugarTurno(actual);

        // Verificar victoria
        if (actual->getMano()->getCantidad() == 0) {
            std::cout << "\n" << actual->getNombre() << " HA GANADO !!!" << std::endl;
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
        
        std::cout << "Opciones: [Indice carta] para jugar, [0] para robar: ";
        int opcion;
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (opcion == 0) {
            // Robar carta
            if (mazo->estaVacio()) {
                std::cout << "Mazo vacio, rebarajando descarte..." << std::endl;
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
            } else {
                std::cout << "No hay cartas para robar." << std::endl;
            }
            turnoFinalizado = true;
        } else if (opcion < 0 || opcion > jugadorActual->getMano()->getCantidad()) {
            // Validar rango de opciones
            std::cout << "Opcion invalida. Debe elegir entre 0 (robar) o 1-" << jugadorActual->getMano()->getCantidad() << " (jugar carta)." << std::endl;
        } else {
            // Intentar jugar carta
            Carta* carta = jugadorActual->getMano()->obtenerCarta(opcion - 1); // Indice 1-based en UI
            if (carta != nullptr) {
                if (validarJugada(carta)) {
                    // Jugarla realmente (sacar de mano)
                    jugadorActual->jugarCarta(opcion - 1);
                    pilaDescarte->push(carta);
                    aplicarEfectoCarta(carta);
                    
                    // Sistema de grito de UNO manual
                    if (jugadorActual->getMano()->getCantidad() == 1) {
                        std::cout << "\nTienes 1 carta! Escribe 'UNO' para gritar UNO (o presiona Enter para omitir): ";
                        std::cin.ignore(); // Limpiar el buffer del numero anterior
                        std::string grito;
                        std::getline(std::cin, grito);
                        
                        if (grito == "UNO" || grito == "uno") {
                            std::cout << jugadorActual->getNombre() << " ha gritado: UNO !!!" << std::endl;
                            jugadorConUnaCartaSinGritar = nullptr; // Grito correctamente
                        } else {
                            std::cout << jugadorActual->getNombre() << " no grito UNO..." << std::endl;
                            jugadorConUnaCartaSinGritar = jugadorActual; // Marcar para posible reporte
                        }
                    } else {
                        // Si ya no tiene 1 carta, limpiar el flag
                        if (jugadorConUnaCartaSinGritar == jugadorActual) {
                            jugadorConUnaCartaSinGritar = nullptr;
                        }
                    }
                    
                    turnoFinalizado = true;
                } else {
                    std::cout << "Jugada invalida. La carta no coincide en color o valor." << std::endl;
                }
            } else {
                std::cout << "Indice invalido." << std::endl;
            }
        }
    }
}

bool Juego::validarJugada(Carta* carta) {
    // 1. Comodines siempre se pueden jugar
    if (carta->getColor() == Color::NEGRO) return true;

    // 2. Coincidir color
    if (carta->getColor() == colorActual) return true;

    // 3. Coincidir valor/simbolo
    if (carta->getValor() == valorActual) return true;

    return false;
}

void Juego::aplicarEfectoCarta(Carta* carta) {
    valorActual = carta->getValor();
    
    // Si es comodin, el usuario elige el color
    if (carta->getColor() == Color::NEGRO) {
        int colorElegido;
        std::cout << "Elige color (0: Rojo, 1: Azul, 2: Verde, 3: Amarillo): ";
        while (!(std::cin >> colorElegido) || colorElegido < 0 || colorElegido > 3) {
            std::cout << "Invalido. 0-3: ";
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        colorActual = static_cast<Color>(colorElegido);
    } else {
        colorActual = carta->getColor();
    }

    // Efectos de accion
    switch (carta->getValor()) {
        case Valor::SALTA:
            std::cout << "Turno saltado!" << std::endl;
            jugadores->siguienteTurno(); 
            break;
        case Valor::REVERSA:
            std::cout << "Sentido invertido!" << std::endl;
            if (jugadores->getCantidad() == 2) {
                jugadores->siguienteTurno();
            } else {
                jugadores->invertirSentido();
            }
            break;
        case Valor::TOMA_DOS:
        case Valor::COMODIN_TOMA_CUATRO: {
            int cantidad = (carta->getValor() == Valor::TOMA_DOS) ? 2 : 4;
            std::cout << "El siguiente jugador come " << cantidad << " cartas y pierde el turno!" << std::endl;
            
            // Obtener siguiente jugador (victima)
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

void Juego::verificarReporteUNO() {
    // Si hay un jugador que no grito UNO, dar oportunidad de reportar
    if (jugadorConUnaCartaSinGritar != nullptr) {
        std::cout << "\n>>> Alguien quiere reportar que " << jugadorConUnaCartaSinGritar->getNombre() 
                  << " no grito UNO? (s/n): ";
        
        char respuesta;
        std::cin >> respuesta;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (respuesta == 's' || respuesta == 'S') {
            // Verificar si efectivamente tiene 1 carta
            if (jugadorConUnaCartaSinGritar->getMano()->getCantidad() == 1) {
                std::cout << "REPORTE EXITOSO! " << jugadorConUnaCartaSinGritar->getNombre() 
                          << " no grito UNO y debe robar 2 cartas." << std::endl;
                
                // Dar 2 cartas de penalizacion
                for (int i = 0; i < 2; ++i) {
                    if (mazo->estaVacio()) {
                        Carta* cima = pilaDescarte->pop();
                        mazo->rellenarDesde(*pilaDescarte);
                        pilaDescarte->push(cima);
                    }
                    if (!mazo->estaVacio()) {
                        jugadorConUnaCartaSinGritar->tomarCarta(mazo->robarCarta());
                    }
                }
                
                std::cout << jugadorConUnaCartaSinGritar->getNombre() << " ahora tiene " 
                          << jugadorConUnaCartaSinGritar->getMano()->getCantidad() << " cartas." << std::endl;
                jugadorConUnaCartaSinGritar = nullptr; // Limpiar el flag
            } else {
                std::cout << "REPORTE ERRONEO! " << jugadorConUnaCartaSinGritar->getNombre() 
                          << " tiene " << jugadorConUnaCartaSinGritar->getMano()->getCantidad() 
                          << " cartas (no 1)." << std::endl;
                std::cout << "Quien reporto: Ingrese su nombre: ";
                
                std::string nombreReportador;
                std::getline(std::cin, nombreReportador);
                
                std::cout << nombreReportador << " hizo un reporte erroneo y debe robar 2 cartas." << std::endl;
                
                // Buscar al reportador y darle 2 cartas de penalizacion
                // Por simplicidad, le damos las cartas al jugador actual (asumiendo que es quien reporto)
                Jugador* reportador = jugadores->obtenerJugadorActual();
                for (int i = 0; i < 2; ++i) {
                    if (mazo->estaVacio()) {
                        Carta* cima = pilaDescarte->pop();
                        mazo->rellenarDesde(*pilaDescarte);
                        pilaDescarte->push(cima);
                    }
                    if (!mazo->estaVacio()) {
                        reportador->tomarCarta(mazo->robarCarta());
                    }
                }
                
                jugadorConUnaCartaSinGritar = nullptr; // Limpiar el flag
            }
        } else {
            std::cout << "Nadie reporto. El juego continua." << std::endl;
        }
    }
}
