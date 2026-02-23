#include "../include/Mazo.h"

Mazo::Mazo(bool esFlip) {
    if (esFlip) {
        // Implementar inicialización para Flip
    } else {
        inicializarMazoEstandar();
    }
}

Mazo::~Mazo() {
    while (!cartas.estaVacia()) {
        Carta* c = cartas.pop();
        delete c;
    }
}

void Mazo::inicializarMazoEstandar() {
    // Ejemplo de creación de algunas cartas
    // 0: Rojo, 1: Azul, 2: Verde, 3: Amarillo
    // 0-9: Numeros, 10: Salta, 11: Reversa, 12: TomaDos
    // 13: Comodin, 14: ComodinTomaCuatro
    
    // Aquí iría la lógica para poblar el mazo
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
    // y luego barajar
    while (!pilaDescarte.estaVacia()) {
        cartas.push(pilaDescarte.pop());
    }
    barajar();
}
