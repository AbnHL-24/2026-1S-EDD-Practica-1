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
    
    // Convertir color a string
    std::string colorStr;
    switch(this->color) {
        case Color::ROJO: colorStr = "ROJO"; break;
        case Color::AZUL: colorStr = "AZUL"; break;
        case Color::VERDE: colorStr = "VERDE"; break;
        case Color::AMARILLO: colorStr = "AMARILLO"; break;
        case Color::NARANJA: colorStr = "NARANJA"; break;
        case Color::TURQUESA: colorStr = "TURQUESA"; break;
        case Color::MORADO: colorStr = "MORADO"; break;
        case Color::ROSA: colorStr = "ROSA"; break;
        case Color::NEGRO: colorStr = "NEGRO"; break;
        default: colorStr = "DESCONOCIDO"; break;
    }
    
    // Convertir valor a string
    std::string valorStr;
    switch(this->valor) {
        case Valor::CERO: valorStr = "0"; break;
        case Valor::UNO: valorStr = "1"; break;
        case Valor::DOS: valorStr = "2"; break;
        case Valor::TRES: valorStr = "3"; break;
        case Valor::CUATRO: valorStr = "4"; break;
        case Valor::CINCO: valorStr = "5"; break;
        case Valor::SEIS: valorStr = "6"; break;
        case Valor::SIETE: valorStr = "7"; break;
        case Valor::OCHO: valorStr = "8"; break;
        case Valor::NUEVE: valorStr = "9"; break;
        case Valor::SALTA: valorStr = "SALTA"; break;
        case Valor::REVERSA: valorStr = "REVERSA"; break;
        case Valor::TOMA_DOS: valorStr = "+2"; break;
        case Valor::COMODIN: valorStr = "COMODIN"; break;
        case Valor::COMODIN_TOMA_CUATRO: valorStr = "+4"; break;
        case Valor::FLIP: valorStr = "FLIP"; break;
        case Valor::TOMA_UNO: valorStr = "+1"; break;
        case Valor::TOMA_CINCO: valorStr = "+5"; break;
        case Valor::SALTA_TODOS: valorStr = "SALTA TODOS"; break;
        default: valorStr = "DESCONOCIDO"; break;
    }
    
    ss << "[" << colorStr << " " << valorStr << "]";
    return ss.str();
}
