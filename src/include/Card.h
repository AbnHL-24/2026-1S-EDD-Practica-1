#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

enum class Color {
    RED, BLUE, GREEN, YELLOW, // Light Side
    ORANGE, TEAL, PURPLE, PINK, // Dark Side
    BLACK // Wild Cards
};

enum class Value {
    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
    SKIP, REVERSE, DRAW_TWO,
    WILD, WILD_DRAW_FOUR,
    FLIP,
    // Dark Side specific
    DRAW_ONE, DRAW_FIVE, SKIP_EVERYONE
};

enum class Side {
    LIGHT,
    DARK
};

class Card {
private:
    Color color;
    Value value;
    Side side;
    
    // For Flip cards, we need to store the other side's properties too
    Color backColor;
    Value backValue;

public:
    Card(Color c, Value v, Side s = Side::LIGHT);
    
    // Getters
    Color getColor() const;
    Value getValue() const;
    Side getSide() const;
    
    // Setters / Modifiers
    void flip(); // Changes the active side
    void setBackSide(Color c, Value v); // Sets the properties of the other side

    // Display
    std::string toString() const;
};

#endif // CARD_H
