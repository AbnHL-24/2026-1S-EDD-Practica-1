#ifndef CARTA_H
#define CARTA_H

#include <string>
#include <iostream>

enum class Color {
    ROJO, AZUL, VERDE, AMARILLO, // Lado Claro
    NARANJA, TURQUESA, MORADO, ROSA, // Lado Oscuro
    NEGRO // Comodines
};

enum class Valor {
    CERO, UNO, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE,
    SALTA, REVERSA, TOMA_DOS,
    COMODIN, COMODIN_TOMA_CUATRO,
    FLIP,
    // Específicos del Lado Oscuro
    TOMA_UNO, TOMA_CINCO, SALTA_TODOS
};

enum class Lado {
    CLARO,
    OSCURO
};

class Carta {
private:
    Color color;
    Valor valor;
    Lado ladoActivo;
    
    // Para cartas Flip, necesitamos almacenar las propiedades del otro lado
    Color colorReverso;
    Valor valorReverso;

public:
    Carta(Color c, Valor v, Lado l = Lado::CLARO);
    
    // Getters
    Color getColor() const;
    Valor getValor() const;
    Lado getLado() const;
    
    // Setters / Modificadores
    void voltear(); // Cambia el lado activo
    void setLadoReverso(Color c, Valor v); // Configura las propiedades del otro lado

    // Visualización
    std::string toString() const;
};

#endif // CARTA_H
