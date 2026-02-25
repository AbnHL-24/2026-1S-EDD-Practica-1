#include <iostream>
#include "include/Juego.h"

int main() {
    std::cout << "=== UNO GAME C++ ===" << std::endl;
    
    Juego juego;
    juego.inicializarJuego();
    juego.buclePrincipal();

    std::cout << "Gracias por jugar." << std::endl;
    return 0;
}
