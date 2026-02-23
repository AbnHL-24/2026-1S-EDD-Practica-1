#include "../include/Card.h"
#include <iostream>
#include <sstream>

Card::Card(Color c, Value v, Side s) : color(c), value(v), side(s) {
    // Default back side values
    this->backColor = Color::ORANGE; // Example
    this->backValue = Value::ZERO;
}

Color Card::getColor() const {
    return this->color;
}

Value Card::getValue() const {
    return this->value;
}

Side Card::getSide() const {
    return this->side;
}

void Card::flip() {
    if (this->side == Side::LIGHT) {
        this->side = Side::DARK;
        // Swap values if needed
    } else {
        this->side = Side::LIGHT;
    }
}

void Card::setBackSide(Color c, Value v) {
    this->backColor = c;
    this->backValue = v;
}

std::string Card::toString() const {
    std::stringstream ss;
    ss << "Card [Color: " << static_cast<int>(this->color) << ", Value: " << static_cast<int>(this->value) << "]";
    return ss.str();
}
