#include "../include/Carta.h"
#include <sstream>

Carta::Carta(Color c, Valor v, Lado l) : color(c), valor(v), ladoActivo(l) {
    // Valores predeterminados para el reverso
    this->colorReverso = Color::NARANJA; // Ejemplo
    this->valorReverso = Valor::CERO;
}

Color Carta::getColor() const {
    return this->color;
}

Valor Carta::getValor() const {
    return this->valor;
}

Lado Carta::getLado() const {
    return this->ladoActivo;
}

void Carta::voltear() {
    if (this->ladoActivo == Lado::CLARO) {
        this->ladoActivo = Lado::OSCURO;
    } else {
        this->ladoActivo = Lado::CLARO;
    }
}

void Carta::setLadoReverso(Color c, Valor v) {
    this->colorReverso = c;
    this->valorReverso = v;
}

std::string Carta::toString() const {
    std::stringstream ss;
    ss << "Carta [Color: " << static_cast<int>(this->color) << ", Valor: " << static_cast<int>(this->valor) << "]";
    return ss.str();
}
