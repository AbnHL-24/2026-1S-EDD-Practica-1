#ifndef MAZO_H
#define MAZO_H

#include "Carta.h"
#include "Pila.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class Mazo {
private:
    Pila<Carta*> cartas;
    
    // Método privado para generar un deck estándar
    void inicializarMazoEstandar();
    
public:
    Mazo(bool esFlip = false);
    ~Mazo();

    void barajar();
    Carta* robarCarta();
    bool estaVacio() const;
    int cartasRestantes() const;
    
    // Rellenar desde la pila de descarte
    void rellenarDesde(Pila<Carta*>& pilaDescarte);
};

#endif // MAZO_H
