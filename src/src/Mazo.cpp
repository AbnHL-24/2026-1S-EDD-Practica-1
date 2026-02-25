#include "../include/Mazo.h"

Mazo::Mazo(int cantidadMazos, bool esFlip) {
    if (esFlip) {
        // Implementar inicialización para Flip
    } else {
        inicializarMazoEstandar(cantidadMazos);
    }
}

Mazo::~Mazo() {
    while (!cartas.estaVacia()) {
        Carta* c = cartas.pop();
        delete c;
    }
}

void Mazo::inicializarMazoEstandar(int cantidadMazos) {
    for (int m = 0; m < cantidadMazos; ++m) {
        Color colores[] = {Color::ROJO, Color::AZUL, Color::VERDE, Color::AMARILLO};
        
        for (const auto& color : colores) {
            // 1 carta de valor 0
            cartas.push(new Carta(color, Valor::CERO));

            // 2 cartas de valor 1-9
            for (int i = 1; i <= 9; ++i) {
                cartas.push(new Carta(color, static_cast<Valor>(i)));
                cartas.push(new Carta(color, static_cast<Valor>(i)));
            }

            // 2 cartas de acción: Salta, Reversa, TomaDos
            Valor acciones[] = {Valor::SALTA, Valor::REVERSA, Valor::TOMA_DOS};
            for (const auto& accion : acciones) {
                cartas.push(new Carta(color, accion));
                cartas.push(new Carta(color, accion));
            }
        }

        // Cartas Comodín (4 de cada tipo)
        for (int i = 0; i < 4; ++i) {
            cartas.push(new Carta(Color::NEGRO, Valor::COMODIN));
            cartas.push(new Carta(Color::NEGRO, Valor::COMODIN_TOMA_CUATRO));
        }
    }
}

void Mazo::barajar() {
    // Para barajar, extraemos todo a un vector temporal, mezclamos y reinsertamos
    std::vector<Carta*> temp;
    while (!cartas.estaVacia()) {
        temp.push_back(cartas.pop());
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(temp.begin(), temp.end(), std::default_random_engine(seed));

    for (Carta* c : temp) {
        cartas.push(c);
    }
}

Carta* Mazo::robarCarta() {
    if (cartas.estaVacia()) {
        throw std::runtime_error("El mazo está vacío");
    }
    return cartas.pop();
}

bool Mazo::estaVacio() const {
    return cartas.estaVacia();
}

int Mazo::cartasRestantes() const {
    return cartas.getTamano();
}

void Mazo::rellenarDesde(Pila<Carta*>& pilaDescarte) {
    // Lógica para rellenar el mazo desde la pila de descarte
    // Mover cartas de la pila de descarte al mazo (excepto quizás la última jugada, 
    // pero eso se suele manejar fuera, asumiendo que aquí entra lo que se puede rebarajar)
    while (!pilaDescarte.estaVacia()) {
        cartas.push(pilaDescarte.pop());
    }
    barajar();
}
