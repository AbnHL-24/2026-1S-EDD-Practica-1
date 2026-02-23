#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "Stack.h"
#include <vector> // Using vector only for shuffling convenience, can replace with raw array if needed
#include <algorithm>
#include <random>
#include <chrono>

class Deck {
private:
    Stack<Card*> cards;
    int totalCards;

    void initializeStandardDeck();
    void initializeFlipDeck(); // If flip mode is enabled

public:
    Deck(bool isFlip = false);
    ~Deck();

    void shuffle();
    Card* drawCard();
    bool isEmpty() const;
    int remainingCards() const;
    
    // Add logic to refill from discard pile later
    void refillFrom(Stack<Card*>& discardPile);
};

#endif // DECK_H
