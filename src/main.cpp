#include <iostream>
#include "include/Mazo.h"
#include "include/Carta.h"

int main() {
    std::cout << "=== PRUEBA DE GENERACIÓN DE MAZO ===" << std::endl;
    
    // 1. Crear el mazo
    Mazo mazo(false); // false = Mazo estándar (no flip)
    
    std::cout << "Mazo creado. Cartas totales: " << mazo.cartasRestantes() << std::endl;

    // 2. Barajar
    std::cout << "Barajando cartas..." << std::endl;
    mazo.barajar();

    // 3. Robar algunas cartas para verificar variedad
    std::cout << "\n--- Robando 10 cartas de prueba ---" << std::endl;
    for (int i = 0; i < 10; ++i) {
        if (!mazo.estaVacio()) {
            Carta* c = mazo.robarCarta();
            std::cout << "Carta " << (i + 1) << ": " << c->toString() << std::endl;
            delete c; // Importante liberar memoria en esta prueba
        }
    }

    std::cout << "\nCartas restantes en el mazo: " << mazo.cartasRestantes() << std::endl;
    std::cout << "=== PRUEBA FINALIZADA ===" << std::endl;

    return 0;
}
